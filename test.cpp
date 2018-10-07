#include <iostream>
#include "algorithm.h"
#include "protoParticleReader.h"
#include "tparticleMaker.h"
#include "hipoReader.h"
#include "manager.h"
#include <vector>
//#include <unordered_map>
#include <map>
#include "particle.h"
using namespace root;

#include "TClonesArray.h"

using namespace std;

class test : public core::algorithm {

  public:
    virtual void init() {}
    virtual void terminate() {}
    virtual void processEvent();

};

void test::processEvent(){
  //unordered_map<int,vector<hipoBase::protoParticle>> *map = (unordered_map<int,vector<hipoBase::protoParticle>>*)(getObject("particles"));
  map<int,TClonesArray*> *particles = (map<int,TClonesArray*>*)getObject("particles");
  if( ! particles ) return;

  if( particles->find(11) == particles->end() ){
    return;
  }
  else {
    cout << " found electrons! " << endl;
    TClonesArray *electrons = (*particles)[11];
    for( int i=0;i<electrons->GetSize(); i++){
      //for( auto p : (*particles)[11]){
      cout << " patricle: " 
        << ((particle*)electrons->At(i))->pid <<" "
        << ((particle*)electrons->At(i))->P() << endl;

    }
  }

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

  hipoBase::hipoReader reader( "/home/bossu/Data/4020_8.hipo");
  reader.open();
  M->addDataReader( &reader );

  hipoBase::protoParticleReader pr;
  root::tparticleMaker pm;
  test ta;

  M->addAlgorithm( &pr );
  M->addAlgorithm( &pm );
  M->addAlgorithm( &ta );

  M->run();

  return 0;

}


