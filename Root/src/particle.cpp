#include "particle.h"

#include "TDatabasePDG.h"
#include "TMath.h"

using namespace root;

ClassImp(particle)

particle* particle::getParticle( int pid, float px, float py, float pz){

  float m = TDatabasePDG::Instance()->GetParticle(pid)->Mass();
  float pt = TMath::Sqrt(px*px + py*py + pz*pz + m*m);
  return new particle( pid, px, py,pz,pt); 
}

