#include "Analysis.h"

#include <TNtuple.h>
#include <TH2F.h>
#include <TDatabasePDG.h>
#include <TLorentzVector.h>
#include <TVector3.h>

#include <iostream>
#include <vector>
#include <unordered_map>

//Analysis() {
//}

void Analysis::init() {
  outputList = new std::vector<void*>();
  pReader = new ReadParticle( this->hipoReader );
  eReader = new ReadEvent( this->hipoReader );
  tReader = new ReadTrack( this->hipoReader );
}

