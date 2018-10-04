#include "algorithm.h"
#include "node.h"

namespace hipoBase {

  class protoParticle {
    public:
      int id;
      float beta;
      int charge;
      float chi2pid;
      int pid;
      float px;
      float py;
      float pz;
      int status;
      float vx;
      float vy;
      float vz;
  };

  class protoParticleReader : public core::algorithm {
    public:
      protoParticleReader() {};

      virtual void init();
      virtual void processEvent();
      virtual void terminate() {};
       
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

  };

};

