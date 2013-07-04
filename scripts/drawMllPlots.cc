#include <iostream>
#include "TLegend.h"
#include "TLatex.h"
#include "TLine.h"
#include "TH1F.h"
#include "THStack.h"
#include "TFile.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TPad.h"

using namespace std;

int drawMllPlot( const string metregion, const string variable,
				 Float_t binwidth, 
			   Float_t xmin = 21.0, Float_t xmax = 201.0, 
			   Float_t ymin = 0.0, Float_t ymax = 1.0 );

int drawRatio( const string metregion, const string variable,
			   Float_t binwidth, 
			   Float_t xmin = 21.0, Float_t xmax = 201.0, 
			   Float_t ymin = 0.0, Float_t ymax = 1.0 );

void drawTex(Float_t bottomleft, Float_t topright, bool istargeted, string thirdline, string fourthline)
{

  float intlumi = 19.5;

  TLatex *tex = new TLatex(bottomleft, topright - 0.05, Form("#sqrt{s} = 8 TeV, L_{int} = %2.1f fb^{-1}", float(intlumi)));    
  // TLatex *tex = new TLatex(bottomleft,topright-0.05, "Simulation" );    
  tex->SetNDC();    
  tex->SetTextSize(0.035);    
  tex->SetLineWidth(2);    

  TLatex *tex2 = new TLatex(bottomleft,topright,"CMS Preliminary");    
  tex2->SetNDC();    
  tex2->SetTextSize(0.035);    
  tex2->SetLineWidth(2);

  TLatex *tex3;
  if(!istargeted){
	tex3 = new TLatex(bottomleft,topright-0.10, thirdline.c_str());//"Inclusive Selection + b-tag");
}else if(istargeted){
	tex3 = new TLatex(bottomleft,topright-0.10, thirdline.c_str() );    
  }
  tex3->SetNDC();    
  tex3->SetTextSize(0.035);    
  tex3->SetLineWidth(2);

  TLatex *tex4 = NULL;
  tex4 = new TLatex(bottomleft,topright-0.15, fourthline.c_str() );    
  tex4->SetNDC();    
  tex4->SetTextSize(0.035);    
  tex4->SetLineWidth(2);

  tex->Draw();
  tex2->Draw();
  tex3->Draw();
  tex4->Draw();
  return;
}

int drawAllPlots( const string metregion )
{

  TCanvas * c1 = new TCanvas( metregion.c_str(), "met", 800, 800 );
  c1->cd();
  drawMllPlot(metregion, "mll", 20);
  c1->cd();
  drawRatio(metregion, "mll", 20);
  c1->SaveAs(Form("~/Desktop/mll_%s.pdf", metregion.c_str()));
  
  return 0;
  
}

int drawMllPlots()
{
  
  drawAllPlots( "met80" );
  drawAllPlots( "met100" );
  drawAllPlots( "met120" );
  drawAllPlots( "met150" );
  drawAllPlots( "met200" );
  return 0;
}

