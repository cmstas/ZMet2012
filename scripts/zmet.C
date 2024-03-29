#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>
#include <fstream>

#include "TCanvas.h"
#include "TLegend.h"
#include "TChain.h"
#include "TDirectory.h"
#include "TFile.h"
#include "TROOT.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TMath.h"
#include "TPad.h"
#include "TCut.h"
#include "TProfile.h"
#include "THStack.h"
#include "TLatex.h"
#include "TGraphErrors.h"
#include "TStyle.h"
#include "TLine.h"
#include "TMath.h"
#include <sstream>
#include "Hootilities.C"
#include "zmet.h"
//#include "histtools.h"

using namespace std;

bool printgif_           = false;
bool alreadyInitialized_ = false;

//--------------------------------------------------
// initialize data/MC samples
//--------------------------------------------------

void initialize(char* path){

  if( alreadyInitialized_ ){

    cout << "Resetting babies" << endl;

    data->Reset();
    tt->Reset();
    zjets->Reset();
    zjetsee->Reset();
    zjetsmm->Reset();
    zjetstt->Reset();
    ww->Reset();
    wz->Reset();
    zz->Reset();
    t->Reset();
    ttV->Reset();
    tbz->Reset();
    vvv->Reset();

    mc.clear();
    mclabels.clear();
  }

  else{

    data	= new TChain("T1");
    tt	        = new TChain("T1");
    zjets	= new TChain("T1");
    zjetsee	= new TChain("T1");
    zjetsmm	= new TChain("T1");
    zjetstt	= new TChain("T1");
    ww	        = new TChain("T1");
    wz	        = new TChain("T1");
    zz  	= new TChain("T1");
    t   	= new TChain("T1");
    ttV   	= new TChain("T1");
    tbz   	= new TChain("T1");
    vvv   	= new TChain("T1");
  }

  cout << endl;
  cout << "Loading babies at       : " << path << endl;

  /*
  // data->  Add(Form("%s/data_53X_baby.root"         , path));
  // data->  Add(Form("%s/data_2012C_53X_baby.root"   , path));

  data->  Add(Form("%s/data_53X_2012A_baby.root"   , path));
  data->  Add(Form("%s/data_53X_2012B_baby.root"   , path));
  data->  Add(Form("%s/data_53X_2012C_baby.root"   , path));
  data->  Add(Form("%s/data_53X_2012D_baby.root"   , path));

  tt->    Add(Form("%s/ttbar_53X_baby.root"        , path));
  zjets-> Add(Form("%s/zjets_full_53X_baby.root"   , path));
  //zjets-> Add(Form("%s/zjets_10to50_baby.root"   , path));
  ww->    Add(Form("%s/ww_53X_baby.root"           , path));
  wz->    Add(Form("%s/wz_53X_baby.root"           , path));
  wz->    Add(Form("%s/wz2l2q_53X_baby.root"       , path));
  zz->    Add(Form("%s/zz_53X_baby.root"           , path));
  zz->    Add(Form("%s/zz4l_53X_baby.root"         , path));
  zz->    Add(Form("%s/zz2l2q_53X_baby.root"       , path));
  t->     Add(Form("%s/t_53X_baby.root"            , path));
  ttV->   Add(Form("%s/ttW_53X_baby.root"          , path));
  ttV->   Add(Form("%s/ttZ_53X_baby.root"          , path));
  vvv->   Add(Form("%s/VVV_53X_baby.root"          , path));

  cout << "-------------------------------------" << endl;
  cout << "USING SKIMMED SAMPLES WITH NJETS >= 2" << endl;
  cout << "-------------------------------------" << endl << endl;

  //data->  Add(Form("%s/data_53X_baby_2jets.root"         , path));
  //data->  Add(Form("%s/data_2012C_53X_baby_2jets.root"   , path));
  data->  Add(Form("%s/data_53X_2012A_baby_2jets.root"   , path));
  data->  Add(Form("%s/data_53X_2012B_baby_2jets.root"   , path));
  data->  Add(Form("%s/data_53X_2012C_baby_2jets.root"   , path));
  data->  Add(Form("%s/data_53X_2012D_baby_2jets.root"   , path));
  tt->    Add(Form("%s/ttbar_53X_baby_2jets.root"        , path));
  zjets-> Add(Form("%s/zjets_full_53X_baby_2jets.root"   , path));
  //zjets-> Add(Form("%s/zjets_10to50_baby_2jets.root"   , path));
  ww->    Add(Form("%s/ww_53X_baby_2jets.root"           , path));
  wz->    Add(Form("%s/wz_53X_baby_2jets.root"           , path));
  wz->    Add(Form("%s/wz2l2q_53X_baby_2jets.root"       , path));
  zz->    Add(Form("%s/zz_53X_baby_2jets.root"           , path));
  zz->    Add(Form("%s/zz4l_53X_baby_2jets.root"         , path));
  zz->    Add(Form("%s/zz2l2q_53X_baby_2jets.root"       , path));
  t->     Add(Form("%s/t_53X_baby_2jets.root"            , path));
  ttV->   Add(Form("%s/ttW_53X_baby_2jets.root"          , path));
  ttV->   Add(Form("%s/ttZ_53X_baby_2jets.root"          , path));
  vvv->   Add(Form("%s/VVV_53X_baby_2jets.root"          , path));
  */


  data->  Add(Form("%s/data_53X_2012ALL_baby.root"       , path));
  tt->    Add(Form("%s/ttbar_53X_slim_baby.root"         , path));
  zjets-> Add(Form("%s/zjets_small_53X_slim_baby.root"   , path));
  ww->    Add(Form("%s/ww_53X_slim_baby.root"            , path));
  wz->    Add(Form("%s/wz3lnu_53X_slim_baby.root"        , path));
  wz->    Add(Form("%s/wz2l2q_53X_slim_baby.root"        , path));
  zz->    Add(Form("%s/zz2l2nu_53X_slim_baby.root"       , path));
  zz->    Add(Form("%s/zz4l_53X_slim_baby.root"          , path));
  zz->    Add(Form("%s/zz2l2q_53X_slim_baby.root"        , path));
  t->     Add(Form("%s/t_53X_slim_baby.root"             , path));
  ttV->   Add(Form("%s/ttw_53X_slim_baby.root"           , path));
  ttV->   Add(Form("%s/ttz_53X_slim_baby.root"           , path));
  tbz->   Add(Form("%s/tbz_53X_slim_baby.root"           , path));
  vvv->   Add(Form("%s/vvv_53X_slim_baby.root"           , path));


  /*
  cout << "-------------------------------------" << endl;
  cout << "USING SKIMMED SAMPLES WITH NJETS >= 2" << endl;
  cout << "-------------------------------------" << endl << endl;

  data->  Add(Form("%s/data_53X_2012ALL_baby_2jets.root"       , path));
  tt->    Add(Form("%s/ttbar_53X_slim_baby_2jets.root"         , path));
  zjets-> Add(Form("%s/zjets_small_53X_slim_baby_2jets.root"   , path));
  ww->    Add(Form("%s/ww_53X_slim_baby_2jets.root"            , path));
  wz->    Add(Form("%s/wz3lnu_53X_slim_baby_2jets.root"        , path));
  wz->    Add(Form("%s/wz2l2q_53X_slim_baby_2jets.root"        , path));
  zz->    Add(Form("%s/zz2l2nu_53X_slim_baby_2jets.root"       , path));
  zz->    Add(Form("%s/zz4l_53X_slim_baby_2jets.root"          , path));
  zz->    Add(Form("%s/zz2l2q_53X_slim_baby_2jets.root"        , path));
  t->     Add(Form("%s/t_53X_slim_baby_2jets.root"             , path));
  ttV->   Add(Form("%s/ttw_53X_slim_baby_2jets.root"           , path));
  ttV->   Add(Form("%s/ttz_53X_slim_baby_2jets.root"           , path));
  tbz->   Add(Form("%s/tbz_53X_slim_baby_2jets.root"           , path));
  vvv->   Add(Form("%s/vvv_53X_slim_baby_2jets.root"           , path));
  */  



  // mc.push_back(zjets);   mclabels.push_back("zjets");
  // mc.push_back(wz);      mclabels.push_back("WZ");
  // mc.push_back(zz);      mclabels.push_back("ZZ");
  // mc.push_back(tt);      mclabels.push_back("ttbar");
  // mc.push_back(t);       mclabels.push_back("single top");
  // mc.push_back(ww);      mclabels.push_back("WW");
  // mc.push_back(ttV);     mclabels.push_back("ttV");
  // mc.push_back(vvv);     mclabels.push_back("VVV");

  mc.push_back(zjets);   mclabels.push_back("zjets");
  mc.push_back(tt);      mclabels.push_back("ttbar");
  mc.push_back(wz);      mclabels.push_back("WZ");
  mc.push_back(zz);      mclabels.push_back("ZZ");
  mc.push_back(ww);      mclabels.push_back("WW");
  mc.push_back(t);       mclabels.push_back("single top");
  mc.push_back(ttV);     mclabels.push_back("ttV");
  mc.push_back(tbz);     mclabels.push_back("tbz");
  mc.push_back(vvv);     mclabels.push_back("VVV");

  //mc.push_back(zjetsee); mclabels.push_back("zjetsee");
  //mc.push_back(zjetsmm); mclabels.push_back("zjetsmm");
  //mc.push_back(zjetstt); mclabels.push_back("zjetstt");

  alreadyInitialized_ = true;
}

