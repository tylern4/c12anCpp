#include "tparticleMaker.h"
#include "protoParticle.h"
using hipoBase::protoParticle;

#include "TClonesArray.h"
#include "particle.h"

#include <vector>
using std::vector;

using namespace root;

void tparticleMaker::init(){
  particles = new TMap();
}


void tparticleMaker::processEvent(){

  particles->Clear();

  vector<protoParticle> *v = (vector<protoParticle>*)(getObject("protoParticles"));
  if( ! v ) return;
  

  for( auto p : (*v)) {
    if( particles->GetValue(p.pid) == NULL ){
      particles->Add(p.pid, new TClonesArray("particle"));

      particles->GetValue(p.pid)->Add(
        new particle( p.pid, p.px, p.py, p.pz ) 
      );
    }
    else {
      particles->GetValue(p.pid)->Add(
        new particle( p.pid, p.px, p.py, p.pz ) 
      );
    }
  }

  bookObject( "particles", particles );
}

