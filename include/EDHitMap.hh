/* ============= HITMAP ============== *
 * Author: J. McElwee                  *
 * Created: 17-08-2024                 *
 * Email: mcelwee@lp2ib.in2p3.fr       *
 *                                     *
 * Hitmap of the raw data to check if  *
 * for the position of the beamspot.   *
 *                                     *
 * =================================== */

#ifndef EDHITMAP_HH
#define EDHITMAP_HH

#include <vector>

#include "TFile.h"
#include "TTree.h"
#include "TH2D.h"

#include "Messaging.hh"

#include "EDMapping24.hh"

class EDHitMap
{
private:

    // File and tree information
    TFile m_curFile {};
    TTree *m_curTree {nullptr};

    // Tree information 
    short m_HG[64], m_LG[64];
    short m_HG_sort[20][64], m_LG_sort[20][64];
    unsigned char m_board;

    MapObj m_maps;

   	std::vector<TH2D*> m_HitMap = {nullptr};


public:
    // --- Constructors ---
    EDHitMap();
    EDHitMap(const char *infile);
    EDHitMap(const char *infile, const char *intree); 
    ~EDHitMap();

    // ---- Methods ----
    void SetBranches();
    void FillHist(int evnt = -1);
    void LoadMap(std::string ICCon, std::string ICJanus);

    std::vector<TH2D*> GetHitMap() { return m_HitMap; };
};


#endif