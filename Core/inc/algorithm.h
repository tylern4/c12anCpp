#ifndef _ALGORITHM_H
#define _ALGORITHM_H

#include "objContainer.h"
#include "dataReader.h"

namespace core {
  
  class algorithm {
    public:
      algorithm() {};
      void setObjContainer( objContainer *o) { _obj = o; }
      virtual void setDataReader( dataReader *r ) { _reader = r; }
      virtual dataReader* getDataReader() { return _reader; }

      virtual void init() = 0;
      virtual void processEvent() = 0;
      virtual void terminate() = 0;

      virtual void bookObject( const char*, void*);
      virtual void* getObject( const char*  );
      
      
    private:
      objContainer *_obj;
      dataReader *_reader;
  };

};

#endif

