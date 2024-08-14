/* =========== EDCHERENKOV =========== *
 * Author: J. McElwee                  *
 * Created: 11-08-2024                 *
 * Email: mcelwee@lp2ib.in2p3.fr       *
 *                                     *
 * Information about the Cherenkov     *
 * plots for the separate canvas.      *
 *                                     *
 * =================================== */

#include "EDCherenkov.hh"

//**********************************************************
//***** CONSTRUCTORS ***************************************

// - - - - - - - - - - - - - - - - - - - - 
EDCherenkov::EDCherenkov(const char *infile)
    : EDHist(infile)
{}
// - - - - - - - - - - - - - - - - - - - - 


// - - - - - - - - - - - - - - - - - - - - 
EDCherenkov::EDCherenkov(const char *infile, const char *intree)
    : EDHist(infile, intree)
{}
// - - - - - - - - - - - - - - - - - - - - 


// - - - - - - - - - - - - - - - - - - - - 
EDCherenkov::~EDCherenkov()
{}
// - - - - - - - - - - - - - - - - - - - - 

//**********************************************************



//**********************************************************
//***** ACCESS FUNCTIONS ***********************************

// - - - - - - - - - - - - - - - - - - - - 

// - - - - - - - - - - - - - - - - - - - - 


// - - - - - - - - - - - - - - - - - - - - 

// - - - - - - - - - - - - - - - - - - - - 


// - - - - - - - - - - - - - - - - - - - - 

// - - - - - - - - - - - - - - - - - - - - 

//**********************************************************



//**********************************************************
//***** ROOT STUFF *****************************************

// - - - - - - - - - - - - - - - - - - - - 
void EDCherenkov::SetBranches()
{
  m_curTree->SetBranchAddress("digiPH", &digiPH[0]);
  m_curTree->SetBranchAddress("digiTime", &digiTime[0]);
}
// - - - - - - - - - - - - - - - - - - - - 

// - - - - - - - - - - - - - - - - - - - - 
void EDCherenkov::FillHist(int inEvent)
{

    TH2D *CherPHT1_temp = new TH2D("Cher1Time",";Cherenkov 1 Time of Arrival [Ticks]; Cherenkov 1 Pulse Amplitude [ADC Counts]",
                             100, 0, 500, 100, 0, 8000);
    TH2D *CherPHT2_temp = new TH2D("Cher2Time",";Cherenkov 2 Time of Arrival [Ticks]; Cherenkov 2 Pulse Amplitude [ADC Counts]",
                             100, 0, 500, 100, 0, 8000);

    TH2D *CherPH_temp = new TH2D("CherPH",";Cherenkov 1 Pulse Amplitude [ADC Counts]; Cherenkov 2 Pulse Amplitude [ADC Counts]",
                            100, 0, 8000, 100, 0, 8000);

    for (int evnt = 0; evnt < m_curTree->GetEntries(); evnt++){
        m_curTree->GetEntry(evnt);
        CherPHT1_temp->Fill(digiTime[1], digiPH[1]);
        CherPHT2_temp->Fill(digiTime[2], digiPH[2]);
        CherPH_temp->Fill(digiPH[1],digiPH[2]);
    }

    CherPHT1_temp->Copy(*CherPHT1);
    CherPHT2_temp->Copy(*CherPHT2);
    CherPH_temp->Copy(*CherPH);

}
// - - - - - - - - - - - - - - - - - - - - 


// - - - - - - - - - - - - - - - - - - - -

// - - - - - - - - - - - - - - - - - - - -

//**********************************************************





