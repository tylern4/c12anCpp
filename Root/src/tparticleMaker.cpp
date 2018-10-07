#include "tparticleMaker.h"
#include "protoParticle.h"
using hipoBase::protoParticle;

#include "TClonesArray.h"
#include "TDatabasePDG.h"
#include "particle.h"

#include <vector>
using std::vector;

using namespace root;

void tparticleMaker::init(){
  particles = new std::map<int,TClonesArray*>();
}


void tparticleMaker::processEvent(){

  particles->clear();

  vector<protoParticle> *v = (vector<protoParticle>*)(getObject("protoParticles"));
  if( ! v ) return;
  

  for( auto p : (*v)) {
    if( particles->find(p.pid) == particles->end() ){
printf("debug 0 ");
      (*particles)[p.pid]= new TClonesArray("particle");
printf("debug 1 ");

      (*particles)[p.pid]->Add(
        particle::getParticle( p.pid, p.px, p.py, p.pz ) 
      );
    }
    else {
      (*particles)[p.pid]->Add(
        particle::getParticle( p.pid, p.px, p.py, p.pz ) 
      );
    }
  }

  //for( auto p : particles ){
    
    bookObject( "particles", particles );
    //}
}

