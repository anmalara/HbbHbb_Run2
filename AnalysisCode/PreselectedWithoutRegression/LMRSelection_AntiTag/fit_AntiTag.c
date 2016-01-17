{
  gSystem->Load("../../PDFs/GaussExp_cxx.so");
  gROOT->LoadMacro("../../BackgroundPrediction_AntiTag_GaussExp.cc");
  BackgroundPrediction_AntiTag_GaussExp(150, 800, 10, // range of plot, binning
                                        250, 700, // range of fit
                                        250, 300,  // range of gaussExp mean
                                        10,  100,   // range of gaussExp width
                                        0.01, 3.1, // range of gaussExp exponent
                                        "h_mX_SB_kinFit", "h_mX_SR_kinFit", 
                                        "lin");
}