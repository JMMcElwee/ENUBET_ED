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

//#include "MappingScript.h"
// #include "system.h"

// #include "ed_z.h"
// #include "ed_phi.h"
// #include "ed_r.h"
// #include "ed_3D.h"

// #include "flag.h"
// #include "binning.h"



int main(int argc, char** argv)
{

/*  gROOT->ProcessLine( "gErrorIgnoreLevel = 1001;");

  // === COMMAND LINE FLAGS ========
  int nReqArg = 1;

  // ----- Flag defaults -----
  int fRunNo = 1418;
  int fEvent = -1;
  std::string fPath = "../../../data/";
  std::string fRunName = "run";
  std::string fOutput = "./plots";
  std::string fMap = "../Mapping";
  bool sGIF = false;
  int fDimension = 3;
  int fPhiBin[2] = {0,17};
  int fnZ = 3;
  int fFERS = 4;
  int fAnodes = 60;

  // ----- Set long flag names -----
  const char* short_opts = "hr:p:n:o:e:gd:s:f:z:F:a:m:";
  static struct option long_opts[15] = {
    {"help", no_argument, NULL, 'h'},
    {"run-number", required_argument, NULL, 'r'},
    {"path", required_argument, NULL, 'p'},
    {"run-name", required_argument, NULL, 'n'},
    {"output", required_argument, NULL, 'o'},
    {"event", required_argument, NULL, 'e'},
    {"gif", no_argument, NULL, 'g'},
    {"dimension", required_argument, NULL, 'd'},
    {"phi-start", required_argument, NULL, 's'},
    {"phi-end", required_argument, NULL, 'f'},
    {"zlayers", required_argument, NULL, 'z'},
    {"number-FERS", required_argument, NULL, 'F'},
    {"number-anodes", required_argument, NULL, 'a'},
    {"map-path", required_argument, NULL, 'm'},
    {nullptr, no_argument, nullptr, 0}
  };

  
  // ----- Loop over the flags -----
  int opt,option_index;
  //  optind =  nReqArg + 1; // Only if there is a required argument
  while ((opt = getopt_long(argc, argv, short_opts, long_opts, &option_index)) != -1) {
    switch(opt) {
    case 'h':
      //      help();
      return 0;
    case 'r':
      fRunNo = std::atoi(optarg);
      break;
    case 'p':
      fPath = optarg;
      break;
    case 'n':
      fRunName = optarg;
      break;
    case 'o':
      fOutput = optarg;
      break;
    case 'e':
      fEvent = std::atoi(optarg);
      break;
    case 'g':
      sGIF = true;
      break;
    case 'd':
      fDimension = std::atoi(optarg);
        //     std::cout << H_INFO << "Saving event as 1D Histograms." << std::endl;
      break;
    case 's':
      fPhiBin[0] = std::atoi(optarg);
      break;
    case 'f':
      fPhiBin[1] = std::atoi(optarg);
      break;
    case 'z':
      fnZ = std::atoi(optarg);
      break;
    case 'F':
      fFERS = std::atoi(optarg);
      break;
    case 'a':
      fAnodes = std::atoi(optarg);
      break;
    case 'm':
      fMap = optarg;
      break;
    case ':':
      printf("\033[1;31m[ERROR]\033[0m -%c requires an argument.\n",optopt);
      return 0;
    case '?':
      printf("\033[1;33m[ERROR]\033[0m -%c is an unknown argument... just ignoring it.\n",optopt);
      break;
    }
  }

*/

  TApplication theApp("App", &argc, argv);

  // Popup the GUI...
  new EventDisplay(gClient->GetRoot(),600,500);
  
  theApp.Run();
  
  return 0;
}
