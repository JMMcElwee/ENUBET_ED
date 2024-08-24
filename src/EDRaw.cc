/* ============== EDRAW ============== *
 * Author: J. McElwee                  *
 * Created: 19-08-2024                 *
 * Email: mcelwee@lp2ib.in2p3.fr       *
 *                                     *
 * Histogram filling for the raw data  * 
 * output from the boards.             *
 *                                     *
 * =================================== */

#include "EDRaw.hh"

//**********************************************************
//***** CONSTRUCTORS ***************************************

// - - - - - - - - - - - - - - - - - - - - 
EDRaw::EDRaw(const char *infile)
    : EDHitMap(infile)
{}
// - - - - - - - - - - - - - - - - - - - - 


// - - - - - - - - - - - - - - - - - - - - 
EDRaw::EDRaw(const char *infile, const char *intree)
    : EDHitMap(infile, intree)
{}
// - - - - - - - - - - - - - - - - - - - -


// - - - - - - - - - - - - - - - - - - - - 
EDRaw::EDRaw(const char *infile, int FERS) 
    : EDHitMap(infile)
{
    m_FERS = FERS;
}
// - - - - - - - - - - - - - - - - - - - - 


// - - - - - - - - - - - - - - - - - - - - 
EDRaw::EDRaw(const char *infile, const char *intree, int FERS) 
    : EDHitMap(infile, intree)
{
    m_FERS = FERS;
}
// - - - - - - - - - - - - - - - - - - - -  


// - - - - - - - - - - - - - - - - - - - - 
EDRaw::~EDRaw()
{}
// - - - - - - - - - - - - - - - - - - - - 

//**********************************************************



//**********************************************************
//***** ROOT STUFF *****************************************

// - - - - - - - - - - - - - - - - - - - - 
void EDRaw::SetBranches()
{
    m_curTree->SetBranchAddress("boardID", &m_board);

    m_curTree->SetBranchAddress("lg",m_LG_raw); // Same as &fLG[0]                                     
    m_curTree->SetBranchAddress("hg",m_HG_raw);
}
// - - - - - - - - - - - - - - - - - - - - 

// - - - - - - - - - - - - - - - - - - - - 
void EDRaw::FillHist(int evnt)
{
    // Default values for all of the events
    //long int entryBounds[2] = {0,(long int)m_curTree->GetEntries()};
    long int entryBounds[2] = {0,50000};

    if (evnt >= 0) 
    { 
        entryBounds[0] = evnt; 
        entryBounds[1] = evnt + 1;
    }

    std::vector<TH2D*> hitmap;
    std::vector<TH2Poly*> ArcMap;
    char const *range[5] = {"T_{0d}","T_{0u}","T_{1}","T_{2}","T_{3}"};
    for (int z = 0; z < 15; z++)
    {
        std::string HistName = "Hit Map " + std::to_string(z);
        hitmap.push_back(new TH2D(HistName.c_str(),";#phi;",26, -8.5, 17.5,5, -0.5, 4.5));

        //hitmap.at(z)->GetZaxis()->SetRangeUser(0,8192);
        hitmap.at(z)->GetYaxis()->SetNdivisions(-5);
        for (int i=0;i<5;i++) hitmap.at(z)->GetYaxis()->SetBinLabel(i+1,range[i]);

        ArcMap.push_back(CreateArcHist((HistName+" Arc").c_str()));
    }


    for (int entry = entryBounds[0]; entry < entryBounds[1]; entry++)
    {
        // Load event                                                                                   
        m_curTree->GetEntry(entry);

        if (entry % 10000 == 0) std::cout << entry << "/" 
                                << entryBounds[1] << " events." << std::endl; 

        // Loop over all anodes in list 
        for (int anode=0; anode < 60; anode++)
            if (m_maps.AnodeCoord.find(std::vector<int>{(int)m_board,anode}) != m_maps.AnodeCoord.end())
            {

            int TVal = m_maps.AnodeCoord[std::vector<int>{(int)m_board,anode}][0];
            int PhiVal = m_maps.AnodeCoord[std::vector<int>{(int)m_board,anode}][1];

            int ZLayer = 0;
            for (TH2D* histogram : hitmap) {
                if (m_maps.AnodeCoord[std::vector<int>{(int)m_board,anode}][2] == ZLayer)
                {
                    if (m_HG_raw[anode] > 0 && m_LG_raw[anode] > 0){
                        if (TVal <= 1){
                            histogram->Fill(PhiVal, TVal, m_HG_raw[anode]);
                            FillArc(ArcMap.at(ZLayer),PhiVal, TVal, m_HG_raw[anode]);
                        }
                        else
                        {
                            histogram->Fill(PhiVal, TVal, m_LG_raw[anode]);
                            FillArc(ArcMap.at(ZLayer),PhiVal, TVal, m_LG_raw[anode]);
                        }
                    }
                }
                ZLayer++;
            }

            }
    }

    m_HitMap = hitmap;
    m_ArcMap = ArcMap;

}
// - - - - - - - - - - - - - - - - - - - - 

//**********************************************************