int drawMllPlot( const string metregion, const string variable,
				 Float_t binwidth, 
				 Float_t xmin, Float_t xmax, 
				 Float_t ymin, Float_t ymax )
{

  TFile * file = NULL;
  file = TFile::Open("photon_template_MET_data_2jetbins_all.root","READ");

  TH1F * h_zjets   = NULL;
  TH1F * h_fsbkg   = NULL;
  TH1F * h_vv      = NULL;
  TH1F * h_rare    = NULL;
  TH1F * h_data    = NULL;
  THStack * stack = new THStack("bgstack", "");

  h_zjets =       (TH1F*)file->Get( Form("h_%s_ll_zjets_%s", variable.c_str(), metregion.c_str() ) );
  h_rare  =       (TH1F*)file->Get( Form("h_%s_ll_rare_%s" , variable.c_str(), metregion.c_str() ) );
  h_data  =       (TH1F*)file->Get( Form("h_%s_ll_data_%s" , variable.c_str(), metregion.c_str() ) );
  h_fsbkg =       (TH1F*)file->Get( Form("h_%s_em_data_%s" , variable.c_str(), metregion.c_str() ) );
  h_vv    =       (TH1F*)file->Get( Form("h_%s_ll_wz_%s"   , variable.c_str(), metregion.c_str() ) );
  h_vv    -> Add ((TH1F*)file->Get( Form("h_%s_ll_zz_%s"   , variable.c_str(), metregion.c_str() ) ));


  TPad *padh = new TPad("p_hist", "p_hist", 0.0, 0.0, 1.0, 0.8);
  padh->SetBottomMargin(0.12);
  padh->SetRightMargin(0.07);
  padh->SetLeftMargin(0.18);
  padh->Draw();
  padh->cd();

  h_zjets -> Rebin(binwidth);
  h_rare  -> Rebin(binwidth);
  h_data  -> Rebin(binwidth);
  h_fsbkg -> Rebin(binwidth);
  h_vv    -> Rebin(binwidth);

  // if ( metregion == "met80"  ) h_zjets -> Scale( 64.5/21.534    );
  // if ( metregion == "met100" ) h_zjets -> Scale( 7.8/2.357      );
  // if ( metregion == "met120" ) h_zjets -> Scale( 3.7/2.657      );
  if ( metregion == "met80"  ) h_zjets -> Scale( (64.5 + 7.8 + 3.7 + 2.0 + 0.4) / (21.534 + 2.357 + 2.657) );
  if ( metregion == "met100" ) h_zjets -> Scale( (       7.8 + 3.7 + 2.0 + 0.4) / (         2.357 + 2.657) );
  if ( metregion == "met120" ) h_zjets -> Scale( (             3.7 + 2.0 + 0.4) /                   2.657  );
  if ( metregion == "met150" ) h_zjets -> SetBinContent( 5, 2.0 );
  if ( metregion == "met200" ) h_zjets -> SetBinContent( 5, .4  );

  h_zjets -> GetXaxis()->SetRangeUser(xmin,xmax);
  h_rare  -> GetXaxis()->SetRangeUser(xmin,xmax);
  h_data  -> GetXaxis()->SetRangeUser(xmin,xmax);
  h_fsbkg -> GetXaxis()->SetRangeUser(xmin,xmax);
  h_vv    -> GetXaxis()->SetRangeUser(xmin,xmax);

  Float_t maxy = ymax;
  if ( h_data -> GetMaximum() > maxy ) {
	maxy = h_data -> GetMaximum() * 1.5;
	if ( metregion == "met150" ) maxy = h_data -> GetMaximum() * 1.75;
	if ( metregion == "met200" ) maxy = h_data -> GetMaximum() * 2.25;
  }

  h_data  -> GetYaxis()->SetRangeUser(ymin,maxy);

  for ( unsigned int bini = (unsigned int)xmax/binwidth+1; bini < (unsigned int)h_data -> GetNbinsX() ; bini++ ){
	
	h_zjets -> Fill( xmax , h_zjets -> GetBinContent(bini) );
	h_rare  -> Fill( xmax , h_rare  -> GetBinContent(bini) );
	h_data  -> Fill( xmax , h_data  -> GetBinContent(bini) );
	h_fsbkg -> Fill( xmax , h_fsbkg -> GetBinContent(bini) );
	h_vv    -> Fill( xmax , h_vv    -> GetBinContent(bini) );

  }

  h_data -> GetXaxis()->SetTitle("dilepton mass [GeV]");
  //h_data -> GetXaxis()->SetTitleOffset(1.2);
  h_data -> GetXaxis()->SetTitleSize(0.05);
  h_data -> GetYaxis()->SetTitle(Form("entries / %.0f GeV", binwidth ) );
  //h_data -> GetYaxis()->SetTitleOffset(1.4);
  h_data -> GetYaxis()->SetTitleOffset(1.2);
  h_data -> GetYaxis()->SetTitleSize(0.05);

  h_data -> SetMarkerStyle(20);

  h_zjets   -> SetFillColor( 50           );//kCyan
  h_rare    -> SetFillColor( kMagenta - 5 );//kBlue - 3
  h_fsbkg   -> SetFillColor( 42           );//kYellow
  h_vv      -> SetFillColor( 31           );//kYellow

  stack -> Add( h_rare  );
  stack -> Add( h_vv    );
  stack -> Add( h_fsbkg );
  stack -> Add( h_zjets );

  h_zjets   -> SetFillStyle(1001); 
  h_rare    -> SetFillStyle(1001); 
  h_fsbkg   -> SetFillStyle(1001); 
  h_vv      -> SetFillStyle(1001); 

  h_data -> Draw("");
  stack  -> Draw("samehist");
  h_data -> Draw("sameE1");

  padh->cd()->RedrawAxis();

  //Draw Legend
  TLegend *l1 = new TLegend(0.60, 0.60, 0.90, 0.90);    
  l1->SetLineColor(kWhite);    
  l1->SetShadowColor(kWhite);    
  l1->SetFillColor(kWhite);    
  l1->AddEntry(h_data , "data"            , "p");
  l1->AddEntry(h_zjets, "Z+Jets"          , "f");
  l1->AddEntry(h_fsbkg, "Flavor Symmetric", "f");
  l1->AddEntry(h_vv   , "WZ+ZZ"           , "f");
  l1->AddEntry(h_rare , "Rare SM"         , "f");
  l1->Draw();

  if (metregion == "met80"  ) drawTex( 0.25, 0.85, false, "ee/#mu#mu events", "E^{miss}_{T} > 80 GeV"  );
  if (metregion == "met100" ) drawTex( 0.25, 0.85, false, "ee/#mu#mu events", "E^{miss}_{T} > 100 GeV" );
  if (metregion == "met120" ) drawTex( 0.25, 0.85, false, "ee/#mu#mu events", "E^{miss}_{T} > 120 GeV" );
  if (metregion == "met150" ) drawTex( 0.25, 0.85, false, "ee/#mu#mu events", "E^{miss}_{T} > 150 GeV" );
  if (metregion == "met200" ) drawTex( 0.25, 0.85, false, "ee/#mu#mu events", "E^{miss}_{T} > 200 GeV" );
  // drawTex(Float_t bottomleft, Float_t topright, bool istargeted, string thirdline)

  return 0;
}

