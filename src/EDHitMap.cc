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

#include "EDHitMap.hh"

//**********************************************************
//***** CONSTRUCTORS ***************************************

// - - - - - - - - - - - - - - - - - - - - 
EDHitMap::EDHitMap(const char *infile)
    : EDHist(infile)
{}
// - - - - - - - - - - - - - - - - - - - - 


// - - - - - - - - - - - - - - - - - - - - 
EDHitMap::EDHitMap(const char *infile, const char *intree)
    : EDHist(infile, intree)
{}
// - - - - - - - - - - - - - - - - - - - -


// - - - - - - - - - - - - - - - - - - - - 
EDHitMap::EDHitMap(const char *infile, int FERS) 
    : EDHist(infile)
{
    m_FERS = FERS;
}
// - - - - - - - - - - - - - - - - - - - - 


// - - - - - - - - - - - - - - - - - - - - 
EDHitMap::EDHitMap(const char *infile, const char *intree, int FERS) 
    : EDHist(infile, intree)
{
    m_FERS = FERS;
}
// - - - - - - - - - - - - - - - - - - - -  


// - - - - - - - - - - - - - - - - - - - - 
EDHitMap::~EDHitMap()
{
    delete EventDisplay;
}
// - - - - - - - - - - - - - - - - - - - - 

//**********************************************************



//**********************************************************
//***** ARC FILLING ****************************************

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
    double x = -R * TMath::Cos(phi);
    double y = R * TMath::Sin(phi);

    h2->Fill(x, y, weight);
}
// - - - - - - - - - - - - - - - - - - - - 

//**********************************************************



//**********************************************************
//***** MAPPING INFO ***************************************

// - - - - - - - - - - - - - - - - - - - - 
void EDHitMap::LoadMap(std::string inMap, std::string mapDir, EMapYear year)
{
    switch (year)
    {
    case k2023:
        m_anodeMap = MappingAnodeCord( (mapDir + inMap) .c_str() );
        m_coordMap = MappingCordAnode( (mapDir + inMap) .c_str() );
        break;
    case k2024:
        // The inMap here are used for the Concentrator map 
        // and mapDir for the Janus
        m_maps = CreateMap(inMap.c_str(), mapDir.c_str());
        break;
    default:
        m_maps = CreateMap(inMap.c_str(), mapDir.c_str());
    }
}
// - - - - - - - - - - - - - - - - - - - - 

//**********************************************************

