#include "hipoReader.h"

using namespace hipoBase;

hipoReader::hipoReader( const char* name ){
  _filename = name;
  _reader = new hipo::reader();
}

void hipoReader::open(){
  _reader->open(_filename);
}

void hipoReader::close(){
  //_reader->close();
}

void* hipoReader::next() {
   if( _reader->next() == false ) return NULL;
  return _reader;
}

