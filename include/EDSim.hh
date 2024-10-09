/* ============== EDSIM ============== *
 * Author: J. McElwee                  *
 * Created: 07-10-2024                 *
 * Email: mcelwee@lp2ib.in2p3.fr       *
 *                                     *
 * Histogram filling for the simu      * 
 * data output from the boards.        *
 *                                     *
 * =================================== */

#ifndef EDSIM_HH
#define EDSIM_HH

#include "EDHitMap.hh"

using namespace std;

class EDSim : public EDHitMap
{
private:

    // Tree information 
    vector<int> *m_r = nullptr,
                *m_phi = nullptr, 
                *m_z = nullptr;
    vector<double> *m_EDep = nullptr;



public:
    // --- Constructors ---
    EDSim(const char *infile);
    EDSim(const char *infile, const char *intree);
    EDSim(const char *infile, int FERS); 
    EDSim(const char *infile, const char *intree, int FERS); 
    ~EDSim();

    // ---- Methods ----
    void SetBranches()         override;
    void FillHist(int inEvent) override;

};


#endif // Header Guard