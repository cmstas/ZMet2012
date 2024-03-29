#include "TChain.h"
#include "makePhotonTemplates.C"

void runPhotonTemplates( char* iter , char* sample ){

  TChain* ch = new TChain("T1");

  //string file = Form("../photon_output/%s/%s_baby_2jets.root",iter,sample);
  string file = Form("../photon_output/%s/%s_baby_2jets_mjj70to110.root",iter,sample);

  cout << "Adding " << file << endl;

  ch->Add( file.c_str() );

  cout << "Entries " << ch->GetEntries() << endl;

  makePhotonTemplates* myLooper = new makePhotonTemplates();
  
  myLooper->ScanChain( ch , iter , sample );
  
}

