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
#include "TH2Poly.h"
#include "TMath.h"
#include "TRandom.h"

#include "Messaging.hh"

#include "EDMapping24.hh"

class EDHitMap
{
private:

	// For arc drawing
	const int nBinsRadius = 5;          // Number of radial bins
    const int nBinsAngle = 25;          // Number of angular bins (opening angle of 2π/200 each)
    const int nSegments = 50;           // Number of segments to approximate the arc
    const double radiusMin = 97.0;      // Minimum radius in cm
    const double radiusMax = 109.0;     // Maximum radius in cm
    const double angleIncrement = 2 * TMath::Pi() / 200; // Angle increment for each bin

    // File and tree information
    TFile m_curFile {};
    TTree *m_curTree {nullptr};

    // Tree information 
    short m_HG[64], m_LG[64];
    short m_HG_sort[20][64], m_LG_sort[20][64];
    unsigned char m_board;

    // Mapping 
    MapObj m_maps;

    // Output vectors of plots 
   	std::vector<TH2D*> m_HitMap = {nullptr};   	
   	std::vector<TH2Poly*> m_ArcMap = {nullptr};


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

    TH2Poly* CreateArcHist(std::string histName);
    void FillArc(TH2Poly* hist, double phi, double R, double weight);
 

    std::vector<TH2D*> GetHitMap() { return m_HitMap; };
    std::vector<TH2Poly*> GetArc() { return m_ArcMap; };

};


#endif