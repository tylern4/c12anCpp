#include "algorithm.h"

void core::algorithm::bookObject( const char* name, void* obj ){
  (*_obj)[name] = obj;
}

void* core::algorithm::getObject( const char* name){
  return (*_obj)[name];
}

