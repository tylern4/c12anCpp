#ifndef OBJCONTAINER_H
#define OBJCONTAINER_H

#include <map>
#include <string>

namespace core {

  class objContainer: public std::map<std::string,void*> { // to be changed with smart pointers
  };
};

#endif

