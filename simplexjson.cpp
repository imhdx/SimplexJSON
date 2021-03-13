#include "simplexjson.h"
#include <cassert>
#include <error.h>
#include <cmath>
#include <cstdlib>
#include <cstring>

#define EXCEPT(c,ch) do{assert(*c->json==(ch));c->json++;}while(0)
#define ISDIGIT(CH) ((CH)>='0'&&(CH)<='9')
#define ISDIGIT1TO9(ch) ((ch)>='1'&&(ch)<='9')

struct simplex_context{
  const char *json;
};

// 没有错误返回，因为whitespace可以为空，所以一定正确
static void simplex_parse_whitespace(simplex_context *c){
  const char *p=c->json;
  while (*p==' ' || *p=='\t' || *p=='\n' || *p=='\r')
	p++;
  c->json=p;
}

static int simplex_parse_literal(simplex_context *c, simplex_value *v, const char *literal, simplex_type type){
  EXCEPT(c,literal[0]);
  size_t i=0;
  for (i=0;literal[i+1];i++){
	if (c->json[i]!=literal[i+1])
	  return SIMPLEX_ERROR;
  }
  c->json += i;
  v->type=type;
  return SIMPLEX_PARSE_OK;
}

static int simplex_parse_number(simplex_context *c, simplex_value *v){
  const char *p=c->json;
  if (*p=='-') p++;
  if (*p=='0') p++;
  else{
	if (!ISDIGIT1TO9(*p)) return SIMPLEX_ERROR;
	for (p++;ISDIGIT(*p);p++);
  }
  if (*p=='.'){
	p++;
	if (!ISDIGIT(*p)) return SIMPLEX_ERROR;
	for (p++;ISDIGIT(*p);p++);
  }
  if (*p=='e' || *p=='E'){
	p++;
	if (*p=='+'||*p=='-') p++;
	if (!ISDIGIT(*p)) return SIMPLEX_ERROR;
	for (p++;ISDIGIT(*p);p++);
  }
  // 为了后面正确判断errno
  errno=0;
  v->n=strtod(c->json,nullptr);
  if (errno==ERANGE && (v->n==HUGE_VAL || v->n==-HUGE_VAL))
	return SIMPLEX_ERROR;
  v->type=SIMPLEX_NUMBER;
  c->json=p;
  return SIMPLEX_PARSE_OK;
}

static int simplex_parse_string(simplex_context *c, simplex_value *v){
  const char *p;
  EXCEPT(c,'\"');
  p=c->json;
  std::string tmp="";
  while (true){
	char ch=*p++;
	switch (ch) {
	  case '\"':
		simplex_set_string(v, tmp);
		c->json=p;
		return SIMPLEX_PARSE_OK;
	  case '\\':
		switch (*p++) {
		  case '\"' : tmp+='\"';break;
		  case '\\' : tmp+='\\';break;
		  case '/' : tmp+='/';break;
		  case 'b': tmp+='\b';break;
		  case 'n' : tmp+='\n';break;
		  case 'f' : tmp+='\f';break;
		  case 'r' : tmp+='\r';break;
		  case 't' : tmp+='\t';break;
		  default:
			return SIMPLEX_ERROR;
		}
		break;
	  case '\0':
		return SIMPLEX_ERROR;
	  default:
		tmp+=ch;
	}
  }
}

static int simplex_parse_value(simplex_context *c, simplex_value *v);
static int simplex_parse_array(simplex_context *c, simplex_value *v){
  EXCEPT(c,'[');
  simplex_parse_whitespace(c);
  if (*c->json==']'){
	// 空数组
	c->json++;
	v->type=SIMPLEX_ARRAY;
	v->a.resize(0);
	return SIMPLEX_PARSE_OK;
  }
  int ret;
  while (true){
	simplex_value e;
	simplex_free(&e);
	if ((ret=simplex_parse_value(c,&e))!=SIMPLEX_PARSE_OK)
	  break;
	v->a.push_back(e);
	simplex_parse_whitespace(c);
	if (*c->json==','){
	  c->json++;
	  simplex_parse_whitespace(c);
	}
	else if (*c->json==']'){
	  c->json++;
	  v->type=SIMPLEX_ARRAY;
	  return SIMPLEX_PARSE_OK;
	}
	else{
	  ret=SIMPLEX_ERROR;
	  break;
	}
  }
  return ret;
}

#include <unordered_map>
typedef std::unordered_map<std::string,simplex_value*> object;

static int simplex_parse_object(simplex_context *c, simplex_value *v){
  EXCEPT(c, '{');
  simplex_parse_whitespace(c);
  if (*c->json=='}'){
	c->json++;
	v->type=SIMPLEX_OBJECT;
	v->o={};
	return SIMPLEX_PARSE_OK;
  }
  int ret;
  object tmp;
  while (true){
	if (*c->json!='\"'){
	  ret=SIMPLEX_ERROR;
	  break;
	}
	simplex_value key;
	simplex_value *val;
	if ((ret=simplex_parse_string(c,&key))!=SIMPLEX_PARSE_OK){
	  break;
	}
	simplex_parse_whitespace(c);
	if (*c->json!=':'){
	  ret=SIMPLEX_ERROR;
	  break;
	}
	else c->json++;
	simplex_parse_whitespace(c);
	val=new simplex_value;
	if ((ret=simplex_parse_value(c,val))!=SIMPLEX_PARSE_OK){
	  delete val;
	  break;
	}
	tmp.insert({key.s,val});
	simplex_parse_whitespace(c);
	if (*c->json==','){
	  c->json++;
	  simplex_parse_whitespace(c);
	}
	else if (*c->json=='}'){
	  c->json++;
	  v->o=tmp;
	  v->type=SIMPLEX_OBJECT;
	  return SIMPLEX_PARSE_OK;
	}
	else{
	  ret=SIMPLEX_ERROR;
	  break;
	}
  }

  // 发生了错误从这里走
  for (auto &it:tmp){
	delete it.second;
  }
  return ret;
}

