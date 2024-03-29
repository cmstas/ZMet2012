#ifndef Z_looper_h
#define Z_looper_h

#include "TFile.h"
#include "TTree.h"
#include "TMath.h"
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include <vector>
#include <map>
#include <fstream>
#include "Math/LorentzVector.h"
//#include "Math/PxPyPzE4D.h"

using namespace std;

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;
typedef vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > VofP4;

class TChain;

class Z_looper
{
 public:
  Z_looper() {};
  ~Z_looper() {
    delete babyFile_;
    delete babyTree_;
  };

  void MakeBabyNtuple (const char *);
  void InitBabyNtuple ();
  void FillBabyNtuple ();
  void CloseBabyNtuple ();
  void ScanChain (TChain*, const char*, bool isData, bool calculateTCMET = false,
                  int my_nEvents = -1, float kFactor = 1.);
  void bookHistos();
  bool isGoodTrack(int, bool usePV = false);
  float deltaPhi( float phi1 , float phi2);
  void fillUnderOverFlow(TH1F *h1, float value, float weight);
  void fillHistos(TH1F *h1[4],    float value, float weight, int myType);
  void fillHistos(TH1F *h1[4][4], float value, float weight, int myType, int nJetsIdx);
  float PassGenSelection( bool isData );
  float GenWeight( bool isData , char* prefix, int metcut );
  float getMetError(  vector<int> goodMuonIndices );
  float getMetError_claudio(  vector<int> goodMuonIndices );
  float gluinoPairCrossSection( float gluinomass );

  bool    initialized;
  TH1D*   gg_xsec_hist;
  TFile*  gg_xsec_file;

 private:
                
  //ntuple, file
  TFile *babyFile_;
  TTree *babyTree_;
    
  //histos

  VofP4 pujets_;
  Int_t npujets_;

  // event stuff
  char    dataset_[500];
  UInt_t  run_;
  Int_t   st_;
  Int_t   goodrun_;
  UInt_t  lumi_;
  UInt_t  event_;
  Int_t   leptype_;
  Int_t   ecaltype_;
  Float_t xsec_;
  Float_t eveto1_;
  Float_t hveto1_;
  Float_t eveto2_;
  Float_t hveto2_;
  Int_t   nGoodVertex_;
  Float_t weight_;
  Float_t ptgen1_;
  Float_t ptgen2_;
  Float_t trgeff_;
  Float_t pthat_;
  Float_t qscale_;
  Float_t mllgen_;
  Float_t vtxweight_;
  Float_t maxemf_;
  Float_t dpdm_;
  Float_t metError_;
  Float_t metErrorC_;
  Float_t eff0_;
  Float_t eff100_;
  Float_t eff200_;
  Float_t eff300_;
  Int_t   ssmu1_;
  Int_t   ssmu2_;
  Int_t   id1_;
  Int_t   id2_;
  Int_t   nlep_;
  Int_t   nmu_;
  Int_t   nel_;
  Int_t   nbvz_;
  Int_t   nbvzres_;
  Float_t mjj_;
  Float_t mbb_;
  Float_t mjjup_;
  Float_t mjjdn_;
  Float_t ml_;
  Float_t mg_;
  Float_t x_;
  Float_t btagweight_;
  Float_t btagweightup_;
  Float_t unclustered_;
  Float_t unclustered_x_;
  Float_t unclustered_y_;
  Int_t   ngenels_;
  Int_t   ngenmus_;
  Int_t   ngentaus_;
  Int_t   ngenleps_;
  Int_t   ngennue_;
  Int_t   ngennum_;
  Int_t   ngennut_;
  Int_t   ngennu_;
  Int_t   njets40up_;
  Int_t   njets40dn_;
  Float_t ht40up_;
  Float_t ht40dn_;
  Int_t   zdilep_;
  Float_t drll_;
  Float_t dphill_;
  Float_t drblmin_;
  Float_t st30_;
  Float_t st40_;

  Int_t   extraz_;
  Int_t   extrag_;

  Float_t m1_;
  Float_t m2_;
  Float_t m3_;
  Int_t   zveto_;
  Int_t   nmuss_;
  Int_t   nextramu_;
  Int_t   nhyp_;

  Float_t pfmett1new_;
  Float_t pfmett1newphi_;

  Int_t   el1nomu_;
  Int_t   el2nomu_;
  Int_t   el1nomuss_;
  Int_t   el2nomuss_;

  Int_t   id3_;
  Int_t   id4_;
  Int_t   id5_;
  Int_t   id6_;

  Float_t m13_;
  Float_t m23_;
  Float_t m14_;
  Float_t m24_;
  Float_t m34_;

