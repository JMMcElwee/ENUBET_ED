#include <iostream>
#include <map>
#include <vector>
#include <numeric>
#include <list>

#include <unistd.h>
#include <getopt.h>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TH1D.h"
#include "TH2D.h"

#include "TApplication.h"

#include "EventDisplay.hh"


int main(int argc, char** argv)
{

  TApplication theApp("App", &argc, argv);

  // Popup the GUI...
  new EventDisplay(gClient->GetRoot(),600,500);
  
  theApp.Run();
  
  return 0;
}
