/* ============ EDHITMAP ============= *
 * Author: J. McElwee                  *
 * Created: 19-08-2024                 *
 * Email: mcelwee@lp2ib.in2p3.fr       *
 *                                     *
 * Information about the main display  *
 * on the cancas. This controls the    *
 * filling and drawing.                *
 *                                     *
 * =================================== */

#ifndef EDHITMAP_HH
#define EDHITMAP_HH

#include <string>

#include "TMath.h"
#include "TH2Poly.h"

#include "EDHist.hh"
#include "EDMapping.hh"
#include "EDMapping24.hh"

class EDHitMap : public EDHist
{
public:

    // ----- SETTINGS -----------
    enum EMapYear
    {
        k2023 = 0,
        k2024 = 1,
    };
    // --------------------------

    // ----- Constructors -------
    EDHitMap(const char *infile);
    EDHitMap(const char *infile, const char *intree);
    EDHitMap(const char *infile, int FERS); 
    EDHitMap(const char *infile, const char *intree, int FERS); 
    ~EDHitMap();
    // ---------------------------

    // ---- Methods --------------
    void LoadMap(std::string inMap,
                 std::string mapDir = "/Users/jmcelwee/Documents/testbeam2023/tools/TestBeam23/Mapping/",
                 EMapYear year = k2024);
    // ---------------------------


    // ---- Access Functions -----
    int GetFERS() { return m_FERS; };

    std::vector<TH2D*>    GetHitMap() { return m_HitMap; };
    std::vector<TH2Poly*> GetArc() { return m_ArcMap; };

    TH3D *GetEventDisplay() { return EventDisplay; };
    // ---------------------------


    // ----- Arc stuff -----------
    TH2Poly* CreateArcHist(std::string histName);
    void     FillArc(TH2Poly* hist, double phi, double R, double weight);
    // ---------------------------



protected:

    // ----- Draw arc ------------
    const int nBinsRadius = 5;          // Number of radial bins
    const int nBinsAngle = 25;          // Number of angular bins (opening angle of 2π/200 each)
    const int nSegments = 50;           // Number of segments to approximate the arc
    const double radiusMin = 97.0;      // Minimum radius in cm
    const double radiusMax = 109.0;     // Maximum radius in cm
    const double angleIncrement = 2 * TMath::Pi() / 200; // Angle increment for each bin
    // ---------------------------

    // ----- Tree ----------------
    int m_FERS = 4;
    int m_Anodes = 60;
    // ---------------------------

    // ----- Mapping -------------
    // 2024
    MapObj m_maps;

    // 2023
    std::map<std::vector<int>, std::vector<int>> m_anodeMap;
    std::map<std::vector<int>, std::vector<int>> m_coordMap;
    // ---------------------------

    // ----- Output plots -------- 
    // Hit map vectors 
    std::vector<TH2D*> m_HitMap = {nullptr};    
    std::vector<TH2Poly*> m_ArcMap = {nullptr};

    // 3D display
    TH3D *EventDisplay = new TH3D();
    // ---------------------------

};



#endif // Header Guard