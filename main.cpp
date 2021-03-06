#include "simplexjson.h"
#include <cstdio>
#include <iostream>

int main(){
  simplex_value root;
  int ret=simplex_parse(&root, "1234");
  if (ret==SIMPLEX_PARSE_OK && root.type==SIMPLEX_NUMBER && root.n==1234){
    printf("OK\n");
  } else printf("error\n");
  return 0;
}