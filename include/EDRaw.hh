/* ============== EDRAW ============== *
 * Author: J. McElwee                  *
 * Created: 19-08-2024                 *
 * Email: mcelwee@lp2ib.in2p3.fr       *
 *                                     *
 * Histogram filling for the raw data  * 
 * output from the boards.             *
 *                                     *
 * =================================== */

#ifndef EDRAW_HH
#define EDRAW_HH

#include "EDHitMap.hh"

class EDRaw : public EDHitMap
{
private:

    // Tree information 
    unsigned char m_board;
    short m_HG_raw[64], m_LG_raw[64];


public:
    // --- Constructors ---
    EDRaw(const char *infile);
    EDRaw(const char *infile, const char *intree);
    EDRaw(const char *infile, int FERS); 
    EDRaw(const char *infile, const char *intree, int FERS); 
    ~EDRaw();

    // ---- Methods ----
    void SetBranches()         override;
    void FillHist(int inEvent) override;

};


#endif // Header Guard