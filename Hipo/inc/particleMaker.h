#ifndef PARTICLEMAKER_H
#define PARTICLEMAKER_H

#include "algorithm.h"

namespace hipoBase {

  class particleMaker : public core::algorithm {
    public:
      virtual void init() {};
      virtual void processEvent();
      virtual void terminate(){};
  };
};


#endif


