#include <TLorentzVector.h>
#include <TVector3.h>
#include "reader.h"
#include "node.h"

class Particle {
  public: 
    int id;
    int pid;
    float chi2pid;
    float beta;
    TLorentzVector momentum;
    int charge;
    int status;
    TVector3 vertex;
};

class ReadParticle {
  public:
    ReadParticle( hipo::reader *);

    void setIt( unsigned int i ) { it = i; }
    unsigned int getIt() { return it; }

    Particle* next();
    Particle* getParticle(int);
    
  private:
    hipo::node<float>      *rp_beta  ;
    hipo::node<int8_t>    *rp_charge ;
    hipo::node<float>    *rp_chi2pid ;
    hipo::node<int32_t>     *rp_pid  ;
    hipo::node<float>       *rp_px   ;
    hipo::node<float>       *rp_py   ;
    hipo::node<float>       *rp_pz   ;
    hipo::node<int16_t>   *rp_status ;
    hipo::node<float>       *rp_vx   ;
    hipo::node<float>       *rp_vy   ;
    hipo::node<float>       *rp_vz   ;

    unsigned int it;
};

