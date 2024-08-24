/* ============ EDEVTMATCH =========== *
 * Author: J. McElwee                  *
 * Created: 19-08-2024                 *
 * Email: mcelwee@lp2ib.in2p3.fr       *
 *                                     *
 * Histogram filling for the processed * 
 * data output from the boards.        *
 *                                     *
 * =================================== */

#ifndef EDEVTMATCH_HH
#define EDEVTMATCH_HH

#include "EDHitMap.hh"

class EDEvtMatch : public EDHitMap
{
private:

    // Tree information 
    short m_HG_sort[20][64], m_LG_sort[20][64];


public:
    // --- Constructors ---
    EDEvtMatch(const char *infile);
    EDEvtMatch(const char *infile, const char *intree);
    EDEvtMatch(const char *infile, int FERS); 
    EDEvtMatch(const char *infile, const char *intree, int FERS); 
    ~EDEvtMatch();

    // ---- Methods ----
    void SetBranches()         override;
    void FillHist(int inEvent) override;

};


#endif // Header Guard