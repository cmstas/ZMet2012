{

  //gSystem->Load("../../MiniFWLite/libMiniFWLite.so");

  #include "babylooper.h"

  gROOT->ProcessLine(".L histtools.C+");
  gROOT->ProcessLine(".L runBabyLooper.C+");

  char* Z_version        = "V00-02-13";
  char* template_version = "V00-02-03";
  
  runBabyLooper(Z_version,template_version, "data_53X_2012ALL" , true , babylooper::e_ZSelection  );
  //runBabyLooper(Z_version,template_version, "wz"          , false  , babylooper::e_ZSelection  );
  //runBabyLooper(Z_version,template_version, "zz"          , false  , babylooper::e_ZSelection  );
  //runBabyLooper(Z_version,template_version, "wz"          , false  , babylooper::e_ZSelection  );
  //runBabyLooper(Z_version,template_version, "zjets"       , false  , babylooper::e_ZSelection  );
  //runBabyLooper(Z_version,template_version, "LM4"         , false  , babylooper::e_ZSelection  );

  
}

