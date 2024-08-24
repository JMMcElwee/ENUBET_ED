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
    // ----- ROOT File Input -----
    TFile m_curFile {};
    TTree *m_curTree {nullptr};
    // ---------------------------


    bool m_IsDrawn = false; 

    std::string m_dir = "/Users/jmcelwee/Documents/testbeam2023/data/";


public:
    // ---- Constructors ----
    EDHist(const char *infile);
    EDHist(const char *infile, const char *intree);
    virtual ~EDHist();

    // ---- Methods ----
    void SetDrawn(bool bIsDrawn);
    bool IsDrawn() { return m_IsDrawn; };

    // ROOT Stuff
    virtual void SetBranches() = 0;
    virtual void FillHist(int inEvent) = 0;


};


#endif // Header guard



