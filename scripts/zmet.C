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
    wz->Reset();
    zz->Reset();

    mc.clear();
    mclabels.clear();
  }

  else{

    data	= new TChain("T1");
    tt	        = new TChain("T1");
    zjets	= new TChain("T1");
    wz	        = new TChain("T1");
    zz  	= new TChain("T1");
  }

  cout << endl;
  cout << "Loading babies at       : " << path << endl;
  
  data->Add(Form("%s/data_baby.root",path));
  zjets->Add(Form("%s/zjets_baby.root",path));

  //tt->Add(Form("%s/ttbar_baby.root",path));
  //zjets->Add(Form("%s/zjets_baby_geq2jets.root",path));
  //wz->Add(Form("%s/wz_summer11_madgraph_baby.root",path));
  //zz->Add(Form("%s/zz_summer11_madgraph_baby.root",path));
  //wz->Add(Form("%s/wz_summer11_pythia_baby.root",path));
  //zz->Add(Form("%s/zz_summer11_pythia_baby.root",path));

  //mc.push_back(tt);     mclabels.push_back("tt");
  mc.push_back(zjets);  mclabels.push_back("zjets");
  //mc.push_back(zz);     mclabels.push_back("zz");
  //mc.push_back(wz);     mclabels.push_back("wz");

  alreadyInitialized_ = true;
}
//------------------------------------------
// selection and weight to apply to babies
//------------------------------------------

TCut selection_TCut(){

  TCut pfleptons("pflep1.pt() > 20 && pflep2.pt() > 20");
  TCut transveto("el1tv==0 && el2tv==0");
  TCut Zmass("dilmasspf>81 && dilmasspf<101");
  TCut njets2("njets>=2");
  TCut ee("leptype==0 && jetptll-ptll>-5 && jetptlt-ptlt>-5");
  TCut mm("leptype==1");
  TCut em("leptype==2");
  TCut sf = ee||mm;

  TCut sel;
  //sel += njets2;
  sel += pfleptons;
  sel += transveto;
  //sel += Zmass;
  sel += (ee||mm||em);

  cout << "Using selection         : " << sel.GetTitle() << endl;

  return sel;
}
TCut weight_TCut(){

  TCut weight("weight * 0.92 * vtxweight");
  
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
  int  nplots      = 2;
  bool residual    = true;
  bool log         = false;
  bool overlayData = true;

  initialize(path);

  TCut sel    = selection_TCut();
  TCut weight = weight_TCut();

  vector<char*> vars;
  vector<char*> xt;
  vector<int>   n;
  vector<float> xi;
  vector<float> xf;
  vector<char*> flavor;

  vars.push_back("dilmasspf");       xt.push_back("M(ee) (GeV)");          n.push_back(100);  xi.push_back(0.);   xf.push_back(200.);    flavor.push_back("ee");
  vars.push_back("dilmasspf");       xt.push_back("M(#mu#mu) (GeV)");      n.push_back(100);  xi.push_back(0.);   xf.push_back(200.);    flavor.push_back("mm");
  //vars.push_back("lljj");          xt.push_back("M(lljj) (GeV)");      n.push_back(25);  xi.push_back(350.); xf.push_back(1850.);   flavor.push_back("ee");
  //vars.push_back("lljj");          xt.push_back("M(lljj) (GeV)");      n.push_back(25);  xi.push_back(350.); xf.push_back(1850.);   flavor.push_back("mm");
  //vars.push_back("njets");         xt.push_back("njets");              n.push_back(6);   xi.push_back(0);    xf.push_back(6);       flavor.push_back("ee");
  //vars.push_back("njets");         xt.push_back("njets");              n.push_back(6);   xi.push_back(0);    xf.push_back(6);       flavor.push_back("mm");
  //vars.push_back("pfmet");         xt.push_back("pfmet (GeV)");        n.push_back(50);  xi.push_back(0.);   xf.push_back(100.);  flavor.push_back("ee");
  //vars.push_back("pfmet");         xt.push_back("pfmet (GeV)");        n.push_back(50);  xi.push_back(0.);   xf.push_back(100.);  flavor.push_back("mm");
  //vars.push_back("dilep.pt()");    xt.push_back("Z p_{T} (GeV)");      n.push_back(10);  xi.push_back(0);    xf.push_back(400);
  //vars.push_back("w.pt()");        xt.push_back("W p_{T} (GeV)");      n.push_back(10);  xi.push_back(0);    xf.push_back(400);

  const unsigned int nvars = vars.size();
  
  TCanvas *can[nvars];
  TPad* legpad[nvars];
  TPad* plotpad[nvars];


  int canCounter = -1;

  for( unsigned int ivar = 0 ; ivar < nvars ; ++ivar ){     
    
    //if( TString(vars.at(ivar)).Contains("met") ) log = true;
    //else                                         log = false;

    //log = false;

    if( combine ){
      if( ivar % nplots == 0 ){
	canCounter++;
	can[canCounter] = new TCanvas(Form("%s_can",vars[ivar]),Form("%s_can",vars[ivar]),1200,600);
	//can[canCounter] = new TCanvas(Form("%s_can",vars[ivar]),Form("%s_can",vars[ivar]),1400,1200);
	//can[canCounter] = new TCanvas(Form("%s_can",vars[ivar]),Form("%s_can",vars[ivar]),2000,1200);
	
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

	//plotpad[canCounter]->Divide(3,2);
	//plotpad[canCounter]->Divide(2,2);
	plotpad[canCounter]->Divide(2,1);
	plotpad[canCounter]->cd(1);

      }else{
	plotpad[canCounter]->cd(1+ivar%nplots);
      }
    }else{
      can[ivar] = new TCanvas(Form("%s_can",vars[ivar]),Form("%s_can",vars[ivar]),600,600);
    }

    //compareDataMC( mc , mclabels , data , vars[ivar] , sel , weight , n[ivar] , xi[ivar] , xf[ivar] , xt[ivar] , overlayData , residual , !combine , log );
    compareDataMC( mc , mclabels , data , vars[ivar] , sel , weight , n[ivar] , xi[ivar] , xf[ivar] , xt[ivar] , overlayData , residual , true , log , flavor.at(ivar) );

    if( printgif && !combine ){
      //can[ivar]->Print(Form("../plots/%s.pdf",vars[ivar]));
      can[ivar]->Print(Form("../plots/%s_%s.ps",vars[ivar],flavor.at(ivar)));
      gROOT->ProcessLine(Form(".! ps2pdf ../plots/%s_%s.ps ../plots/%s_%s.pdf",vars[ivar],flavor.at(ivar),vars[ivar],flavor.at(ivar)));
      can[ivar]->Print(Form("../plots/%s_%s.png",vars[ivar],flavor.at(ivar)));
    }
  } 

  if( printgif && combine ){
    can[0]->Print("../plots/makePlots.pdf");
    can[0]->Print("../plots/makePlots.ps");
    //gROOT->ProcessLine(".! ps2pdf ../plots/makePlots.ps ../plots/makePlots.pdf");
    can[0]->Print("../plots/makePlots.png");
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



