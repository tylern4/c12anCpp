#ifndef _ROOT_PARTICLEMAKER_H
#define _ROOT_PARTICLEMAKER_H

#include "algorithm.h"

#include <map>

class TClonesArray;

namespace root {

  class tparticleMaker : public core::algorithm {
   
    public:
      virtual void init();
      virtual void processEvent();
      virtual void terminate() {} 

    private:
      std::map<int,TClonesArray*> *particles;

  };
};

#endif

