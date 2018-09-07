#include "reader.h"
#include "node.h"

#include <cmath>

class Track {
  public: 
     int16_t  NDF;
     int16_t  NDF_nomm;
     float       chi2;
     float    chi2_nomm;
     int8_t   detector;
     int16_t    index;
     int16_t   pindex;
     float    px_nomm;
     float    py_nomm;
     float    pz_nomm;
     int8_t         q;
     int8_t    sector;
     int16_t   status;
     float    vx_nomm;
     float    vy_nomm;
     float    vz_nomm;   
     
     float   getP(){   return sqrt(px_nomm*px_nomm+py_nomm*py_nomm+pz_nomm*pz_nomm); }
     float   getPT(){  return sqrt(px_nomm*px_nomm+py_nomm*py_nomm); }
     float   getPhi(){ return atan2( py_nomm, px_nomm ); }
     float   getTheta(){ return acos( pz_nomm/getP() ); }
};

class ReadTrack {
  public:
    ReadTrack( hipo::reader *);

    void setIt( unsigned int i ) { it = i; }
    unsigned int getIt() { return it; }

    Track* next();
    Track* getTrack(int);
    
  private:
    hipo::node<int16_t>         *REC__Track_NDF ;
    hipo::node<int16_t>    *REC__Track_NDF_nomm ;
    hipo::node<float>          *REC__Track_chi2 ;
    hipo::node<float>     *REC__Track_chi2_nomm ;
    hipo::node<int8_t>     *REC__Track_detector ;
    hipo::node<int16_t>       *REC__Track_index ;
    hipo::node<int16_t>      *REC__Track_pindex ;
    hipo::node<float>       *REC__Track_px_nomm ;
    hipo::node<float>       *REC__Track_py_nomm ;
    hipo::node<float>       *REC__Track_pz_nomm ;
    hipo::node<int8_t>            *REC__Track_q ;
    hipo::node<int8_t>       *REC__Track_sector ;
    hipo::node<int16_t>      *REC__Track_status ;
    hipo::node<float>       *REC__Track_vx_nomm ;
    hipo::node<float>       *REC__Track_vy_nomm ;
    hipo::node<float>       *REC__Track_vz_nomm ;

    unsigned int it;
};





