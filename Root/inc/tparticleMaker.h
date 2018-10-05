#ifndef _ROOT_PARTICLEMAKER_H
#define _ROOT_PARTICLEMAKER_H

#include "algorithm.h"

#include "TMap.h"

namespace root {

  class tparticleMaker : public core::algorithm {
   
    public:
      virtual void init();
      virtual void processEvent();
      virtual void terminate() {} 

    private:
      TMap *particles;

  };
};

#endif

