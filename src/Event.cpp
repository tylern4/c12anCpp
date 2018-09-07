#include "Event.h"

ReadEvent::ReadEvent(hipo::reader *reader){
       REC__Event_BCG = reader->getBranch<float>("REC::Event","BCG");
   REC__Event_EVNTime = reader->getBranch<float>("REC::Event","EVNTime");
     REC__Event_EvCAT = reader->getBranch<int16_t>("REC::Event","EvCAT");
     REC__Event_Helic = reader->getBranch<int8_t>("REC::Event","Helic");
        REC__Event_LT = reader->getBranch<double>("REC::Event","LT");
    REC__Event_NEVENT = reader->getBranch<int32_t>("REC::Event","NEVENT");
      REC__Event_NPGP = reader->getBranch<int16_t>("REC::Event","NPGP");
      REC__Event_NRUN = reader->getBranch<int32_t>("REC::Event","NRUN");
     REC__Event_PTIME = reader->getBranch<float>("REC::Event","PTIME");
    REC__Event_RFTime = reader->getBranch<float>("REC::Event","RFTime");
    REC__Event_STTime = reader->getBranch<float>("REC::Event","STTime");
       REC__Event_TRG = reader->getBranch<int64_t>("REC::Event","TRG");
      REC__Event_TYPE = reader->getBranch<int8_t>("REC::Event","TYPE");
}

Event *ReadEvent::getEvent() {
  if( REC__Event_TRG->getLength()==0 ) return NULL;

  Event *e = new Event();
  e->BCG      =     REC__Event_BCG->getValue(0); 
  e->time     = REC__Event_EVNTime->getValue(0);
  e->category =   REC__Event_EvCAT->getValue(0);
  e->helicity =   REC__Event_Helic->getValue(0);
  e->LT       =      REC__Event_LT->getValue(0);
  e->NEVENT   =  REC__Event_NEVENT->getValue(0);
  e->NPGP     =    REC__Event_NPGP->getValue(0);
  e->NRUN     =    REC__Event_NRUN->getValue(0);
  e->PTIME    =   REC__Event_PTIME->getValue(0);
  e->RFTime   =  REC__Event_RFTime->getValue(0);
  e->STTime   =  REC__Event_STTime->getValue(0);
  e->TRG      =     REC__Event_TRG->getValue(0);
  e->TYPE     =    REC__Event_TYPE->getValue(0);
  return e;
}