//------------------------------------------
// selection and weight to apply to babies
//------------------------------------------

TCut selection_TCut(){

  TCut pfleptons("pflep1.pt() > 20 && pflep2.pt() > 20");
  TCut pt2020("lep1.pt()>20.0 && lep2.pt()>20.0");
  TCut transveto("el1tv==0 && el2tv==0");
  TCut Zmasspf("dilmasspf>81 && dilmasspf<101");
  TCut Zmass("dilmass>81 && dilmass<101");
  TCut njets2("njets>=2");
  TCut njets4("njets>=4");
  TCut nlep3("nlep==3 && lep3.pt()>20");
  TCut nlep4("nlep==4");
  TCut met30("pfmet>30");
  TCut met40("pfmet>40");
  TCut met50("pfmet>50");
  TCut met60("pfmet>60");
  TCut met75("pfmet>75");
  TCut met100("pfmet>100");
  TCut bveto("nbm==0");
  TCut btag1("nbm>=1");
  TCut nlep2("nlep==2");
  TCut rho40("rho>=0.0 && rho<40.0");
  TCut mjj("mjj>70.0 && mjj<110.0");
  TCut nb1("nbcsvm>=1");
  TCut nbm0("nbcsvm==0");
  TCut nbl0("nbcsvl==0");
  TCut dR01("sqrt(  (lep1.eta()-lep2.eta())*(lep1.eta()-lep2.eta())  +  acos(cos((lep1.phi()-lep2.phi())))*acos(cos((lep1.phi()-lep2.phi()) )) ) > 0.1");
  TCut runrange("isdata==0 || (run<197556 || run>198913)");
  TCut mll15("dilmass>15.0");
  TCut mll_76_106("dilmass>76.0 && dilmass<106.0");
  TCut eetype("leptype==0 && (ee==1 || isdata==0)");
  TCut mmtype("leptype==1 && (mm==1 || isdata==0)");
  TCut emtype("leptype==2 && (em==1||me==1||isdata==0)");
  TCut sf = eetype||mmtype;
  TCut filters("csc==0 && hbhe==1 && hcallaser==1 && ecaltp==1 && trkfail==1 && eebadsc==1 && hbhenew==1");
  TCut mt100("sqrt(2*pfmet*lep3.pt()*(1-cos(pfmetphi-lep3.phi())))>100.0"); 
  // no trigger requirements
  // TCut eetype("leptype==0 && jetptll-ptll>-5 && jetptlt-ptlt>-5");
  // TCut mmtype("leptype==1");
  // TCut emtype("leptype==2");
  // TCut eetype("leptype==0 && jetptll-ptll>-5 && jetptlt-ptlt>-5 && (ee==1 || isdata==0)");
  // TCut eetype("leptype==0 && (ee==1)");
  // TCut mmtype("leptype==1 && (mm==1)");
  // TCut emtype("leptype==2 && (em==1||me==1)");
  // TCut eetype("leptype==0 && jetptll-ptll>-5 && jetptlt-ptlt>-5 && (ee==1 || isdata==0)");
  // TCut mmtype("leptype==1 && (mm==1 || mmtk==1 || mu==1 || weight!=1.0)");
  // TCut emtype("leptype==2 && (em==1 || me==1   || mu==1 || weight!=1.0)");
  

  /*
  TCut sel;
  //sel += "njets==2";
  //sel += njets2;
  sel += pfleptons;
  //sel += transveto;
  sel += !Zmass;
  sel += (eetype||mmtype||emtype);
  //sel += nlep3;
  sel += met50;
  sel += btag1;
  sel += rho40;
  //sel += bveto;
  //sel += nlep2;
  //sel += mjj;
  //sel += met60;
  //sel += "jet2.pt()>50.0";
  */

  //----------------------
  // Aachen inclusive SR
  //----------------------
  /*
  TCut presel("njets40>=2 && ht40>100 && pfmet>150 && abs(lep1.eta())<2.4 && abs(lep2.eta())<2.4");
  //TCut presel("njets40>=2 && pfmet>50");
  TCut mll70("dilmass>15.0 && dilmass<70.0");
  TCut mll120("dilmass>120.0");
  //TCut presel("njets40>=3 && pfmet>100 && lep2.pt()>20.0 && abs(lep1.eta())<1.4 && abs(lep2.eta())<1.4 && dilmass>20.0 && dilmass<70.0");

  TCut sel;
  sel += presel; 
  sel += (eetype||mmtype||emtype);
  //sel += nb1;
  //sel += mll70;
  //sel += mll120;
  */

  //--------------------
  // ETH MET100 SR
  //--------------------
  /*
  TCut presel("pfmet>100 && njets40>=3");
  TCut leptons("lep1.pt()>20.0 && lep2.pt()>20.0 && abs(lep1.eta())<2.4 && abs(lep2.eta())<2.4");
  //TCut leptons("lep1.pt()>20.0 && lep2.pt()>20.0 && abs(lep1.eta())<1.4 && abs(lep2.eta())<1.4");
  TCut mll70("dilmass>15.0 && dilmass<70.0");
  TCut mll120("dilmass>120.0");
  // TCut presel("njets40>=2 && pfmet>50");
  // TCut mll70("dilmass>12.0 && dilmass<70.0");
  // TCut presel("njets40>=3 && pfmet>100 && lep2.pt()>20.0 &&  && dilmass<70.0");

  TCut sel;
  sel += presel; 
  sel += leptons;
  //sel += mll70;
  sel += (eetype||mmtype||emtype);
  sel += mll120;
  //sel += (emtype);
  //sel += nb1;
  //sel += mll70;
  */

  //------------------------------
  // inclusive ttbar selection
  //------------------------------
  /*
  TCut presel("lep1.pt()>20.0 && lep2.pt()>20.0 && dilmass>15.0 && (dilmass<76.0||dilmass>106.0)");
  TCut eta24("abs(lep1.eta())<2.4 && abs(lep2.eta())<2.4");
  //TCut presel("njets40>=2 && dilmass>12.0 && lep2.pt()>20.0");
  //TCut mll_40_70("dilmass>40 && dilmass<70.0");
  TCut njets40gt2("njets40>=2");

  TCut sel;
  sel += presel;
  sel += eta24;
  sel += (eetype||mmtype||emtype);
  //sel += runrange;

  // sel += mll_76_106;
  // sel += Zmass||emtype;
  // sel += pt2020; 
  // sel += Zmass; 
  // sel += (emtype);
  sel += "pfmet>50";
  // sel += njets40gt2;
  // sel += nb1;
  // sel += dR01;
  // sel += mll_40_70;
  */

  //------------------------------
  // inclusive Z selection
  //------------------------------
  /*
  TCut sel;
  //sel += runrange;
  sel += (eetype||mmtype||emtype);
  sel += filters;
  sel += pt2020;
  sel += mll15;
  sel += njets2;
  sel += nbm0;
  //sel += nbl0;
  sel += mjj;
  sel += nlep2;
  //sel += mll_76_106;
  sel += Zmass;
  */
  //------------------------------
  // WZ control region
  //------------------------------
  /*
  TCut sel;
  //sel += runrange;
  sel += (eetype||mmtype||emtype);
  sel += filters;
  sel += pt2020;
  sel += "nlep==3 && lep3.pt()>20.0";
  sel += met50;
  sel += Zmass;
  sel += njets2;
  //sel += nb0;
  //sel += sf;
  //sel += mt100;
  */
  //------------------------------
  // ZZ control region
  //------------------------------

  TCut sel;
  //sel += runrange;
  sel += (eetype||mmtype||emtype);
  sel += filters;
  sel += pt2020;
  sel += "nlep==4 && lep3.pt()>20.0 && lep4.pt()>20.0";
  sel += Zmass;
  //sel += njets2;
  //sel += nb0;

  cout << "Using selection         : " << sel.GetTitle() << endl;

  return sel;
}
TCut weight_TCut(){

  //TCut weight("1");
  //TCut weight("weight * 5.10 * vtxweight * trgeff");
  //TCut weight("weight * 9.2 * trgeff * vtxweight");
  TCut weight("weight * 19.3 * trgeff * vtxweight");
  //TCut weight("weight * 19.3 * trgeff * vtxweight * (200/130.4)"); // normalize to data for WZ+>=2 jets
  //TCut weight("weight * 5.10");
  //TCut weight("weight * 2.5 * vtxweight");
  //TCut weight("weight * 5.10");
  //TCut weight("1");
  
  cout << "Using weight            : " << weight.GetTitle() << endl;
  return weight;
}


