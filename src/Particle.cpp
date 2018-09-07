#include "Particle.h"
#include <cmath>
#include <TDatabasePDG.h>

ReadParticle::ReadParticle( hipo::reader *reader) {
    rp_beta  = reader->getBranch<float>("REC::Particle","beta");
   rp_charge = reader->getBranch<int8_t>("REC::Particle","charge");
  rp_chi2pid = reader->getBranch<float>("REC::Particle","chi2pid");
     rp_pid  = reader->getBranch<int32_t>("REC::Particle","pid");
     rp_px   = reader->getBranch<float>("REC::Particle","px");
     rp_py   = reader->getBranch<float>("REC::Particle","py");
     rp_pz   = reader->getBranch<float>("REC::Particle","pz");
   rp_status = reader->getBranch<int16_t>("REC::Particle","status");
     rp_vx   = reader->getBranch<float>("REC::Particle","vx");
     rp_vy   = reader->getBranch<float>("REC::Particle","vy");
     rp_vz   = reader->getBranch<float>("REC::Particle","vz");

  it = 0;
}

Particle* ReadParticle::next() {
  return getParticle(it++);
}

Particle* ReadParticle::getParticle(int i) {
  if( i >= rp_beta->getLength() ) return NULL;
  Particle *p = new Particle();
  p->id = i;
  p->pid     = rp_pid->getValue(i);
  p->chi2pid = rp_chi2pid->getValue(i);
  p->charge     = rp_charge->getValue(i);
  p->beta     = rp_beta->getValue(i);
  p->status     = rp_status->getValue(i);
  p->pid     = rp_pid->getValue(i);
  p->vertex.SetXYZ( 
      rp_vx->getValue(i),
      rp_vy->getValue(i),
      rp_vz->getValue(i)
    );
  int pidformass = p->pid;
  TDatabasePDG *pdg = TDatabasePDG::Instance();
  if( ! pdg->GetParticle(p->pid) ) pidformass = 211; // use pion if pid from EB is unkown
  p->momentum.SetXYZT(
      rp_px->getValue(i),
      rp_py->getValue(i),
      rp_pz->getValue(i),
      sqrt(
        rp_px->getValue(i)*rp_px->getValue(i) +
        rp_py->getValue(i)*rp_py->getValue(i) +
        rp_pz->getValue(i)*rp_pz->getValue(i) +
        pdg->GetParticle(pidformass)->Mass()*pdg->GetParticle(pidformass)->Mass()
      )
  );
  return p;
}

