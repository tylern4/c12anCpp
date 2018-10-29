cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${ROOT_CXX_FLAGS}" )
include_directories(inc)

add_library(testRoot SHARED
  src/particle.cpp
  src/particleMaker.cpp
  )
target_link_libraries(testRoot ${ROOT_LIBRARIES})