void plotHist( TH1F* h1 , TH1F* h2 , char* leg1 , char* leg2 , char* xtitle ){

  gPad->SetLogy(1);

  h1->GetXaxis()->SetTitle( xtitle );
  h1->DrawNormalized("hist");
  h2->SetLineColor(2);
  h2->SetMarkerColor(2);
  h2->DrawNormalized("sameE1");

  TLegend *leg = new TLegend(0.7,0.7,0.9,0.9);
  leg->AddEntry(h1,leg1,"l");
  leg->AddEntry(h2,leg2,"p");
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->Draw();

}

//------------------------------------
// print yield table
//------------------------------------

void printYieldTable( char* path , bool latex = false ){

  deleteHistos();

  initialize(path);
  
  TCut sel    = selection_TCut();
  TCut weight = weight_TCut();

  printYields( mc , mclabels , data , sel , weight , latex );
 
}

//--------------------------------------------------
// make data/MC plots
//--------------------------------------------------

void makePlots( char* path , bool printgif = false ){

  bool combine     = true;
  int  nplots      = 3;
  bool residual    = true;
  bool log         = false;
  bool overlayData = true;
  bool normalize   = false;
  bool fit         = false;

  initialize(path);

  TCut sel    = selection_TCut();
  TCut weight = weight_TCut();

  vector<char*> vars;
  vector<char*> xt;
  vector<int>   n;
  vector<float> xi;
  vector<float> xf;
  vector<char*> flavor;
  vector<TCut>  cuts;

  // vars.push_back("nvtx"); 
  // xt.push_back("N_{VTX}");
  // n.push_back(30);  xi.push_back(0.);  xf.push_back(30.); 
  // flavor.push_back("all"); 
  // cuts.push_back(TCut(""));
  /*
  vars.push_back("njets40"); 
  xt.push_back("n_{jets}");
  n.push_back(6);  xi.push_back(0.);  xf.push_back(6.); 
  flavor.push_back("ee"); 
  cuts.push_back(TCut("leptype==0"));

  vars.push_back("njets40"); 
  xt.push_back("n_{jets}");
  n.push_back(6);  xi.push_back(0.);  xf.push_back(6.); 
  flavor.push_back("mm"); 
  cuts.push_back(TCut("leptype==1"));
  */

  // vars.push_back("njets40"); 
  // xt.push_back("n_{jets}");
  // n.push_back(6);  xi.push_back(0.);  xf.push_back(6.); 
  // flavor.push_back("all"); 
  // cuts.push_back(TCut("leptype<2"));

  // vars.push_back("njets40"); 
  // xt.push_back("n_{jets}");
  // n.push_back(6);  xi.push_back(0.);  xf.push_back(6.); 
  // flavor.push_back("em"); 
  // cuts.push_back(TCut("leptype==2"));

  /*
  char* myvar = "sqrt((lep1.eta()-lep2.eta())*(lep1.eta()-lep2.eta())  +  acos(cos((lep1.phi()-lep2.phi())))*acos(cos((lep1.phi()-lep2.phi()) )))";


  vars.push_back(myvar); 
  xt.push_back("#DeltaR(ll)");
  n.push_back(20);  xi.push_back(0.);  xf.push_back(5.); 
  flavor.push_back("ee"); 
  cuts.push_back(TCut("leptype==0"));

  vars.push_back(myvar); 
  xt.push_back("#DeltaR(ll)");
  n.push_back(20);  xi.push_back(0.);  xf.push_back(5.); 
  flavor.push_back("mm"); 
  cuts.push_back(TCut("leptype==1"));


  vars.push_back(myvar); 
  xt.push_back("#DeltaR(ll)");
  n.push_back(20);  xi.push_back(0.);  xf.push_back(5.); 
  flavor.push_back("em"); 
  cuts.push_back(TCut("leptype==2"));
*/  


  // vars.push_back("dilmass"); 
  // xt.push_back("M(ll) (GeV)");
  // n.push_back(30);  xi.push_back(20.);  xf.push_back(320.); 
  // flavor.push_back("em"); 
  // cuts.push_back(TCut("leptype==2"));

  // vars.push_back("dilmass"); 
  // xt.push_back("M(ll) (GeV)");
  // n.push_back(30);  xi.push_back(20.);  xf.push_back(320.); 
  // flavor.push_back("all"); 
  // cuts.push_back(TCut("leptype<2"));

  // vars.push_back("dilmass"); 
  // xt.push_back("M(ee) (GeV)");
  // n.push_back(15);  xi.push_back(50.);  xf.push_back(200.); 
  // flavor.push_back("ee"); 
  // cuts.push_back(TCut("leptype==0"));

  // vars.push_back("dilmass"); 
  // xt.push_back("M(#mu#mu) (GeV)");
  // n.push_back(15);  xi.push_back(50.);  xf.push_back(200.); 
  // flavor.push_back("mm"); 
  // cuts.push_back(TCut("leptype==1"));

  // vars.push_back("dilmass"); 
  // xt.push_back("M(e#mu) (GeV)");
  // n.push_back(30);  xi.push_back(0.);  xf.push_back(300.); 
  // flavor.push_back("em"); 
  // cuts.push_back(TCut("leptype==2"));

  // vars.push_back("dilmass"); 
  // xt.push_back("M(ll) (GeV)");
  // n.push_back(15);  xi.push_back(0.);  xf.push_back(300.); 
  // flavor.push_back("all"); 
  // cuts.push_back(TCut("leptype<2"));

  /*
  vars.push_back("lep2.pt()"); 
  xt.push_back("trailing lepton p_{T} [GeV]");
  n.push_back(20);  xi.push_back(0.);  xf.push_back(100.); 
  flavor.push_back("ee"); 
  cuts.push_back(TCut("leptype==0"));

  vars.push_back("lep2.pt()"); 
  xt.push_back("trailing lepton p_{T} [GeV]");
  n.push_back(20);  xi.push_back(0.);  xf.push_back(100.); 
  flavor.push_back("mm"); 
  cuts.push_back(TCut("leptype==1"));

  vars.push_back("lep2.pt()"); 
  xt.push_back("trailing lepton p_{T} [GeV]");
  n.push_back(20);  xi.push_back(0.);  xf.push_back(100.); 
  flavor.push_back("em"); 
  cuts.push_back(TCut("leptype==2"));
  */

  /*
  vars.push_back("pfmet"); 
  xt.push_back("E_{T}^{miss} [GeV]");
  n.push_back(20);  xi.push_back(0.);  xf.push_back(200.); 
  flavor.push_back("ee"); 
  cuts.push_back(TCut("leptype==0"));

  vars.push_back("pfmet"); 
  xt.push_back("E_{T}^{miss} [GeV]");
  n.push_back(20);  xi.push_back(0.);  xf.push_back(200.); 
  flavor.push_back("mm"); 
  cuts.push_back(TCut("leptype==1"));

  vars.push_back("pfmet"); 
  xt.push_back("E_{T}^{miss} [GeV]");
  n.push_back(20);  xi.push_back(0.);  xf.push_back(200.); 
  flavor.push_back("em"); 
  cuts.push_back(TCut("leptype==2"));
*/
  /*
  //--------------------------------------------------------------
  // tt-->ll control plots for single lepton stop analysis
  //--------------------------------------------------------------

  TCut jetcut("njets>=2");
  TCut el("abs(id1)==11");
  TCut mu("abs(id1)==13");

  vars.push_back("lep1.pt()"); 
  xt.push_back("leading e p_{T} (GeV)");
  n.push_back(20);  xi.push_back(0.);  xf.push_back(400.); 
  flavor.push_back("all"); 
  cuts.push_back(TCut(jetcut+el));

  vars.push_back("pfmet"); 
  xt.push_back("E_{T}^{miss}, e (GeV)");
  n.push_back(20);  xi.push_back(0.);  xf.push_back(400.); 
  flavor.push_back("all"); 
  cuts.push_back(TCut(jetcut+el));

  vars.push_back("sqrt(2*pfmet*lep1.pt()*(1-cos(pfmetphi-lep1.phi())))"); 
  xt.push_back("M_{T}, e (GeV)");  
  n.push_back(20);  xi.push_back(0.);  xf.push_back(400.); 
  flavor.push_back("all"); 
  cuts.push_back(TCut(jetcut+el));

  vars.push_back("lep1.pt()"); 
  xt.push_back("leading #mu p_{T} (GeV)");    
  n.push_back(20);  xi.push_back(0.);  xf.push_back(400.); 
  flavor.push_back("all");
  cuts.push_back(TCut(jetcut+mu));

  vars.push_back("pfmet"); 
  xt.push_back("E_{T}^{miss}, #mu (GeV)");
  n.push_back(20);  xi.push_back(0.);  xf.push_back(400.); 
  flavor.push_back("all"); 
  cuts.push_back(TCut(jetcut+mu));

  vars.push_back("sqrt(2*pfmet*lep1.pt()*(1-cos(pfmetphi-lep1.phi())))"); 
  xt.push_back("M_{T}, #mu (GeV)");  
  n.push_back(20);  xi.push_back(0.);  xf.push_back(400.); 
  flavor.push_back("all"); 
  cuts.push_back(TCut(jetcut+mu));
  */       

  //vars.push_back("lep2.pt()");     xt.push_back("trailing lepton p_{T} (GeV)");  n.push_back(10);  xi.push_back(20.);   xf.push_back(220.); flavor.push_back("all");
  //vars.push_back("dilmasspf");       xt.push_back("M(ee) (GeV)");          n.push_back(15);  xi.push_back(50.);   xf.push_back(200.);    flavor.push_back("ee");
  //vars.push_back("dilmasspf");       xt.push_back("M(#mu#mu) (GeV)");      n.push_back(15);  xi.push_back(50.);   xf.push_back(200.);    flavor.push_back("mm");
  //vars.push_back("dilmasspf");       xt.push_back("M(e#mu) (GeV)");        n.push_back(15);  xi.push_back(0.);   xf.push_back(300.);    flavor.push_back("em");

  //vars.push_back("nvtx");              xt.push_back("N_{VTX}");              n.push_back(40);  xi.push_back(0.);    xf.push_back(40.);     flavor.push_back("all");
  //vars.push_back("dilmasspf");       xt.push_back("M(e#mu) (GeV)");        n.push_back(75);  xi.push_back(50.);   xf.push_back(200.);    flavor.push_back("em");
  //vars.push_back("lljj");          xt.push_back("M(lljj) (GeV)");      n.push_back(25);  xi.push_back(350.); xf.push_back(1850.);   flavor.push_back("ee");
  //vars.push_back("lljj");          xt.push_back("M(lljj) (GeV)");      n.push_back(25);  xi.push_back(350.); xf.push_back(1850.);   flavor.push_back("mm");
  //vars.push_back("njets");         xt.push_back("njets");              n.push_back(10);   xi.push_back(0);    xf.push_back(10);       flavor.push_back("all"); cuts.push_back(TCut(""));
  //vars.push_back("njets");         xt.push_back("njets");              n.push_back(6);   xi.push_back(0);    xf.push_back(6);       flavor.push_back("mm");
  //vars.push_back("pfmet");         xt.push_back("pfmet (GeV)");        n.push_back(50);  xi.push_back(0.);   xf.push_back(100.);  flavor.push_back("ee");
  //vars.push_back("pfmet");         xt.push_back("pfmet (GeV)");        n.push_back(50);  xi.push_back(0.);   xf.push_back(100.);  flavor.push_back("all"); cuts.push_back(TCut(""));
  //vars.push_back("dilep.pt()");    xt.push_back("Z p_{T} (GeV)");      n.push_back(10);  xi.push_back(0);    xf.push_back(400);
  //vars.push_back("w.pt()");        xt.push_back("W p_{T} (GeV)");      n.push_back(10);  xi.push_back(0);    xf.push_back(400);

  // WZ/ZZ control plots
  vars.push_back("njets");         xt.push_back("njets");          n.push_back(5);   xi.push_back(0);    xf.push_back(5);       flavor.push_back("sf"); cuts.push_back(TCut(""));
  vars.push_back("pfmet");         xt.push_back("pfmet (GeV)");    n.push_back(6);   xi.push_back(0.);   xf.push_back(60.0);    flavor.push_back("sf"); cuts.push_back(TCut(""));
  vars.push_back("dilep.pt()");    xt.push_back("Z p_{T} (GeV)");  n.push_back(6);   xi.push_back(0);    xf.push_back(300.0);   flavor.push_back("sf"); cuts.push_back(TCut(""));

  // vars.push_back("jet1.eta()");            xt.push_back("1st jet #eta");       n.push_back(12);   xi.push_back(-3);    xf.push_back(3);       flavor.push_back("sf"); cuts.push_back(TCut(""));
  // vars.push_back("jet2.eta()");            xt.push_back("2nd jet #eta");       n.push_back(12);   xi.push_back(-3);    xf.push_back(3);       flavor.push_back("sf"); cuts.push_back(TCut(""));
  // vars.push_back("jet1.eta()-jet2.eta()"); xt.push_back("1st - 2nd jet #eta"); n.push_back(12);   xi.push_back(-6);    xf.push_back(6);       flavor.push_back("sf"); cuts.push_back(TCut(""));

  // vars.push_back("lep1.pt()");   xt.push_back("1st lepton p_{T} [GeV]"); n.push_back(10);   xi.push_back(0); xf.push_back(200); flavor.push_back("sf"); cuts.push_back(TCut(""));
  // vars.push_back("lep2.pt()");   xt.push_back("2nd lepton p_{T} [GeV]"); n.push_back(10);   xi.push_back(0); xf.push_back(200); flavor.push_back("sf"); cuts.push_back(TCut(""));
  // vars.push_back("lep3.pt()");   xt.push_back("3rd lepton p_{T} [GeV]"); n.push_back(10);   xi.push_back(0); xf.push_back(200); flavor.push_back("sf"); cuts.push_back(TCut(""));

  // vars.push_back("mjj");             xt.push_back("M(jj) (GeV)");      n.push_back(20);   xi.push_back(0);    xf.push_back(400.0);   flavor.push_back("ee"); cuts.push_back(TCut("leptype==0"));
  // vars.push_back("mjj");             xt.push_back("M(jj) (GeV)");      n.push_back(20);   xi.push_back(0);    xf.push_back(400.0);   flavor.push_back("mm"); cuts.push_back(TCut("leptype==1"));
  // vars.push_back("mjj");             xt.push_back("M(jj) (GeV)");      n.push_back(20);   xi.push_back(0);    xf.push_back(400.0);   flavor.push_back("em"); cuts.push_back(TCut("leptype==2"));

  // vars.push_back("sqrt(2*pfmet*lep3.pt()*(1-cos(pfmetphi-lep3.phi())))"); 
  // xt.push_back("M_{T} [GeV]");  
  // n.push_back(20);  xi.push_back(0.);  xf.push_back(200.); 
  // flavor.push_back("sf"); 
  // cuts.push_back(TCut(""));


  // vars.push_back("njets");         xt.push_back("njets");          n.push_back(10);   xi.push_back(0);    xf.push_back(10);       flavor.push_back("sf"); cuts.push_back(TCut(""));
  // vars.push_back("sumjetpt");      xt.push_back("H_{T} [GeV]");    n.push_back(10);   xi.push_back(0);    xf.push_back(500);      flavor.push_back("sf"); cuts.push_back(TCut(""));
  // vars.push_back("nbcsvm");        xt.push_back("b-tags (CSVM)");  n.push_back(4);    xi.push_back(0);    xf.push_back(4);        flavor.push_back("sf"); cuts.push_back(TCut(""));

  //vars.push_back("pfmet");         xt.push_back("E_{T}^{miss} [GeV]");  n.push_back(8);   xi.push_back(0);    xf.push_back(400);    flavor.push_back("sf"); cuts.push_back(TCut(""));

  //vars.push_back("mjj");         xt.push_back("dijet mass [GeV]");  n.push_back(20);   xi.push_back(0);    xf.push_back(500);    flavor.push_back("sf"); cuts.push_back(TCut(""));

  const unsigned int nvars = vars.size();
  
  TCanvas *can[nvars];
  TPad* legpad[nvars];
  TPad* plotpad[nvars];


  int canCounter = -1;

  for( unsigned int ivar = 0 ; ivar < nvars ; ++ivar ){     
    
    // if( ivar < 2 ) log = true;
    // else           log = false;
    
    //if( TString(vars.at(ivar)).Contains("met") ) log = true;
    //else                                         log = false;

    //log = false;

    TString tvar(vars.at(ivar));
    tvar.ReplaceAll("()","");
    tvar.ReplaceAll("(","");
    tvar.ReplaceAll(")","");
    tvar.ReplaceAll(".","");
    tvar.ReplaceAll("*","");
    const char* myvar = tvar;

    if( combine ){
      if( ivar % nplots == 0 ){
	canCounter++;


	if( nplots == 1 ) can[canCounter] = new TCanvas(Form("%s_can",myvar),Form("%s_can",myvar),600,600);
	if( nplots == 2 ) can[canCounter] = new TCanvas(Form("%s_can",myvar),Form("%s_can",myvar),1200,600);
	if( nplots == 3 ) can[canCounter] = new TCanvas(Form("%s_can",myvar),Form("%s_can",myvar),1500,500);
	if( nplots == 4 ) can[canCounter] = new TCanvas(Form("%s_can",myvar),Form("%s_can",myvar),1200,1200);
	if( nplots == 6 ) can[canCounter] = new TCanvas(Form("%s_can",myvar),Form("%s_can",myvar),1200,800);

	//can[canCounter] = new TCanvas(Form("%s_can",myvar),Form("%s_can",myvar),1200,600);
	//can[canCounter] = new TCanvas(Form("%s_can",myvar),Form("%s_can",myvar),1400,1200);
	//can[canCounter] = new TCanvas(Form("%s_can",myvar),Form("%s_can",myvar),2000,1200);
	
	/*
	  legpad[canCounter] = new TPad("legpad","legpad",12./14.,0,1,1);
	  legpad[canCounter]->Draw();
	  legpad[canCounter]->cd();

	  TLegend *leg = getLegend( mc , mclabels , true , 0. , 0.3 , 0.95 , 0.7 );
	  leg->SetTextSize(0.1);
	  leg->SetBorderSize(1);
	  leg->Draw();
	*/
	can[canCounter]->cd();

	plotpad[canCounter] = new TPad("plotpad","plotpad",0,0,1.,1.);
	//plotpad[canCounter] = new TPad("plotpad","plotpad",0,0,12./14.,1);
	plotpad[canCounter]->Draw();
	plotpad[canCounter]->cd();

	if( nplots == 2 ) plotpad[canCounter]->Divide(2,1);
	if( nplots == 3 ) plotpad[canCounter]->Divide(3,1);
	if( nplots == 4 ) plotpad[canCounter]->Divide(2,2);
	if( nplots == 6 ) plotpad[canCounter]->Divide(3,2);
	plotpad[canCounter]->cd(1);

      }else{
	plotpad[canCounter]->cd(1+ivar%nplots);
      }
    }else{
      can[ivar] = new TCanvas(Form("%s_can",myvar),Form("%s_can",myvar),600,600);
    }

    //compareDataMC( mc , mclabels , data , vars[ivar] , sel , weight , n[ivar] , xi[ivar] , xf[ivar] , xt[ivar] , overlayData , residual , !combine , log );
    compareDataMC( mc , mclabels , data , vars[ivar] , TCut(sel+cuts.at(ivar)) , weight , n[ivar] , 
		   xi[ivar] , xf[ivar] , xt[ivar] , overlayData , residual , true , log , normalize , fit , flavor.at(ivar) );

    if( printgif && !combine ){
      can[ivar]->Print(Form("../plots/%s_%s.pdf",myvar,flavor.at(ivar)));
      //can[ivar]->Print(Form("../plots/%s_%s.png",myvar,flavor.at(ivar)));
    }
  } 

  if( printgif && combine ){
    can[0]->Print("../plots/makePlots.pdf");
    //can[0]->Print("../plots/makePlots.ps");
    //can[0]->Print("../plots/makePlots.png");
  }


}
/*
void makePlots( char* path , bool printgif = false ){

  initialize(path);

  TCut sel    = selection_TCut();
  TCut weight = weight_TCut();

  //sel = sel + "y > 8.5 && ht > 300";

  vector<char*> vars;
  vector<char*> xt;
  vector<int>   n;
  vector<float> xi;
  vector<float> xf;


  vars.push_back("njets");       xt.push_back("njets");              n.push_back(6);  xi.push_back(0);  xf.push_back(6);
  vars.push_back("dilep.pt()");  xt.push_back("Z p_{T}");            n.push_back(20); xi.push_back(0);  xf.push_back(400);
  vars.push_back("w.pt()");      xt.push_back("W p_{T}");            n.push_back(20); xi.push_back(0);  xf.push_back(400);
  vars.push_back("pfmet");       xt.push_back("pfmet (GeV)");        n.push_back(10); xi.push_back(0.); xf.push_back(200.);

  //vars.push_back("lep3.pt()");   xt.push_back("3rd lepton p_{T}");   n.push_back(20); xi.push_back(0);  xf.push_back(200);
  //vars.push_back("dilpt");     xt.push_back("p_{T}(ll) (GeV)");  n.push_back(30); xi.push_back(0.); xf.push_back(300.);
  //vars.push_back("ht");        xt.push_back("H_{T} (GeV)");      n.push_back(20); xi.push_back(0.); xf.push_back(1000.);
  //vars.push_back("ndavtx");      xt.push_back("nDAVertices");      n.push_back(20); xi.push_back(0);  xf.push_back(20);
  //vars.push_back("dilep.mass()");     xt.push_back("dilmass (GeV)");    n.push_back(100);  xi.push_back(0);  xf.push_back(200);
  
  const unsigned int nvars = vars.size();
  
  TCanvas *can[nvars];
    
  for( unsigned int ivar = 0 ; ivar < nvars ; ++ivar ){     
    can[ivar] = new TCanvas(Form("%s_can",vars[ivar]),Form("%s_can",vars[ivar]),600,600);

    compareDataMC( mc , mclabels , data , vars[ivar] , sel , weight , n[ivar] , xi[ivar] , xf[ivar] , xt[ivar] );

    if( printgif ) can[ivar]->Print(Form("../plots/%s.png",vars[ivar]));
  } 
}
*/

