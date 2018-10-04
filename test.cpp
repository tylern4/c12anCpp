#include <iostream>
#include "algorithm.h"
#include "protoParticleReader.h"
#include "hipoReader.h"
#include "manager.h"
#include <vector>

using namespace std;

class test : public core::algorithm {

  public:
    virtual void init() {}
    virtual void terminate() {}
    virtual void processEvent();

};

void test::processEvent(){
  vector<hipoBase::protoParticle> *v = (vector<hipoBase::protoParticle>*)(getObject("protoParticles"));
  if( ! v ) return;

  //cout << " ++++ new event " << v->size() << endl;
  //for( hipoBase::protoParticle p : (*v) ){
    //cout << " patricle: " 
        //<< p.id <<" "
        //<< p.pid <<" "
        //<< p.charge <<" "
        //<< p.beta << endl;
  //}
}

int main() {

  core::manager *M = core::manager::instance();

  hipoBase::hipoReader reader( "/home/fbossu/Data/Analysis/RG-A/E10.6/skim8/4070_8.hipo");
  reader.open();
  M->addDataReader( &reader );

  hipoBase::protoParticleReader pr;
  test ta;

  M->addAlgorithm( &pr );
  M->addAlgorithm( &ta );

  M->run();

  return 0;

}


