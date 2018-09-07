#include "reader.h"

#include "Track.h"
#include "Particle.h"
#include "Event.h"
#include <vector>


class Analysis {

  public:
    /*Analysis() {};*/
    Analysis( hipo::reader *h) { setHipoReader(h); }

    virtual void init();

    virtual bool processEvent() = 0;

    hipo::reader *getHipoReader(){ return hipoReader; }
    std::vector<void*>* getOutputList() { return outputList; }

  protected:
    hipo::reader *hipoReader;
    ReadParticle *pReader;
    ReadEvent *eReader;
    ReadTrack *tReader;

  private:
    std::vector<void*> *outputList;

    void setHipoReader( hipo::reader *hr ) { hipoReader = hr; }
};


