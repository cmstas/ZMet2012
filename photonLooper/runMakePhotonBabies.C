#include "TChain.h"
#include "makePhotonBabies.C"


void pickSkimIfExists( TChain *ch, const std::string& base )
{

  TChain *dummy = new TChain("Events");
  int nFiles = 0;
  if (dummy->Add(base.c_str())) {
    nFiles = ch->Add(base.c_str());
    std::cout << "Main " <<base.c_str() << " exists: use it. Loaded " 
              << nFiles << " files" << std::endl;
  } else{
    std::cout << "Didn't find sample " << base << " , quitting" << std::endl;
    exit(0);
  }

  // be paranoid
  if (nFiles == 0) {
    std::cout << "ERROR: expected to read files " 
              << base.c_str() << "  but found none" << std::endl;
    assert(0);
  }

  return;
}


void runMakePhotonBabies(char* prefix , bool isData = true, float kFactor = 1.){

  TChain* ch = new TChain("Events");

  //-----------------------------------------------------------------------------------

  if( strcmp( prefix , "data_53X_2012A" ) == 0 ){    
    //pickSkimIfExists(ch,"PhotonTriggerSkim_slim/DoubleElectron_Run2012A-13Jul2012-v1_AOD/V05-03-18_slim/merged_ntuple_999999_9_1_skim.root");
    pickSkimIfExists(ch,"PhotonTriggerSkim_slim/DoubleElectron_Run2012A-13Jul2012-v1_AOD/V05-03-18_slim/merged*root");
    pickSkimIfExists(ch,"PhotonTriggerSkim_slim/DoubleElectron_Run2012A-recover-06Aug2012-v1_AOD/V05-03-18_slim/merged*root");
  }

  //-----------------------------------------------------------------------------------

  else if( strcmp( prefix , "data_53X_2012B" ) == 0 ){    
    pickSkimIfExists(ch,"PhotonTriggerSkim_slim/DoubleElectron_Run2012B-13Jul2012-v1_AOD/V05-03-18_slim/merged*root");
  }

  //-----------------------------------------------------------------------------------

  else if( strcmp( prefix , "data_53X_2012C" ) == 0 ){    
    pickSkimIfExists(ch,"PhotonTriggerSkim_slim/DoubleElectron_Run2012C-24Aug2012-v1_AOD/V05-03-18_slim/merged*root");
    pickSkimIfExists(ch,"PhotonTriggerSkim_slim/DoubleElectron_Run2012C-PromptReco-v2_AOD/V05-03-18_slim/merged*root");
  }

  //-----------------------------------------------------------------------------------

  else if( strcmp( prefix , "data_53X_2012D" ) == 0 ){    
    pickSkimIfExists(ch,"PhotonTriggerSkim_slim/DoubleElectron_Run2012D-PromptReco-v1_AOD/V05-03-18_slim/merged*root");
  }

  //-----------------------------------------------------------------------------------

  else if( strcmp( prefix , "Photon" ) == 0 ){
    pickSkimIfExists(ch,"/hadoop/cms/store/user/cwelke/CMSSW_5_2_3_patch4_V05-02-27/Photon_Run2012A-PromptReco-v1_AOD/unmerged/store*root");
    pickSkimIfExists(ch,"/hadoop/cms/store/user/cwelke/CMSSW_5_2_3_patch4_V05-02-27/SinglePhoton_Run2012B-PromptReco-v1_AOD/unmerged/store*root");
  }

  //-----------------------------------------------------------------------------------

  else if( strcmp( prefix , "DoubleElectron" ) == 0 ){
    pickSkimIfExists(ch,"PhotonTriggerSkim/DoubleElectron_Run2012A-13Jul2012-v1_AOD/V05-03-13/merged*root");
    pickSkimIfExists(ch,"PhotonTriggerSkim/DoubleElectron_Run2012A-recover-06Aug2012-v1_AOD/V05-03-13/merged*root");
    pickSkimIfExists(ch,"PhotonTriggerSkim/DoubleElectron_Run2012B-13Jul2012-v1_AOD/V05-03-13/merged*root");
    pickSkimIfExists(ch,"PhotonTriggerSkim/DoubleElectron_Run2012C-PromptReco-v1_AOD/V05-03-13/merged*root");
    pickSkimIfExists(ch,"PhotonTriggerSkim/DoubleElectron_Run2012C-PromptReco-v2_AOD/V05-03-13/merged*root");
  }
  
  //-----------------------------------------------------------------------------------

  else if( strcmp( prefix , "DoubleElectron_2012Cv2" ) == 0 ){
    pickSkimIfExists(ch,"PhotonTriggerSkim/DoubleElectron_Run2012C-PromptReco-v2_AOD/V05-03-13/merged*root");
  }
  
  //-----------------------------------------------------------------------------------

  else{
    cout << "ERROR: cannot find sample " << prefix << endl;
    exit(0);
  }

  //-----------------------------------------------------------------------------------
    
  bool calculateTCMET = false;  //recalculate tcmet on-the-fly?
  
  cout << endl;
  cout << "Checking for corrupt files" << endl;
  cout << "Entries " << ch->GetEntries() << endl;
  ch->Draw("evt_run");
  cout << endl;
  
  makePhotonBabies* myLooper = new makePhotonBabies();
  
  cout << "Running on sample " << prefix << endl;
  myLooper->ScanChain(ch, prefix, isData, calculateTCMET, -1 ,kFactor);
  
}

