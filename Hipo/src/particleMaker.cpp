#include "particleMaker.h"
#include "protoParticleReader.h"
#include <unordered_map>
#include <vector>

using namespace hipoBase;
using namespace std;

void particleMaker::processEvent(){
  vector<protoParticle> *v = (vector<protoParticle>*)(getObject("protoParticles"));
  
  if( ! v ) return;

  unordered_map<int,vector<protoParticle>> *map = new unordered_map<int,vector<protoParticle>>();

  for( auto p : (*v)) {
    if( map->find(p.pid) == map->end() ){
      (*map)[p.pid] = vector<protoParticle>();
      (*map)[p.pid].push_back(p);
    }
    else {
      (*map)[p.pid].push_back(p);
    }
  }

  bookObject( "particles", map );
  
}

