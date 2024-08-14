/* =========== EDCHERENKOV =========== *
 * Author: J. McElwee                  *
 * Created: 11-08-2024                 *
 * Email: mcelwee@lp2ib.in2p3.fr       *
 *                                     *
 * Information about the Cherenkov     *
 * plots for the separate canvas.      *
 *                                     *
 * =================================== */

#ifndef EDCHERENKOV_HH
#define EDCHERENKOV_HH

#include "TLine.h"

#include "EDHist.hh"

class EDCherenkov : public EDHist
{
private:
    // Tree information 
    UShort_t digiPH[8], digiTime[8];

    // Cherenkov Histograms
    TH2D *CherPH   = new TH2D();
    TH2D *CherPHT1 = new TH2D();
    TH2D *CherPHT2 = new TH2D();


public:
    // --- Constructors ---
    EDCherenkov(const char *infile);
    EDCherenkov(const char *infile, const char *intree);
    ~EDCherenkov();

    // ---- Methods ----
    void SetBranches()             override;
    void FillHist(int inEvent = 0) override;

    // ---- Access Functions ----
    TH2D *GetCherPH()   { return CherPH; };
    TH2D *GetCherPHT1() { return CherPHT1; };
    TH2D *GetCherPHT2() { return CherPHT2; };
};



#endif // Header Guard