  LorentzVector*  lep1_;
  LorentzVector*  lep2_;
  LorentzVector*  pflep1_;
  LorentzVector*  pflep2_;
  LorentzVector*  lep3_;
  LorentzVector*  lep4_;
  LorentzVector*  lep5_;
  LorentzVector*  lep6_;
  LorentzVector*  w_;
  LorentzVector*  dilep_;
  LorentzVector*  dileppf_;
  LorentzVector*  jet1_; 
  LorentzVector*  jet2_; 
  LorentzVector*  jet3_; 
  LorentzVector*  jet4_; 
  LorentzVector*  jet5_; 
  LorentzVector*  jet6_; 
  LorentzVector*  jet7_; 
  LorentzVector*  jet8_; 
  LorentzVector*  subthreshjetup1_; 
  LorentzVector*  subthreshjetup2_; 
  LorentzVector*  bjet1_; 
  LorentzVector*  bjet2_; 
  LorentzVector*  bjet3_; 
  LorentzVector*  bjet4_; 
  LorentzVector*  genz_; 
  LorentzVector*  gent_; 
  LorentzVector*  gentbar_; 
  LorentzVector*  genttbar_; 

  Float_t tche1_;
  Float_t tche2_;
  Float_t tche3_;
  Float_t tche4_;
  Float_t tche5_;
  Float_t tche6_;
  Float_t tche7_;
  Float_t tche8_;

  Float_t csv1_;
  Float_t csv2_;
  Float_t csv3_;
  Float_t csv4_;
  Float_t csv5_;
  Float_t csv6_;
  Float_t csv7_;
  Float_t csv8_;

  Float_t jetunc1_;
  Float_t jetunc2_;
  Float_t jetunc3_;
  Float_t jetunc4_;
  Float_t jetunc5_;
  Float_t jetunc6_;
  Float_t jetunc7_;
  Float_t jetunc8_;

  Int_t jetgenb1_;
  Int_t jetgenb2_;
  Int_t jetgenb3_;
  Int_t jetgenb4_;
  Int_t jetgenb5_;
  Int_t jetgenb6_;
  Int_t jetgenb7_;
  Int_t jetgenb8_;

  Int_t   isdata_;
  Int_t   el1tv_;
  Int_t   el2tv_;
  Float_t lljj_;
  Float_t jj_;
  Float_t l1jj_;
  Float_t l2jj_;
  Float_t j1ll_;
  Float_t j2ll_;
  Float_t l1j1_;
  Float_t l2j2_;
  Float_t l1j2_;
  Float_t l2j1_;
  Float_t rho_;

  // genmet stuff
  Float_t genmet_;
  Float_t genmetcustom_;
  Float_t genmetphi_;
  Float_t gensumet_;

  // pfmet stuff
  Float_t minmet_;
  Float_t trkmet_;
  Float_t trkmetphi_;
  Float_t trksumet_;

  Float_t pfmet_;
  Float_t pfmett1_;
  Float_t pfmett1phi_;
  Float_t pfmetUp_;
  Float_t pfmetDn_;
  Float_t pfmetphi_;
  Float_t pfsumet_;

  //pfmuon stuff
  Int_t   npfmuons_;
  Int_t   nmatchedpfmuons_;
  Float_t ptll_pf_;
  Float_t ptlt_pf_;

  // calomet stuff
  Float_t met_;
  Float_t metphi_;
  Float_t sumet_;

  Float_t ptlltrk_;
  Float_t ptllgen_;
  Float_t ptltgen_;
  Float_t ptlttrk_;
  Float_t ptllgfit_;
  Float_t ptltgfit_;

  // muon-corrected calomet stuff
  Float_t mumet_;
  Float_t mumetphi_;
  Float_t musumet_;

  // muon-corrected JES calomet stuff
  Float_t mujesmet_;
  Float_t mujesmetphi_;
  Float_t mujessumet_;

  // tcmet stuff
  Float_t dphixmet_;
  Float_t metPar_;
  Float_t metPerp_;
  Float_t dphijetmet_;
  Float_t tcmet_;
  Float_t tcmetphi_;
  Float_t tcsumet_;

  Float_t tcmetNew_;
  Float_t tcmetphiNew_;
  Float_t tcsumetNew_;
  Float_t tcmetcor_;
  Float_t pfmetcor_;
  Float_t dilmasscor_;

  // jet stuff
  Int_t   failjetid_;
  Int_t   nJets_;
  Int_t   nJetsOld_;
  Int_t   nJetsRes_;
  Int_t   nJetsUp_;
  Int_t   nJetsDn_;
  Int_t   nJPT_;
  Int_t   nJets40_;
  Float_t sumJetPt_;
  Float_t sumJetPt10_;
  Float_t vecJetPt_;
  Int_t   nbtags_;
  Int_t   nbl_;
  Int_t   nbm_;
  Int_t   nbcsvm_;
  Int_t   nbcsvl_;
  Int_t   nbcsvlm_;
  Int_t   nbcsvt_;
  Float_t ht30_;
  Float_t ht40_;
  Float_t jzb_;

