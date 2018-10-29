cmake_minimum_required(VERSION 3.5)
project(c12anCpp)
set(VERSION 0.1)

list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
find_package(ROOT REQUIRED COMPONENTS
  EG
  Core
  Imt
  RIO
  Net
  Hist
  Graf
  Graf3d
  Gpad
  ROOTVecOps
  Tree
  TreePlayer
  Rint
  Postscript
  Matrix
  Physics
  MathCore
  Thread
  MultiProc
  ROOTDataFrame
)
include(${ROOT_USE_FILE})
set(CMAKE_CXX_FLAGS "${ROOT_CXX_FLAGS}")

set(CMAKE_MODULE_PATH
   ${CMAKE_MODULE_PATH}
   ${PROJECT_SOURCE_DIR}/cmake)


link_directories($ENV{HIPO}/lib)
include_directories(Core Hip Roo Core/inc Hipo/inc Root/inc $ENV{HIPO}/Hipo)
add_subdirectory(Core)
add_subdirectory(Hipo)
add_subdirectory(Root)

add_executable(example test.cpp)
target_link_libraries(example ${ROOT_LIBRARIES} c12Core hipoBase testRoot hipocpp)
