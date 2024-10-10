/* ============== EDSIM ============== *
 * Author: J. McElwee                  *
 * Created: 07-10-2024                 *
 * Email: mcelwee@lp2ib.in2p3.fr       *
 *                                     *
 * Histogram filling for the simu      * 
 * data output from the boards.        *
 *                                     *
 * =================================== */


#include "EDSim.hh"

//**********************************************************
//***** CONSTRUCTORS ***************************************

// - - - - - - - - - - - - - - - - - - - - 
EDSim::EDSim(const char *infile)
    : EDHitMap(infile)
{}
// - - - - - - - - - - - - - - - - - - - - 


// - - - - - - - - - - - - - - - - - - - - 
EDSim::EDSim(const char *infile, const char *intree)
    : EDHitMap(infile, intree)
{}
// - - - - - - - - - - - - - - - - - - - -


// - - - - - - - - - - - - - - - - - - - - 
EDSim::EDSim(const char *infile, int FERS) 
    : EDHitMap(infile)
{
    m_FERS = FERS;
}
// - - - - - - - - - - - - - - - - - - - - 


// - - - - - - - - - - - - - - - - - - - - 
EDSim::EDSim(const char *infile, const char *intree, int FERS) 
    : EDHitMap(infile, intree)
{
    m_FERS = FERS;
}
// - - - - - - - - - - - - - - - - - - - -  


// - - - - - - - - - - - - - - - - - - - - 
EDSim::~EDSim()
{}
// - - - - - - - - - - - - - - - - - - - - 

//**********************************************************



//**********************************************************
//***** ROOT STUFF *****************************************

// - - - - - - - - - - - - - - - - - - - - 
void EDSim::SetBranches()
{
    m_curTree->SetBranchAddress("caloR",   &m_r);
    m_curTree->SetBranchAddress("caloPhi", &m_phi);
    m_curTree->SetBranchAddress("caloZ",   &m_z);

    m_curTree->SetBranchAddress("t0Phi", &m_phit0);
    m_curTree->SetBranchAddress("t0Z",   &m_zt0);

    m_curTree->SetBranchAddress("ucmEDep", &m_EDep);
    m_curTree->SetBranchAddress("t0UpEDep", &m_EDepT0Up);
    m_curTree->SetBranchAddress("t0DwEDep", &m_EDepT0Dw);
}
// - - - - - - - - - - - - - - - - - - - - 

// - - - - - - - - - - - - - - - - - - - - 
void EDSim::FillHist(int evnt)
{

    long int entryBounds[2] = {0,(long int)m_curTree->GetEntries()};
    if (evnt >= 0) 
    { 
        entryBounds[0] = evnt; 
        entryBounds[1] = evnt + 1;
    }

    int Z[2] = {0, 14};
    int Phi[2] = {-8, 17};
    TH3D *ED3D = new TH3D("Simulation 3D",";Z;#phi;",
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
        m_curTree->GetEntry(entry);

        int ZLayer = 0;
        for (TH2D* histogram : hitmap)
        {
            // Calorimeter energy deposity
            for (int hit = 0; hit < m_EDep->size(); hit++)
            {
                if (m_z->at(hit) == ZLayer) {
                    histogram->Fill(m_phi->at(hit), m_r->at(hit)+2, m_EDep->at(hit));
                    FillArc(ArcMap.at(m_z->at(hit)), m_phi->at(hit), m_r->at(hit)+2, m_EDep->at(hit));
                    ED3D->Fill(m_z->at(hit),  m_phi->at(hit), m_r->at(hit)+2, m_EDep->at(hit));
                }
            }

            // T0 deposits
            for (int hit = 0; hit < m_EDepT0Up->size(); hit++)
            {
                if (m_zt0->at(hit) == ZLayer) {
                    histogram->Fill(m_phit0->at(hit), 0., m_EDepT0Dw->at(hit));
                    FillArc(ArcMap.at(m_zt0->at(hit)), m_phit0->at(hit), 0., m_EDepT0Dw->at(hit));
                    ED3D->Fill(m_zt0->at(hit),  m_phit0->at(hit), 0., m_EDepT0Dw->at(hit));

                    histogram->Fill(m_phit0->at(hit), 1., m_EDepT0Up->at(hit));
                    FillArc(ArcMap.at(m_zt0->at(hit)), m_phit0->at(hit), 1., m_EDepT0Up->at(hit));
                    ED3D->Fill(m_zt0->at(hit),  m_phit0->at(hit), 1., m_EDepT0Up->at(hit));
                }
            }

            ZLayer++;
        }
        
    }

    ED3D->GetZaxis()->SetNdivisions(-5);
    for (int i=0;i<5;i++) ED3D->GetZaxis()->SetBinLabel(i+1,range[i]);
 
    m_HitMap = hitmap;
    m_ArcMap = ArcMap;
    ED3D->Copy(*m_EventDisplay);

}
// - - - - - - - - - - - - - - - - - - - - 

//**********************************************************