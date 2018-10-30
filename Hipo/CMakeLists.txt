cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${ROOT_CXX_FLAGS}" )
include_directories(inc)

add_library(hipoBase SHARED
  src/hipoReader.cpp
  src/protoParticleReader.cpp
  )

target_link_libraries(hipoBase c12Core hipocpp)
