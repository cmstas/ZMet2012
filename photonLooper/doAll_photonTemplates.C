{

  gROOT->ProcessLine(".L histtools.C+");
  gROOT->ProcessLine(".L runPhotonTemplates.C+");
  //gSystem->Load("../Tools/MiniFWLite/libMiniFWLite.so");
  
  //runPhotonTemplates("V00-00-11","Photon");
  //runPhotonTemplates("V00-01-00","DoubleElectron");
  runPhotonTemplates("V00-02-03","data_53X_2012ALL");
  
}