static int simplex_parse_value(simplex_context *c, simplex_value *v){
  switch (*c->json) {
	case 't' : return simplex_parse_literal(c, v, "true", SIMPLEX_TRUE);
	case 'f' : return simplex_parse_literal(c,v,"false",SIMPLEX_FALSE);
	case 'n' : return simplex_parse_literal(c,v,"null", SIMPLEX_NULL);
	case '\"': return simplex_parse_string(c,v);
	case '\0': return SIMPLEX_ERROR; // 不允许空串
	case '[' : return simplex_parse_array(c, v);
	case '{' : return simplex_parse_object(c,v);
	default  : return simplex_parse_number(c,v);
  }
}

int simplex_parse(simplex_value* v,const char *json){
  simplex_context c{};
  int ret;
  assert(v!=nullptr);
  c.json=json;
  simplex_free(v);
  simplex_parse_whitespace(&c);
  if ((ret=simplex_parse_value(&c,v))==SIMPLEX_PARSE_OK){
	simplex_parse_whitespace(&c);
	if (*c.json!='\0'){
	  v->type=SIMPLEX_NULL;
	  ret=SIMPLEX_ERROR;
	}
  }
  return ret;
}

void simplex_free(simplex_value *v){
  assert(v!=nullptr);
  v->s="";
  v->a.clear();
  for (auto &it:v->o){
	delete it.second;
  }
  v->o.clear();
  v->type=SIMPLEX_NULL;
}

simplex_type simplex_get_type(const simplex_value *v){
  assert(v!=nullptr);
  return v->type;
}

bool simplex_get_boolean(const simplex_value *v){
  assert(v!=nullptr && (v->type==SIMPLEX_TRUE || v->type==SIMPLEX_FALSE));
  return v->type==SIMPLEX_TRUE;
}

void simplex_set_boolean(simplex_value *v, bool b){
  simplex_free(v);
  if (b) v->type=SIMPLEX_TRUE;
  else v->type=SIMPLEX_FALSE;
}

double simplex_get_number(const simplex_value *v){
  assert(v!=nullptr&&v->type==SIMPLEX_NUMBER);
  return v->n;
}

void simplex_set_number(simplex_value *v, double n){
  simplex_free(v);
  v->n=n;
  v->type=SIMPLEX_NUMBER;
}

const std::string& simplex_get_string(const simplex_value *v){
  assert(v!=nullptr&&v->type==SIMPLEX_STRING);
  return v->s;
}

size_t simplex_get_string_length(const simplex_value *v){
  assert(v!=nullptr && v->type==SIMPLEX_STRING);
  return v->s.size();
}

void simplex_set_string(simplex_value *v,const std::string &s){
  assert(v!=nullptr);
  simplex_free(v);
  v->type=SIMPLEX_STRING;
  v->s=s;
}

size_t simplex_get_array_size(const simplex_value *v){
  assert(v!=nullptr && v->type==SIMPLEX_ARRAY);
  return v->a.size();
}

simplex_value simplex_get_array_element(const simplex_value *v, size_t index){
  assert(v!=nullptr && v->type==SIMPLEX_ARRAY);
  assert(index<v->a.size());
  return v->a[index];
}

size_t simplex_get_object_size(const simplex_value *v){
  assert(v!=nullptr && v->type==SIMPLEX_OBJECT);
  return v->o.size();
}

std::string simplex_stringify_string(const std::string &s){
  std::string json=std::string(1,'\"');
  for (char ch:s){
	switch (ch){
	  case '\"':json+="\\\"";break;
	  case '\\':json+="\\\\";break;
	  case '\b':json+="\\b";break;
	  case '\f':json+="\\f";break;
	  case '\n':json+="\\n";break;
	  case '\r':json+="\\r";break;
	  case '\t':json+="\\t";break;
	  default:
		json+=ch;
	}
  }
  json+='\"';
  return json;
}

std::string simplex_stringify(const simplex_value* v){
  std::string json;
  bool flag=false;
  switch (v->type) {
	case SIMPLEX_NULL:
	  json+="null";break;
	case SIMPLEX_TRUE:
	  json+="true";break;
	case SIMPLEX_FALSE:
	  json+="false";break;
	case SIMPLEX_STRING:
	  json+=simplex_stringify_string(v->s);break;
	case SIMPLEX_NUMBER:
	  json+=std::to_string(v->n);break;
	case SIMPLEX_OBJECT:
	  json+="{";
	  flag=false;
	  for (auto &p:v->o){
		if (flag) json+=",";
		flag=true;
		json+=simplex_stringify_string(p.first);
		json+=":";
		json+=simplex_stringify(p.second);
	  }
	  json+="}";break;
	case SIMPLEX_ARRAY:
	  json+="[";
	  for (size_t i=0;i<v->a.size();i++){
		if (i>0) json+=",";
		json+=simplex_stringify(&(v->a[i]));
	  }
	  json+="]";break;
	default:
	  printf("ERROR!!\n");
  }
  return json;
}

