/* =========== EDPROCESSED =========== *
 * Author: J. McElwee                  *
 * Created: 19-08-2024                 *
 * Email: mcelwee@lp2ib.in2p3.fr       *
 *                                     *
 * Histogram filling for the raw.      * 
 * data output from the boards.        *
 *                                     *
 * =================================== */

#include "EDProcessed.hh"

//**********************************************************
//***** CONSTRUCTORS ***************************************

// - - - - - - - - - - - - - - - - - - - - 
EDProcessed::EDProcessed(const char *infile)
    : EDHitMap(infile)
{}
// - - - - - - - - - - - - - - - - - - - - 


// - - - - - - - - - - - - - - - - - - - - 
EDProcessed::EDProcessed(const char *infile, const char *intree)
    : EDHitMap(infile, intree)
{}
// - - - - - - - - - - - - - - - - - - - -


// - - - - - - - - - - - - - - - - - - - - 
EDProcessed::EDProcessed(const char *infile, int FERS) 
    : EDHitMap(infile)
{
    m_FERS = FERS;
}
// - - - - - - - - - - - - - - - - - - - - 


// - - - - - - - - - - - - - - - - - - - - 
EDProcessed::EDProcessed(const char *infile, const char *intree, int FERS) 
    : EDHitMap(infile, intree)
{
    m_FERS = FERS;
}
// - - - - - - - - - - - - - - - - - - - -  


// - - - - - - - - - - - - - - - - - - - - 
EDProcessed::~EDProcessed()
{}
// - - - - - - - - - - - - - - - - - - - - 

//**********************************************************



//**********************************************************
//***** ROOT STUFF *****************************************

// - - - - - - - - - - - - - - - - - - - - 
void EDProcessed::SetBranches()
{
    m_curTree->SetBranchAddress("fersLG",m_LG_proc); // Same as &fLG[0]                                     
    m_curTree->SetBranchAddress("fersHG",m_HG_proc);
}
// - - - - - - - - - - - - - - - - - - - - 

// - - - - - - - - - - - - - - - - - - - - 
void EDProcessed::FillHist(int evnt)
{

    // Default values for all of the events
    long int entryBounds[2] = {0,(long int)m_curTree->GetEntries()};
//    long int entryBounds[2] = {0,50000};

    std::cout << evnt << std::endl;

    if (evnt >= 0) 
    { 
        entryBounds[0] = evnt; 
        entryBounds[1] = evnt + 1;
    }

    int Z[2] = {0, 14};
    int Phi[2] = {-8, 17};
    TH3D *ED3D = new TH3D("Processed 3D",";Z;#phi;",
                          Z[1]-Z[0]+1, Z[0]-0.5, Z[1]+0.5,
                          Phi[1]-Phi[0]+1, Phi[0]-0.5, Phi[1]+0.5,
                          5, -0.5, 4.5);
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
        for (int board=0; board < 20; board++)   
            for (int anode=0; anode < 60; anode++)
                if (m_anodeMap.find(std::vector<int>{(int)board,anode}) != m_anodeMap.end())
                {
                    int channel = board*60 + anode;

                    int TVal = m_anodeMap[std::vector<int>{(int)board,anode}][0];
                    int PhiVal = m_anodeMap[std::vector<int>{(int)board,anode}][1];

                    int ZLayer = 0;
                    for (TH2D* histogram : hitmap) 
                    {
                        if (m_anodeMap[std::vector<int>{(int)board,anode}][2] == ZLayer)
                        {
                            if (m_HG_proc[channel] > 0 && m_LG_proc[channel] > 0)
                            {
                                if (TVal <= 1)
                                {
                                    histogram->Fill(PhiVal, TVal, m_HG_proc[channel]);
                                    FillArc(ArcMap.at(ZLayer),PhiVal, TVal, m_HG_proc[channel]);
                                    ED3D->Fill(ZLayer, PhiVal, TVal, m_HG_proc[channel]);
                                }
                                else
                                {
                                    histogram->Fill(PhiVal, TVal, m_LG_proc[channel]);
                                    FillArc(ArcMap.at(ZLayer),PhiVal, TVal, m_LG_proc[channel]);
                                    ED3D->Fill(ZLayer, PhiVal, TVal, m_LG_proc[channel]);
                                }
                            }
                        }
                        ZLayer++;
                    }

                }
    }


    m_HitMap = hitmap;
    m_ArcMap = ArcMap;
    ED3D->Copy(*m_EventDisplay);


}
// - - - - - - - - - - - - - - - - - - - - 

//**********************************************************