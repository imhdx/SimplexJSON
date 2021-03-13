#include <cstdio>
#include "simplexjson.h"
#include <iostream>

int main(){
  simplex_value v;
  simplex_free(&v);
  std::string json="{\"123\":123, \"345\":\"12222\" }";
  std::cout<<json<<std::endl;
  int ret=simplex_parse(&v, json.c_str());
  if (ret==SIMPLEX_PARSE_OK){
	std::cout<<simplex_stringify(&v)<<std::endl;
  }
  else{
	printf("ERROR!\n");
  }
  return 0;
}