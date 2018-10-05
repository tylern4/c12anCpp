#ifndef PARTICLE_H
#define PARTICLE_H

#include "TLorentzVector.h"

namespace root {
  class particle : public TLorentzVector {
    public: 
      int pid;
      virtual particle* getParticle( int, float, float, float);
    private:
      particle( int id, float x, float y, float z, float t) : TLorentzVector(x,y,z,t) { pid = id; }
  };
};

#endif 

