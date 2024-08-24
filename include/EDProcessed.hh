/* =========== EDPROCESSED =========== *
 * Author: J. McElwee                  *
 * Created: 19-08-2024                 *
 * Email: mcelwee@lp2ib.in2p3.fr       *
 *                                     *
 * Histogram filling for the raw.      * 
 * data output from the boards.        *
 *                                     *
 * =================================== */

#ifndef EDPROCESSED_HH
#define EDPROCESSED_HH

#include "EDHitMap.hh"

class EDProcessed : public EDHitMap
{
private:

    // Tree information 
    short m_HG_proc[10*60], m_LG_proc[10*60];


public:
    // --- Constructors ---
    EDProcessed(const char *infile);
    EDProcessed(const char *infile, const char *intree);
    EDProcessed(const char *infile, int FERS); 
    EDProcessed(const char *infile, const char *intree, int FERS); 
    ~EDProcessed();

    // ---- Methods ----
    void SetBranches()         override;
    void FillHist(int inEvent) override;

};


#endif // Header Guard