  //electron-matched jet stuff
  Float_t drjet_ll_;
  Float_t jetpt_ll_;
  Int_t   pfjetid_ll_;
  Float_t drjet_lt_;
  Float_t jetpt_lt_;
  Int_t   pfjetid_lt_;

  //leading jet stuff
  Float_t jetmax_pt_;
  Float_t jetmax_dphimet_;

  //Z stuff
  Int_t   passz_;
  Int_t   pdgid_;
  Int_t   idll_;
  Int_t   idlt_;
  Float_t ptll_;
  Float_t ptlt_;
  Float_t pterrll_;
  Float_t pterrlt_;
  Float_t etall_;
  Float_t etalt_;
  Float_t phill_;
  Float_t philt_;
  Float_t dilmass_;
  Float_t dilmasspf_;
  Float_t dilpt_;
  Int_t   flagll_;
  Int_t   flaglt_;

  Int_t   bptx_;       
  Int_t   bsc_;        
  Int_t   beamhalo_;   
  Int_t   goodvtx_;    
  Int_t   goodtrks_;   

  Int_t el27_;
  Int_t mm_;
  Int_t mmtk_;
  Int_t me_;
  Int_t em_;
  Int_t mu_;
  Int_t mu21_;
  Int_t ee_;
  Int_t eldup_;

  Float_t mlb1_;
  Float_t mlb2_;
  Float_t mlbt1_;
  Float_t mlbt2_;
  Float_t mlbmin_;
  Float_t mlbtmin_;

  Float_t mt2_;
  Float_t mt2j_;

  Int_t   csc_;      
  Int_t   hbhe_;   
  Int_t   hbhenew_;   
  Int_t   hcallaser_;
  Int_t   ecaltp_;
  Int_t   trkfail_;
  Int_t   eebadsc_;

  Float_t jet1beta1_01_;
  Float_t jet2beta1_01_;
  Float_t jet3beta1_01_;
  Float_t jet4beta1_01_;

  Float_t jet1beta2_01_;
  Float_t jet2beta2_01_;
  Float_t jet3beta2_01_;
  Float_t jet4beta2_01_;

  Float_t jet1beta1_05_;
  Float_t jet2beta1_05_;
  Float_t jet3beta1_05_;
  Float_t jet4beta1_05_;

  Float_t jet1beta2_05_;
  Float_t jet2beta2_05_;
  Float_t jet3beta2_05_;
  Float_t jet4beta2_05_;

  Float_t jet1beta1_10_;
  Float_t jet2beta1_10_;
  Float_t jet3beta1_10_;
  Float_t jet4beta1_10_;

  Float_t jet1beta2_10_;
  Float_t jet2beta2_10_;
  Float_t jet3beta2_10_;
  Float_t jet4beta2_10_;

  Int_t   vtxidx_;

  Int_t   jet1flav_;
  Int_t   jet2flav_;
  Int_t   jet3flav_;
  Int_t   jet4flav_;

  Float_t jet1drgen_;
  Float_t jet2drgen_;
  Float_t jet3drgen_;
  Float_t jet4drgen_;

  TH2F* hunc_eta1;
  TH2F* hunc_eta2;
  TH2F* hunc_eta3;
  TH2F* hunc_eta4;
  TH2F* hunc_eta5;
  TH2F* hunc_eta6;

  TH1F* hgenmet_all;
  TH1F* hgenmet_pass;
  TProfile* hresponse;  
  TH1F*   hgenps_pthat;
  TH1F*   hphotonpt;


  TH1F* hptz[5];
  TH1F* htcmet[4][4];
  TH1F* htcmetNew[4][4];
  TH1F* hpfmet[4][4];
  TH1F* hdilMass[4];

  TH1F* metPredicted;
  TH1F* metObserved;
  TH1F* metPredicted_sf;
  TH1F* metObserved_sf;
  TH1F* metPredicted_df;
  TH1F* metObserved_df;
  TH1F* metPredicted_ee;
  TH1F* metObserved_ee;
  TH1F* metPredicted_mm;
  TH1F* metObserved_mm;
  TH1F* metParPredicted;
  TH1F* metParObserved;
  TH1F* metPerpPredicted;
  TH1F* metPerpObserved;

  TH1F* metPredicted_njets[11];
  TH1F* metObserved_njets[11];

  TH1F* metTemplate[11][23];
  TH1F* metParTemplate[11][23];
  TH1F* metPerpTemplate[11][23];


};





#endif
