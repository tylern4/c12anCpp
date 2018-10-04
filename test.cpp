#include <iostream>
#include "algorithm.h"
#include "protoParticleReader.h"
#include "particleMaker.h"
#include "hipoReader.h"
#include "manager.h"
#include <vector>
#include <unordered_map>

using namespace std;

class test : public core::algorithm {

  public:
    virtual void init() {}
    virtual void terminate() {}
    virtual void processEvent();

};

void test::processEvent(){
  unordered_map<int,vector<hipoBase::protoParticle>> *map = (unordered_map<int,vector<hipoBase::protoParticle>>*)(getObject("particles"));
  if( ! map ) return;

  if( map->find(11) == map->end() ){
    return;
  }
  else {
    cout << " found electrons! " << endl;
    for( auto p : (*map)[11]){
      cout << " patricle: " 
        << p.id <<" "
        << p.pid <<" "
        << p.charge <<" "
        << p.beta << endl;

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
  hipoBase::particleMaker pm;
  test ta;

  M->addAlgorithm( &pr );
  M->addAlgorithm( &pm );
  M->addAlgorithm( &ta );

  M->run();

  return 0;

}


