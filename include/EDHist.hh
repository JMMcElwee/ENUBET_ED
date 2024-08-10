/* ============= EDHIST ============== *
 * Author: J. McElwee                  *
 * Created: 24-07-2024                 *
 * Email: mcelwee@lp2ib.in2p3.fr       *
 *                                     *
 * Control the plotting for the        *
 * histograms and controlling the ROOT *
 * file.                               *
 *                                     *
 * =================================== */

#ifndef EDHIST_HH
#define EDHIST_HH

#include <iostream>
#include <map>
#include <vector>
#include <numeric>

#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TAxis.h"

#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"

#include "EDMapping.hh"

#include "Messaging.hh"

typedef std::vector<TH1D*> THV;

class EDHist 
{

protected:
    TFile m_curFile {};
    TTree *m_curTree {nullptr};

    const char *m_intree = "t";

    int m_FERS = 4;
    int m_Anodes = 60; 

    // This is not the best way to do 
    // it, but will have to do for now
    short m_HG[10*60], m_LG[10*60];
    UShort_t digiPH[8], digiTime[8];

    std::string m_dir = "/Users/jmcelwee/Documents/testbeam2023/data/";
    std::string m_mapDir = "/Users/jmcelwee/Documents/testbeam2023/tools/TestBeam23/Mapping/";
    std::string m_map = "Mapping2023_v2.txt";

    std::map<std::vector<int>, std::vector<int>> m_anodeMap;
    std::map<std::vector<int>, std::vector<int>> m_coordMap;

    TH3D *event_display = new TH3D();
    TH2D *cherPH = new TH2D();


public:
    // --- Constructors ---
    EDHist(const char *infile);
    EDHist(const char *infile, const char *intree);
    EDHist(const char *infile, int FERS, int anodes); 
    EDHist(const char *infile, const char *intree, int FERS, int anodes); 
    ~EDHist();

    // ROOT Stuff
    void SetBranches();

    void LoadMap();

    void FillHist();
    void FillCherenkov();

    void Events3D(const std::vector<THV> &hist_lg, const std::vector<THV> &hist_hg);


    // Access Function
    TH2D *GetCher() { return cherPH; };
    TH3D *GetED() { return event_display; };

};



#endif // Header guard