#ifndef __SIMPLEX_JSON
#define __SIMPLEX_JSON

#include <string>
#include <vector>
#include <unordered_map>
typedef enum{
  SIMPLEX_NULL,
  SIMPLEX_FALSE,
  SIMPLEX_TRUE,
  SIMPLEX_NUMBER,
  SIMPLEX_ARRAY,
  SIMPLEX_OBJECT,
  SIMPLEX_STRING
}simplex_type;


struct simplex_value{
  std::string s;
  std::vector<simplex_value> a;
  double n;
  // 注意此处value用的指针
  std::unordered_map<std::string, simplex_value*> o;
  simplex_type type;
};

// 简单的errno
// TODO
enum {
  SIMPLEX_PARSE_OK=0,
  SIMPLEX_ERROR
};
//
//void simplex_init(simplex_value *v){
//  v->type=SIMPLEX_NULL;
//}

int simplex_parse(simplex_value *v, const char *json);
std::string simplex_stringify(const simplex_value* v);

void simplex_free(simplex_value *v);

simplex_type simplex_get_type(const simplex_value* v);



bool simplex_get_boolean(const simplex_value *v);
void simplex_set_boolean(simplex_value *v,int b);

double simplex_get_number(const simplex_value *v);
void simplex_set_number(simplex_value *v, double n0);

const std::string& simplex_get_string(const simplex_value *v);
size_t simplex_get_string_length(const simplex_value *v);
void simplex_set_string(simplex_value *v,const std::string &s);

size_t simplex_get_array_size(const simplex_value *v);
simplex_value simplex_get_array_element(const simplex_value *v,size_t index);

size_t simplex_get_object_size(const simplex_value *v);
// const std::string& simplex_get_object_key(const simplex_value *v,size_t index);
// size_t simplex_get_obejct_key_length(const simplex_value *v,size_t index);
// simplex_value* simplex_get_object_value(const simplex_value *v, size_t index);
#endif