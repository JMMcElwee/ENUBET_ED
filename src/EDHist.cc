/* ============= EDHIST ============== *
 * Author: J. McElwee                  *
 * Created: 24-07-2024                 *
 * Email: mcelwee@lp2ib.in2p3.fr       *
 *                                     *
 * Control the plotting for the        *
 * histograms and controlling the ROOT *
 * file.                               *
 *                                     *
 * =================================== */

#include "EDHist.hh"


//**********************************************************
//***** CONSTRUCTORS ***************************************

// - - - - - - - - - - - - - - - - - - - - 
EDHist::EDHist(const char *infile)
    : m_curFile(infile, "READ")
{
    // Check if file exists
    if (m_curFile.IsZombie()) {
        std::cout << H_ERROR << "I can't open a file that doesn't exist. Exiting..."
        << std::endl;
        exit(0);
    }

    // Default value of the tree
    m_curFile.GetObject("t",m_curTree);
}
// - - - - - - - - - - - - - - - - - - - - 

// - - - - - - - - - - - - - - - - - - - - 
EDHist::EDHist(const char *infile, const char *intree) 
    : EDHist(infile)
{
    //m_intree = intree;    
    m_curFile.GetObject(intree,m_curTree);
}
// - - - - - - - - - - - - - - - - - - - - 

// - - - - - - - - - - - - - - - - - - - - 
EDHist::~EDHist()
{}
// - - - - - - - - - - - - - - - - - - - - 

//**********************************************************



//**********************************************************
//***** ACCESS FUNCTIONS ***********************************

// - - - - - - - - - - - - - - - - - - - - 
void EDHist::SetDrawn(bool bIsDrawn)
{
    m_IsDrawn = bIsDrawn;
}
// - - - - - - - - - - - - - - - - - - - - 

//**********************************************************
