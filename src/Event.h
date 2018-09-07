#include "reader.h"
#include "node.h"

class Event {
  public:
    float BCG;
    float time;
    int category;
    short helicity;
    double LT;
    int NEVENT;
    int NPGP;
    int NRUN;
    float PTIME;
    float RFTime;
    float STTime;
    long TRG;
    short TYPE;
};

class ReadEvent {
  public:
    ReadEvent( hipo::reader * );
    Event *getEvent();
  private:
   hipo::node<float>         *REC__Event_BCG ;
   hipo::node<float>     *REC__Event_EVNTime ;
   hipo::node<int16_t>     *REC__Event_EvCAT ;
   hipo::node<int8_t>      *REC__Event_Helic ;
   hipo::node<double>         *REC__Event_LT ;
   hipo::node<int32_t>    *REC__Event_NEVENT ;
   hipo::node<int16_t>      *REC__Event_NPGP ;
   hipo::node<int32_t>      *REC__Event_NRUN ;
   hipo::node<float>       *REC__Event_PTIME ;
   hipo::node<float>      *REC__Event_RFTime ;
   hipo::node<float>      *REC__Event_STTime ;
   hipo::node<int64_t>       *REC__Event_TRG ;
   hipo::node<int8_t>       *REC__Event_TYPE ;
};