TH1F* getHist( TChain* ch , char* var , TCut sel , char* histname , int nbins , float xmin , float xmax ){

  TH1F* h = new TH1F(histname,histname,nbins,xmin,xmax);
  h->Sumw2();
  TCanvas *ctemp = new TCanvas();
  ch->Draw(Form("TMath::Min(%s,%f) >> %s",var,xmax-0.001,histname),sel);
  delete ctemp;
  return h;
}

TH2F* getHist2D( TChain* ch , char* varx , char* vary , TCut sel , char* histname , 
		 int nbinsx , float xmin , float xmax , int nbinsy , float ymin , float ymax ){
  
  TH2F* h = new TH2F(histname,histname,nbinsx,xmin,xmax,nbinsy,ymin,ymax);
  h->Sumw2();

  TCanvas *ctemp = new TCanvas();
  ch->Draw(Form("TMath::Min(%s,%f):TMath::Min(%s,%f) >> %s",vary,ymax-0.001,varx,xmax-0.01,histname),sel);
  delete ctemp;
  return h;
}


float calculateHistError( TH1F* h , int minbin , int maxbin ){

  float err2 = 0;
  for( int i = minbin ; i <= maxbin ; ++i ){
    err2 += pow( h->GetBinError(i) , 2 );
  }

  return sqrt(err2);
}




