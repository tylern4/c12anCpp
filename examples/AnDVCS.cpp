#include "AnDVCS.h"

#include <TNtuple.h>
#include <TH2F.h>
#include <TH1F.h>
#include <TDatabasePDG.h>
#include <TLorentzVector.h>
#include <TVector3.h>

#include <iostream>
#include <typeinfo>
#include <vector>
#include <unordered_map>

//Analysis() {
//}

void AnDVCS::init() {
  Analysis::init();
  // dvcs
  TNtuple *dvcs = new TNtuple("dvcs","dvcs","eP:eTheta:ePhi:pP:pTheta:pPhi:gP:gTheta:gPhi:MMepg:MMep:MMeg:MMpg:Q2:xB:Helicity:phiTrento:t:W2");
  getOutputList()->push_back( dvcs );
  
  TNtuple *pi0 = new TNtuple("pi0","pi0",
    "eP:eTheta:ePhi:pP:pTheta:pPhi:g1P:g1Theta:g1Phi:g2P:g2Theta:g2Phi:MMgg:MMepgg:MMep:MMegg:MMpgg:Q2:xB:Helicity:phiTrento:t:W2");
  getOutputList()->push_back( pi0 );

  TH2F *h = new TH2F("h","theta vs phi", 180,0,180, 360,-180,180);
  getOutputList()->push_back( h );

  TH1F *h1 = new TH1F("htrigger","trigger bits",32,0,32);
  getOutputList()->push_back( h1 );

}


