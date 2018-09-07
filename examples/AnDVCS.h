#include "Analysis.h"


class AnDVCS : public Analysis {

  public:
    AnDVCS( hipo::reader *h) : Analysis(h) { }

    virtual void init();

    virtual bool processEvent();


};


