/* ============ EDDISPLAY ============ *
 * Author: J. McElwee                  *
 * Created: 11-08-2024                 *
 * Email: mcelwee@lp2ib.in2p3.fr       *
 *                                     *
 * Information about the main display  *
 * on the cancas. This controls the    *
 * filling and drawing.                *
 *                                     *
 * =================================== */

#ifndef EDDISPLAY_HH
#define EDDISPLAY_HH

#include "EDHist.hh"

class EDDisplay : public EDHist
{
private:

    // Tree information 
    short m_HG[10*60], m_LG[10*60];

    int m_FERS = 4;
    int m_Anodes = 60;

    std::string m_mapDir = "/Users/jmcelwee/Documents/testbeam2023/tools/TestBeam23/Mapping/";
    std::string m_map = "Mapping_Right_8FERS.txt";

    std::map<std::vector<int>, std::vector<int>> m_anodeMap;
    std::map<std::vector<int>, std::vector<int>> m_coordMap;

    TH3D *EventDisplay = new TH3D();


public:
    // --- Constructors ---
    EDDisplay(const char *infile);
    EDDisplay(const char *infile, const char *intree);
    EDDisplay(const char *infile, int FERS, int anodes); 
    EDDisplay(const char *infile, const char *intree, int FERS, int anodes); 
    ~EDDisplay();

    // ---- Methods ----
    void SetBranches()         override;
    void FillHist(int inEvent) override;
    void FillHist2(int inEvent, int Phi[2], int Z[2]);
    void LoadMap();

    // ---- Access Functions ----
    int GetFERS() { return m_FERS; };
    int GetAnodes() { return m_Anodes; };

    TH3D *GetEventDisplay() { return EventDisplay; };
};



#endif // Header Guard