int drawRatio( const string metregion, const string variable,
			   Float_t binwidth, 
			   Float_t xmin, Float_t xmax, 
			   Float_t ymin, Float_t ymax )
{

  TFile * file = NULL;
  file = TFile::Open("photon_template_MET_data_2jetbins_all.root","READ");

  TH1F * h_allbg   = NULL;
  TH1F * h_zjets   = NULL;
  TH1F * h_data    = NULL;

  TH1F * h_fsbkg   = NULL;

  TH1F * h_mc   = NULL;
  TH1F * ratio  = NULL;
  TH1F * ratioerr  = NULL;

  h_fsbkg = (TH1F*)file->Get( Form("h_%s_em_data_%s", variable.c_str(), metregion.c_str() ) )->Clone("h_fsbkg");

  h_allbg =       (TH1F*)file->Get( Form("h_%s_em_data_%s", variable.c_str(), metregion.c_str() ) );
  h_allbg ->Add  ((TH1F*)file->Get( Form("h_%s_ll_rare_%s" , variable.c_str(), metregion.c_str() ) ));
  h_allbg ->Add  ((TH1F*)file->Get( Form("h_%s_ll_wz_%s" , variable.c_str(), metregion.c_str() ) ));
  h_allbg ->Add  ((TH1F*)file->Get( Form("h_%s_ll_zz_%s" , variable.c_str(), metregion.c_str() ) ));

  h_zjets =       (TH1F*)file->Get( Form("h_%s_ll_zjets_%s", variable.c_str(), metregion.c_str() ) );
  h_data  =       (TH1F*)file->Get( Form("h_%s_ll_data_%s" , variable.c_str(), metregion.c_str() ) );

  TPad *pad = new TPad("p_hist", "p_hist", 0.0, 0.8, 1.0, 1.0);
  pad->SetBottomMargin(0.12);
  pad->SetRightMargin(0.07);
  pad->SetLeftMargin(0.18);
  pad->SetTopMargin(0.1);
  pad->Draw();
  pad->cd();

  h_mc    = h_allbg;
  ratio   = h_data;

  ratio -> Rebin(binwidth);
  h_allbg -> Rebin(binwidth);
  h_fsbkg -> Rebin(binwidth);
  h_zjets -> Rebin(binwidth);

  if ( metregion == "met80"  ) h_zjets -> Scale( (64.5 + 7.8 + 3.7 + 2.0 + 0.4) / (21.534 + 2.357 + 2.657) );
  if ( metregion == "met100" ) h_zjets -> Scale( (       7.8 + 3.7 + 2.0 + 0.4) / (         2.357 + 2.657) );
  if ( metregion == "met120" ) h_zjets -> Scale( (             3.7 + 2.0 + 0.4) /                   2.657  );
  if ( metregion == "met150" ) h_zjets -> SetBinContent( 5, 2.0 );
  if ( metregion == "met200" ) h_zjets -> SetBinContent( 5, .4  );

  ratio -> GetXaxis()->SetRangeUser(xmin,xmax);
  h_allbg -> GetXaxis()->SetRangeUser(xmin,xmax);
  h_zjets -> GetXaxis()->SetRangeUser(xmin,xmax);

  for ( unsigned int bini = (unsigned int)xmax/binwidth+1; bini < (unsigned int)h_allbg -> GetNbinsX() + 1; bini++ ){

	h_allbg -> Fill( xmax , h_allbg  -> GetBinContent(bini) );
	h_fsbkg -> Fill( xmax , h_fsbkg  -> GetBinContent(bini) );
	h_zjets -> Fill( xmax , h_zjets -> GetBinContent(bini) );
    ratio   -> Fill( xmax , ratio  -> GetBinContent(bini) );

  }

  h_allbg -> Add( h_zjets );

  ratio -> SetLineColor(kBlack);

  // ratio->SetLineWidth(2);

  ratio -> SetMarkerStyle(20);
  // ratio -> SetMarkerSize(0.5);

  ratio -> GetXaxis() ->SetRangeUser( xmin, xmax );
  h_mc  -> GetXaxis() ->SetRangeUser( xmin, xmax );

  for ( unsigned int bini = 0; bini < (unsigned int)h_allbg -> GetNbinsX() + 1; bini++ ){
  	h_allbg -> SetBinError( bini, 0.0 );
  }
  ratio->Divide(h_mc);

  ratio->GetXaxis()->SetLabelSize(0);

  // pad->SetGridy(1);

  // ratio->GetXaxis()->SetLabelSize(0);
  ratio->GetYaxis()->SetRangeUser(0.0,2.0);
  ratio->GetYaxis()->SetNdivisions(5);
  ratio->GetYaxis()->SetTitle("ratio");
  //ratio->GetYaxis()->SetTitleSize(0.15);
  ratio->GetYaxis()->SetTitleSize(0.2);
  //ratio->GetYaxis()->SetTitleOffset(0.37);
  ratio->GetYaxis()->SetTitleOffset(0.32);
  ratio->GetYaxis()->SetLabelSize(0.5);


  ratio->SetTitle("");
  // ratio->GetXaxis()->SetLabelSize(0);
  ratio->GetYaxis()->SetLabelSize(0.15);

  ratioerr = (TH1F*)ratio->Clone("ratioerr");
  ratioerr->SetFillColor(kBlue+1);
  ratioerr->SetFillStyle(3004);
  ratioerr->SetMarkerSize(0);

  for( Int_t ind = 0; ind < ratioerr -> GetNbinsX()+1; ind++ ){
	ratioerr -> SetBinContent( ind, 1.0 );
	cout<<"fsbkg: "<<h_fsbkg -> GetBinContent(ind)<<endl;
	cout<<"allbg: "<<h_allbg -> GetBinContent(ind)<<endl;
	ratioerr -> SetBinError( ind, sqrt( h_fsbkg -> GetBinContent(ind) + pow(h_zjets -> GetBinContent(ind)*0.3,2) )/h_allbg->GetBinContent(ind) );
  }

  ratioerr -> SetBinError( 5, 0.19 );


  ratio->Draw("lpE1");
  gStyle->SetErrorX(0.0);
  ratioerr -> Draw("sameE2");

  TLine * mainaxis = new TLine(xmin, 1.0, xmax, 1.0);
  mainaxis->SetLineWidth(2);
  mainaxis->Draw("same");
  // c1->SaveAs()

  return 0;
}
