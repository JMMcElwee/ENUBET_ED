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
    int Phi[2] = {-8, 17};
    int Z[2] = {0, 14};

    std::vector<THV> hist_hg(m_FERS, THV(m_Anodes,nullptr));
    std::vector<THV> hist_lg(m_FERS, THV(m_Anodes,nullptr));
    char histName[12];

    //std::vector<int> evnt_arr(m_curTree->GetEntries());
    //std::iota(evnt_arr.begin(),evnt_arr.end(), 1);

    // --- Set event array size ---
    int evnt_arr_size;
    if (evnt < 0) evnt_arr_size = m_curTree->GetEntries();
    else evnt_arr_size = 1;
    std::vector<int> evnt_arr(evnt_arr_size);

    if (evnt < 0) std::iota(evnt_arr.begin(),evnt_arr.end(), 1);
    else evnt_arr.at(0) = evnt;

    for (int FERS = 0; FERS < m_FERS; FERS++) // FERS  
        for (int anode = 0; anode < m_Anodes; anode++)
        { // Anode

            // --- Set histograms ---                                                                                   
            snprintf(histName,12,"b%i_a%i_hg",FERS,anode); // Avoid naming error
            hist_hg[FERS][anode] = new TH1D(histName,histName,100,0,8000);
            snprintf(histName,12,"b%i_a%i_lg",FERS,anode);
            hist_lg[FERS][anode] = new TH1D(histName,histName,100,0,8000);

            // --- Check channel exists --- 
            std::vector<int> channelVec = {FERS,anode};
            if (m_anodeMap.find(channelVec) != m_anodeMap.end())
                for (int i : evnt_arr)
                {
                    m_curTree->GetEntry(i);

                    int channel = FERS*m_Anodes + anode;
                    hist_hg[FERS][anode]->Fill(m_HG_proc[channel]);
                    hist_lg[FERS][anode]->Fill(m_LG_proc[channel]);
                } // Event 
        } // Anode


    std::string edName = "Run Number: " + std::to_string(18)
                     + " -- Event: " + std::to_string(evnt);
    TH3D *ED3D = new TH3D(edName.c_str(),edName.c_str(),
                          Z[1]-Z[0]+1, Z[0]-0.5, Z[1]+0.5,
                          Phi[1]-Phi[0]+1, Phi[0]-0.5, Phi[1]+0.5,
                          5, -0.5, 4.5);
//                          3, 11.5, 14.5,
//                          18, -0.5, 17.5,
//                          5, -0.5, 4.5);

    for (int r = 4; r >= 0; r--) // Currently fixed                                                                 
        for (int z = Z[0]; z <= Z[1]; z++) // Max z currently fixed                                        
            for (int phi = Phi[0]; phi <= Phi[1]; phi++)
                if (m_coordMap.find(std::vector<int>{r,phi,z}) != m_coordMap.end())
                {
                    // --- Grab the correct 1D histogram ---                                                              
                    std::vector<int> BAPos = m_coordMap[std::vector<int>{r,phi,z}];
                    //std::cout << BAPos[0] << " " << BAPos[1] << std::endl;                                        

                    if (m_FERS > BAPos[0])
                    {
                        //              std::cout << r << " " << z << " " << phi << std::endl;                              
                        TH1D *holdLG = (TH1D*) hist_lg[BAPos.at(0)][BAPos.at(1)];
                        double hist_max_LG = holdLG->GetXaxis()->GetBinCenter(holdLG->GetMaximumBin());
                        // This should always be over 200 for the later cut...                                              
                        //if (inputs->Event() < 0)
                        hist_max_LG = holdLG->Integral(holdLG->FindBin(200),holdLG->FindBin(7500));

                        TH1D *holdHG = (TH1D*) hist_hg[BAPos.at(0)][BAPos.at(1)];
                        double hist_max_HG = holdHG->GetXaxis()->GetBinCenter(holdHG->GetMaximumBin());
                        //if (inputs->Event() < 0)
                        hist_max_HG = holdHG->Integral(holdHG->FindBin(500),holdHG->FindBin(7500));


                        if (r <= 1 && hist_max_HG > 500) ED3D->Fill(z,phi,r,hist_max_HG);
                        else if (r > 1 && hist_max_LG > 200) ED3D->Fill(z,phi,r,hist_max_LG);
                        else ED3D->Fill(z,phi,r,0.1);
                    }
                    else ED3D->Fill(z,phi,r,0.1);
                    
                }

    gStyle->SetOptStat(0);

    // --- Change axis labels ---                                                                                   
    char const *range[5] = {"T_{0d}","T_{0u}","T_{1}","T_{2}","T_{3}"};
    ED3D->GetZaxis()->SetNdivisions(-5);
    for (int i=0;i<5;i++) ED3D->GetZaxis()->SetBinLabel(i+1,range[i]);
    ED3D->GetXaxis()->SetTitle("Z");
    ED3D->GetXaxis()->CenterTitle(true);
    ED3D->GetYaxis()->SetTitle("#phi");
    ED3D->GetYaxis()->CenterTitle(true);

    ED3D->Copy(*EventDisplay);

}
// - - - - - - - - - - - - - - - - - - - - 

//**********************************************************