bool AnDVCS::processEvent() {
  if( ! hipoReader ) return false;

  // retrive output objects
  // ---------------------- 
  TNtuple *nt = static_cast<TNtuple*>(getOutputList()->at(0));
  TNtuple *pi0 = static_cast<TNtuple*>(getOutputList()->at(1));
  TH2F *h = static_cast<TH2F*>(getOutputList()->at(2));
  TH1F *htrigger = static_cast<TH1F*>(getOutputList()->at(3));

 
  
  // event information
  Event *event = eReader->getEvent();
  if( ! event ){ return false; }
  
  // fill triggers
  for( int i=0;i<32;i++){
    if( (event->TRG & (1<<i) ) > 0 ) htrigger->Fill(i);
  }

  // make track maps
  // ---------------
  std::unordered_map<int,Track> tracks;
  Track *t;
  while( t = tReader->next() ){
    tracks[ t->pindex ] = *t;
  }
  tReader->setIt(0);
  if( tracks.size() == 0 ) return false;

  // vectors for identified paritcles
  std::vector<Particle> electrons;
  std::vector<Particle> protons;
  std::vector<Particle> photons;
  std::unordered_map<int,std::vector<Particle>> particles;
  particles[11]   = electrons;
  particles[22]   = photons;
  particles[2212] = protons;

  // fill the particle vectors
  // -------------------------
  Particle *p;
  while( p = pReader->next() ){
    if( particles.find( p->pid) != particles.end() ){
      particles[p->pid].push_back( *p );
      
      // test with histograms
      if( p->status >= 4000 ) h->Fill( p->momentum.Theta()/M_PI*180., p->momentum.Phi()/M_PI*180. );
    }
  } 
  pReader->setIt(0);

  // fill the output of tracks
  //trks->Fill( t->getP(), t->getPT(), t->vz_nomm, t->getPhi(), t->getTheta(), t-> 

  // look for DVCS events: we want at least 1 electron, 1 proton and 1 gamma
  if( particles[11].size()<1) return false;
  if( particles[22].size()<1) return false;
  if( particles[2212].size()<1) return false;
 

  // initial state
  // -------------
  double massElectron = TDatabasePDG::Instance()->GetParticle(11)->Mass();
  double massProton   = TDatabasePDG::Instance()->GetParticle(2212)->Mass();
  // incoming electron
  TLorentzVector inE( 0., 0., 10.594, sqrt( 10.594*10.594 + massElectron*massElectron ) );
  // target proton
  TLorentzVector inP( 0., 0., 0., massProton);


  // form DVCS candidates
  // loop over electrons, then protons and then photons
  // --------------------------------------------------
  float vals[19]; // array to hold values for ntuple filling

  // loop over electrons
  for( auto E : particles[11] ){
    if( E.charge > 0 ) continue;

    TLorentzVector Q = inE - E.momentum;
    float Q2 = -Q.Mag2();
    float xB = Q2 / (2*massProton*(inE.T()-E.momentum.T()));

    if( Q2 < 1. ) continue; // Q^2 cut

    TLorentzVector w = Q + inP;
    float W2 = w.Mag2();

    // loop over protons
    for( auto P : particles[2212] ){
      if( P.charge < 0 ) continue;
    
      TLorentzVector T = P.momentum - inP;  
      float t = T.Mag2();
 
      // cut on proton track quality 
      if( tracks[P.id].chi2/tracks[P.id].NDF>6) continue;

      // loop over photons
      //for( auto G : particles[22] ){
      for( auto G = particles[22].begin(); G != particles[22].end(); ++G ){
      //for( auto G = photons.begin(), end = photons.end(); G != end; ++G ){
        //std::cout << std::type_info(G) <<std::endl;

        // create missing mass lorentz vectors
        TLorentzVector MMepg = E.momentum + P.momentum + G->momentum - inE - inP;
        TLorentzVector MMep = E.momentum + P.momentum - inE - inP;
        TLorentzVector MMeg = E.momentum + G->momentum - inE - inP;
        TLorentzVector MMpg = P.momentum + G->momentum - inE - inP;

        // compute phi Trento
        // ------------------
        
        // normal vector to the plane E, E'
        TVector3 lepPlane = inE.Vect().Cross(E.momentum.Vect());

        // normal vector to the plane Q, P'
        TVector3 hadPlane = Q.Vect().Cross(P.momentum.Vect());

        // phi trento
        float s = lepPlane.Cross(hadPlane).Dot(Q.Vect());
        float phiTrento = lepPlane.Angle( hadPlane );
        if( s < 0. ) phiTrento += M_PI;

        // fill ntuple
        vals[0] = E.momentum.P();
        vals[1] = E.momentum.Theta();
        vals[2] = E.momentum.Phi();
        vals[3] = P.momentum.P();
        vals[4] = P.momentum.Theta();
        vals[5] = P.momentum.Phi();
        vals[6] = G->momentum.P();
        vals[7] = G->momentum.Theta();
        vals[8] = G->momentum.Phi();
        vals[9] = MMepg.Mag2();
        vals[10] = MMep.Mag2();
        vals[11] = MMeg.Mag2();
        vals[12] = MMpg.Mag2();
        vals[13] = Q2;
        vals[14] = xB;
        vals[15] = (float)event->helicity;
        vals[16] = phiTrento;
        vals[17] = t;
        vals[18] = W2;
        nt->Fill(vals);
        
        // second loop over photons
        //for( auto G2 = std::next(G), end = photons.end(); G2 != end; ++G2 ){
        for( auto G2 = std::next(G); G2 != particles[22].end(); ++G2 ){
          //if( *G2 ) continue;
          TLorentzVector MMgg = G->momentum + G2->momentum;
          TLorentzVector MMepgg = E.momentum + P.momentum + MMgg - inE - inP;
          TLorentzVector MMegg = E.momentum + MMgg - inE - inP;
          TLorentzVector MMpgg = P.momentum + MMgg - inE - inP;
          float ggv[23];
          ggv[0] = E.momentum.P();
          ggv[1] = E.momentum.Theta();
          ggv[2] = E.momentum.Phi();
          ggv[3] = P.momentum.P();
          ggv[4] = P.momentum.Theta();
          ggv[5] = P.momentum.Phi();
          ggv[6] = G->momentum.P();
          ggv[7] = G->momentum.Theta();
          ggv[8] = G->momentum.Phi();
          ggv[9] = G2->momentum.P();
          ggv[10] = G2->momentum.Theta();
          ggv[11] = G2->momentum.Phi();
          ggv[12] = MMgg.Mag();
          ggv[13] = MMepgg.Mag2();
          ggv[14] = MMep.Mag2();
          ggv[15] = MMegg.Mag2();
          ggv[16] = MMpgg.Mag2();
          ggv[17] = Q2;
          ggv[18] = xB;
          ggv[19] = (float)event->helicity;
          ggv[20] = phiTrento;
          ggv[21] = t;
          ggv[22] = W2;
          pi0->Fill(ggv);
        }
      }// end photon loop
    }// end proton loop
  }// end electron loop

  return true;
}

