//***********************************************************************
//======================================================================= 
// Inspired from code by HIPO 3.1 io library
// Modify the processEvent of your Analysis object
// Date: 
// author: fbossu
//***********************************************************************
#include <cstdlib>
#include <iostream>

#include "reader.h"
#include "node.h"

#include <TFile.h>

//#include "src/Analysis.h"
#include "AnDVCS.h"

#include <cmath>
#include <vector>
#include <string>

#include <TNtuple.h>
#include <TH2F.h>

int main(int argc, char** argv) {
  std::cout << " Analysis program: it reads HIPO files and save ROOT histo/ntuples " << std::endl;

  std::vector<std::string> inputFiles;
  char inputFileName[256];
  if(argc>1) {
    for( int i=1;i<argc;i++){
      sprintf(inputFileName,"%s",argv[i]);
      std::cout << inputFileName << std::endl;
      inputFiles.push_back( inputFileName ) ;
    }
  } else {
    std::cout << " *** please provide a file name..." << std::endl;
    exit(0);
  }

  TFile *fout = TFile::Open("test.root","recreate");

  hipo::reader  reader;

  AnDVCS myAn( &reader );
  reader.open(inputFiles.at(0).c_str()); // open the fist file to be able to get the branches correctly
  myAn.init(); // remember that call the reader open before init

  // set the TDirectory location for the output objects. TODO: include it in the init method?
  ((TNtuple*)myAn.getOutputList()->at(0))->SetDirectory(fout);
  ((TNtuple*)myAn.getOutputList()->at(1))->SetDirectory(fout);
  ((TH2F*)myAn.getOutputList()->at(2))->SetDirectory(fout);
  //----------------------------------------------------
  //--  Main LOOP running through events
  //----------------------------------------------------
  for( auto inputFile : inputFiles ){
    std::cout << inputFile << std::endl;
    reader.open(inputFile.c_str());
    int entry = 0;
    while(reader.next()==true){
      entry++;
      if( entry%10000 == 0) std::cout << "event # " << entry << std::endl;
      //std::cout << "event # " << entry << std::endl;
      //if( entry > 10000 ) break;

      myAn.processEvent();
    }
  }

  //((TNtuple*)myAn.getOutputList()->at(0))->SaveAs("test.root");
  fout->Write();
  fout->Close();
   
  return 0;
}


