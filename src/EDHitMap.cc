/* ============= HITMAP ============== *
 * Author: J. McElwee                  *
 * Created: 17-08-2024                 *
 * Email: mcelwee@lp2ib.in2p3.fr       *
 *                                     *
 * Hitmap of the raw data to check if  *
 * for the position of the beamspot.   *
 *                                     *
 * =================================== */

#include "EDHitMap.hh"

//**********************************************************
//***** CONSTRUCTORS ***************************************

// - - - - - - - - - - - - - - - - - - - - 
EDHitMap::EDHitMap()
{}
// - - - - - - - - - - - - - - - - - - - - 

// - - - - - - - - - - - - - - - - - - - - 
EDHitMap::EDHitMap(const char *infile)
    : m_curFile(infile, "READ")
{
    // Check if file exists
    if (m_curFile.IsZombie()) {
        std::cout << H_ERROR << "I can't open a file that doesn't exist. Exiting..."
        << std::endl;
        exit(0);
    }

    // Default value of the tree
    m_curFile.GetObject("t", m_curTree);
}
// - - - - - - - - - - - - - - - - - - - - 


// - - - - - - - - - - - - - - - - - - - - 
EDHitMap::EDHitMap(const char *infile, const char *intree)
    : EDHitMap(infile)
{  
    m_curFile.GetObject(intree,m_curTree);
}
// - - - - - - - - - - - - - - - - - - - -


// - - - - - - - - - - - - - - - - - - - - 
EDHitMap::~EDHitMap()
{}
// - - - - - - - - - - - - - - - - - - - - 

//**********************************************************



//**********************************************************
//***** ROOT STUFF *****************************************

// - - - - - - - - - - - - - - - - - - - - 
void EDHitMap::SetBranches()
{
  m_curTree->SetBranchAddress("boardID", &m_board);

  //m_curTree->SetBranchAddress("fersLG",m_LG_sort); // Same as &fLG[0]                                     
  //m_curTree->SetBranchAddress("fersHG",m_HG_sort);

  m_curTree->SetBranchAddress("lg",m_LG); // Same as &fLG[0]                                     
  m_curTree->SetBranchAddress("hg",m_HG);
}
// - - - - - - - - - - - - - - - - - - - - 


// - - - - - - - - - - - - - - - - - - - - 
void EDHitMap::LoadMap(std::string ICCon, std::string ICJanus)
{
    m_maps = CreateMap(ICCon.c_str(), ICJanus.c_str());
}
// - - - - - - - - - - - - - - - - - - - - 


// - - - - - - - - - - - - - - - - - - - - 
void EDHitMap::FillHist(int evnt)
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
    char const *range[5] = {"T_{0d}","T_{0u}","T_{1}","T_{2}","T_{3}"};
    for (int z = 0; z < 15; z++)
    {
        std::string HistName = "Hit Map " + std::to_string(z);
        hitmap.push_back(new TH2D(HistName.c_str(),";#phi;",26, -8.5, 17.5,5, -0.5, 4.5));

        //hitmap.at(z)->GetZaxis()->SetRangeUser(0,8192);
        hitmap.at(z)->GetYaxis()->SetNdivisions(-5);
        for (int i=0;i<5;i++) hitmap.at(z)->GetYaxis()->SetBinLabel(i+1,range[i]);
    }


    for (int entry = entryBounds[0]; entry < entryBounds[1]; entry++)
    {
        // Load event                                                                                   
        m_curTree->GetEntry(entry);

        if (entry % 10000 == 0) std::cout << entry << "/" 
                                << entryBounds[1] << " events." << std::endl; 

        // Loop over all anodes in list
//        for (int board=0; board < 20; board++)   
            for (int anode=0; anode < 60; anode++)
                if (m_maps.AnodeCoord.find(std::vector<int>{(int)m_board,anode}) != m_maps.AnodeCoord.end())
                {

                int TVal = m_maps.AnodeCoord[std::vector<int>{(int)m_board,anode}][0];
                int PhiVal = m_maps.AnodeCoord[std::vector<int>{(int)m_board,anode}][1];

                int ZLayer = 0;
                for (TH2D* histogram : hitmap) {
                    if (m_maps.AnodeCoord[std::vector<int>{(int)m_board,anode}][2] == ZLayer)
                    {
                    /*    if (m_HG_sort[board][anode] > 0 && m_LG_sort[board][anode] > 0){
                        if (TVal <= 1)
                            histogram->Fill(PhiVal, TVal, m_HG_sort[board][anode]);
                        else
                            histogram->Fill(PhiVal, TVal, m_LG_sort[board][anode]);
                        }*/
                        if (m_HG[anode] > 0 && m_LG[anode] > 0){
                        if (TVal <= 1)
                            histogram->Fill(PhiVal, TVal, m_HG[anode]);
                        else
                            histogram->Fill(PhiVal, TVal, m_LG[anode]);
                        }
                    }
                    ZLayer++;
                }

                //std::cout << "Soemthing else here" << std::endl;
                }
    }


    m_HitMap = hitmap;

}
// - - - - - - - - - - - - - - - - - - - - 



// - - - - - - - - - - - - - - - - - - - - 
//void EDHitMap::ArcHist()
//{

//}
// - - - - - - - - - - - - - - - - - - - - 

//**********************************************************

