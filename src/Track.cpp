#include "Track.h"

ReadTrack::ReadTrack( hipo::reader *reader) {
        REC__Track_NDF = reader->getBranch<int16_t>("REC::Track","NDF");
   REC__Track_NDF_nomm = reader->getBranch<int16_t>("REC::Track","NDF_nomm");
       REC__Track_chi2 = reader->getBranch<float>("REC::Track","chi2");
  REC__Track_chi2_nomm = reader->getBranch<float>("REC::Track","chi2_nomm");
   REC__Track_detector = reader->getBranch<int8_t>("REC::Track","detector");
      REC__Track_index = reader->getBranch<int16_t>("REC::Track","index");
     REC__Track_pindex = reader->getBranch<int16_t>("REC::Track","pindex");
    REC__Track_px_nomm = reader->getBranch<float>("REC::Track","px_nomm");
    REC__Track_py_nomm = reader->getBranch<float>("REC::Track","py_nomm");
    REC__Track_pz_nomm = reader->getBranch<float>("REC::Track","pz_nomm");
          REC__Track_q = reader->getBranch<int8_t>("REC::Track","q");
     REC__Track_sector = reader->getBranch<int8_t>("REC::Track","sector");
     REC__Track_status = reader->getBranch<int16_t>("REC::Track","status");
    REC__Track_vx_nomm = reader->getBranch<float>("REC::Track","vx_nomm");
    REC__Track_vy_nomm = reader->getBranch<float>("REC::Track","vy_nomm");
    REC__Track_vz_nomm = reader->getBranch<float>("REC::Track","vz_nomm");

  it = 0;
}

Track* ReadTrack::next() {
  return getTrack(it++);
}

Track* ReadTrack::getTrack(int i) {
  if( i >= REC__Track_NDF->getLength() ) return NULL;
  Track *p = new Track();

  p->NDF =             REC__Track_NDF->getValue(i);
  p->NDF_nomm =   REC__Track_NDF_nomm->getValue(i);
  p->chi2 =           REC__Track_chi2->getValue(i);
  p->chi2_nomm = REC__Track_chi2_nomm->getValue(i);
  p->detector =   REC__Track_detector->getValue(i);
  p->index =         REC__Track_index->getValue(i);
  p->pindex =       REC__Track_pindex->getValue(i);
  p->px_nomm =     REC__Track_px_nomm->getValue(i);
  p->py_nomm =     REC__Track_py_nomm->getValue(i);
  p->pz_nomm =     REC__Track_pz_nomm->getValue(i);
  p->q =                 REC__Track_q->getValue(i);
  p->sector =       REC__Track_sector->getValue(i);
  p->status =       REC__Track_status->getValue(i);
  p->vx_nomm =     REC__Track_vx_nomm->getValue(i);
  p->vy_nomm =     REC__Track_vy_nomm->getValue(i);
  p->vz_nomm =     REC__Track_vz_nomm->getValue(i);

  return p;
}

