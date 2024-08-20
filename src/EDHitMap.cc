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
  //m_curTree->SetBranchAddress("boardID", &m_board);

    //  m_curTree->SetBranchAddress("lg",m_LG); // Same as &fLG[0]                                     
//  m_curTree->SetBranchAddress("hg",m_HG);

  m_curTree->SetBranchAddress("fersLG",m_LG_sort); // Same as &fLG[0]                                     
  m_curTree->SetBranchAddress("fersHG",m_HG_sort);
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
                if (m_maps.AnodeCoord.find(std::vector<int>{(int)board,anode}) != m_maps.AnodeCoord.end())
                {

                int TVal = m_maps.AnodeCoord[std::vector<int>{(int)board,anode}][0];
                int PhiVal = m_maps.AnodeCoord[std::vector<int>{(int)board,anode}][1];

                int ZLayer = 0;
                for (TH2D* histogram : hitmap) {
                    if (m_maps.AnodeCoord[std::vector<int>{(int)board,anode}][2] == ZLayer)
                    {
                        if (m_HG_sort[board][anode] > 0 && m_LG_sort[board][anode] > 0){
                        if (TVal <= 1){
                            histogram->Fill(PhiVal, TVal, m_HG_sort[board][anode]);
                            FillArc(ArcMap.at(ZLayer),PhiVal, TVal, m_HG_sort[board][anode]);
                        }
                        else{
                            histogram->Fill(PhiVal, TVal, m_LG_sort[board][anode]);
                            FillArc(ArcMap.at(ZLayer),PhiVal, TVal, m_LG_sort[board][anode]);
                        }
                        }
                        /*if (m_HG[anode] > 0 && m_LG[anode] > 0){
                        if (TVal <= 1){
                            histogram->Fill(PhiVal, TVal, m_HG[anode]);
                            FillArc(ArcMap.at(ZLayer),PhiVal, TVal, m_HG[anode]);
                        }
                        else{
                            histogram->Fill(PhiVal, TVal, m_LG[anode]);
                            FillArc(ArcMap.at(ZLayer),PhiVal, TVal, m_LG[anode]);
                        }
                        }*/
                    }
                    ZLayer++;
                }

                }
    }


    m_HitMap = hitmap;
    m_ArcMap = ArcMap;

}
// - - - - - - - - - - - - - - - - - - - - 



// - - - - - - - - - - - - - - - - - - - - 
TH2Poly* EDHitMap::CreateArcHist(std::string histName)
{
    // Create a TH2Poly histogram with a tighter range for zooming in
    TH2Poly *h2 = new TH2Poly(histName.c_str(), ";x [cm]; y [cm]", -50, 45, 80, 120);

    // Loop over the radial bins
    for (int i = 0; i < nBinsRadius; ++i) {
        // Determine the radius for this bin
        double rMin = radiusMin + i * (radiusMax - radiusMin) / nBinsRadius;
        double rMax = radiusMin + (i + 1) * (radiusMax - radiusMin) / nBinsRadius;

        // Loop over the angular bins
        for (int j = -8; j <= (nBinsAngle-8); ++j) {
            // Determine the angle for this bin (in radians), and rotate by pi/2 clockwise
            double angleMin = j * angleIncrement + 82*TMath::Pi()/180;
            double angleMax = (j + 1) * angleIncrement + 82*TMath::Pi()/180;

            // Create vectors to store the x and y coordinates of the vertices
            std::vector<double> x, y;

            // Add the inner arc (rMin) vertices
            for (int k = 0; k <= nSegments; ++k) {
                double angle = angleMin + k * (angleMax - angleMin) / nSegments;
                x.push_back(rMin * TMath::Cos(angle));
                y.push_back(rMin * TMath::Sin(angle));
            }

            // Add the outer arc (rMax) vertices (in reverse order)
            for (int k = nSegments; k >= 0; --k) {
                double angle = angleMin + k * (angleMax - angleMin) / nSegments;
                x.push_back(rMax * TMath::Cos(angle));
                y.push_back(rMax * TMath::Sin(angle));
            }

            // Add the arc segment as a polygon bin
            h2->AddBin(x.size(), x.data(), y.data());
        }
    }

    h2->GetZaxis()->SetRangeUser(0,800);
    return h2;


}
// - - - - - - - - - - - - - - - - - - - - 

// - - - - - - - - - - - - - - - - - - - - 
void EDHitMap::FillArc(TH2Poly* h2, double phiBin, double rBin, double weight) {

    // Calculate the radius (R) for the given rBin
    double rMin = radiusMin + rBin * (radiusMax - radiusMin) / nBinsRadius;
    double rMax = radiusMin + (rBin + 1) * (radiusMax - radiusMin) / nBinsRadius;
    double R = (rMin + rMax) / 2;  // Use the middle of the bin for R

    // Calculate the angle (phi) for the given phiBin and rotate by pi/2 clockwise
    double phiMin = phiBin * angleIncrement + 82*TMath::Pi()/180;
    double phiMax = (phiBin + 1) * angleIncrement + 82*TMath::Pi()/180;
    double phi = (phiMin + phiMax) / 2;  // Use the middle of the bin for phi

    // Convert polar coordinates (R, phi) to Cartesian coordinates (x, y)
    double x = R * TMath::Cos(phi);
    double y = R * TMath::Sin(phi);

    h2->Fill(x, y, weight);
}
// - - - - - - - - - - - - - - - - - - - - 

//**********************************************************

