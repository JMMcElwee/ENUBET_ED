/* ========== EVENT DISPLAY ========== *
 * Author: J. McElwee                  *
 * Created: 22-07-2024                 *
 * Email: mcelwee@lp2ib.in2p3.fr       *
 *                                     *
 * Class definition for the event      *
 * display class, controlling the      *
 * main frame for the GUI.             *
 *                                     *
 * =================================== */


#include "EventDisplay.hh"

//**********************************************************
//***** CONSTRUCTOR ****************************************

EventDisplay::EventDisplay(const TGWindow *p,UInt_t w,UInt_t h) 
  : TGMainFrame(p,w,h,kHorizontalFrame) {
 
  // Create a horizontal frame widget with buttons
  TGVerticalFrame *leftframe = new TGVerticalFrame(this, 400, 600, kLHintsLeft | kLHintsCenterY);
  TGVerticalFrame *rightframe = new TGVerticalFrame(this, 600, 600, kLHintsRight | kLHintsExpandX | kLHintsExpandY);

  AddFrame(leftframe, new TGLayoutHints(kLHintsLeft | kFixedWidth ));
  AddFrame(rightframe,new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));



  // --- Run information button group ---- 
  TGVButtonGroup *fRunInfo = new TGVButtonGroup(leftframe, "Run Information");

  // Data Directory
  TGLabel *lDatDir = new TGLabel(fRunInfo, "Directory");
  fRunInfo->AddFrame(lDatDir, new TGLayoutHints(kLHintsLeft));

  fDatDir = new TGTextEntry(fRunInfo);
  fRunInfo->AddFrame(fDatDir, new TGLayoutHints(kLHintsCenterX | kLHintsExpandX));
  fDatDir->SetText("/Users/jmcelwee/Documents/testbeam2023/data/");


  // Run Prefix
  TGHorizontalFrame *pHoriz = new TGHorizontalFrame(fRunInfo, 400, 50, kLHintsCenterX | kLHintsBottom);
  fRunInfo->AddFrame(pHoriz, new TGLayoutHints(kLHintsExpandX | kLHintsCenterX));

  TGLabel *lRunPre = new TGLabel(pHoriz, "Prefix        ");
  pHoriz->AddFrame(lRunPre, new TGLayoutHints(kLHintsCenterY));

  fRunPre = new TGTextEntry(pHoriz);
  pHoriz->AddFrame(fRunPre, new TGLayoutHints(kLHintsCenterY | kLHintsRight));
  fRunPre->SetText("run36");


  // Run Number 
  TGHorizontalFrame *rBottom = new TGHorizontalFrame(fRunInfo, 300, 50, kLHintsCenterX | kLHintsBottom);
  fRunInfo->AddFrame(rBottom, new TGLayoutHints(kLHintsExpandX | kLHintsCenterX));

  TGLabel *lNRun = new TGLabel(rBottom, "Number");
  rBottom->AddFrame(lNRun, new TGLayoutHints(kLHintsCenterY));

  fNRun = new TGNumberEntry(rBottom);
  rBottom->AddFrame(fNRun, new TGLayoutHints(kLHintsCenterY | kLHintsRight));
  fNRun->SetText("1684");


  // Event Number 
  TGHorizontalFrame *fEventGroup = new TGHorizontalFrame(fRunInfo, 300, 50, kLHintsCenterX | kLHintsBottom);
  fRunInfo->AddFrame(fEventGroup, new TGLayoutHints(kLHintsExpandX | kLHintsCenterX));

  TGLabel *lNEvent = new TGLabel(fEventGroup, "Event");
  fEventGroup->AddFrame(lNEvent, new TGLayoutHints(kLHintsCenterY));

  fNEvent = new TGNumberEntry(fEventGroup);
  fEventGroup->AddFrame(fNEvent, new TGLayoutHints(kLHintsCenterY | kLHintsRight));
  fNEvent->SetText("0");
  fNEvent->Connect("ValueSet(Long_t)","EventDisplay", this, "DoDraw()");

  fRunInfo->Show();
  leftframe->AddFrame(fRunInfo, new TGLayoutHints(kLHintsCenterX | kLHintsExpandX));
  // -------------------------------------



  // ---- Event Display Selection --------
  TGButtonGroup *fDimension = new TGButtonGroup(leftframe, "Dimension");

  new TGRadioButton(fDimension, "2D Phi-R", 1);
  new TGRadioButton(fDimension, "2D Phi-Z", 2);
  new TGRadioButton(fDimension, "2D Z-R", 3);
  new TGRadioButton(fDimension, "3D", 0);
  fDimension->SetButton(0); 
  fDimension->Connect("Pressed(Int_t)", "EventDisplay", this,
                       "Do2D(Int_t)");

  fDimension->Show();
  leftframe->AddFrame(fDimension, new TGLayoutHints(kLHintsCenterX | kLHintsExpandX));
  // -------------------------------------



  // ---- Cherenkov information ----------
  TGHButtonGroup *fCherGroup = new TGHButtonGroup(leftframe, "Cherenkov");

  TGVerticalFrame *fCherCutFrame = new TGVerticalFrame(fCherGroup, 150, 200, kLHintsExpandX | kLHintsExpandY);
  TGVButtonGroup *fCherSelFrame = new TGVButtonGroup(fCherGroup);
  fCherGroup->AddFrame(fCherCutFrame, new TGLayoutHints(kLHintsLeft | kLHintsExpandX));
  fCherGroup->AddFrame(fCherSelFrame, new TGLayoutHints(kLHintsLeft | kLHintsExpandX));

  // Show Cherenkov
  fCherShow = new TGCheckButton(fCherCutFrame, "Show cuts");
  fCherCutFrame->AddFrame(fCherShow, new TGLayoutHints(kLHintsLeft));
  // Check out this bottom line, interesting!
  //->Connect("Toggled(Bool_t)", "TGButton", fButton, "SetEnabled(Bool_t)");
  fCherShow->Connect("Toggled(Bool_t)", "EventDisplay", this, "ShowCherenkov(Bool_t)");

  // Cuts
  TGLabel *lCherCuts = new TGLabel(fCherCutFrame, "Cuts 1/2");
  fCherCutFrame->AddFrame(lCherCuts, new TGLayoutHints(kLHintsLeft));

  fCherCuts[0] = new TGNumberEntry(fCherCutFrame);
  fCherCutFrame->AddFrame(fCherCuts[0], new TGLayoutHints(kLHintsLeft));
  fCherCuts[0]->SetText("800");

  fCherCuts[1] = new TGNumberEntry(fCherCutFrame);
  fCherCutFrame->AddFrame(fCherCuts[1], new TGLayoutHints(kLHintsLeft));
  fCherCuts[1]->SetText("1400");

  // Select Cherenkov view 
  new TGRadioButton(fCherSelFrame, "PH1:PH2", 0);
  new TGRadioButton(fCherSelFrame, "PH1:T1", 1);
  new TGRadioButton(fCherSelFrame, "PH2:T2", 2);
  fCherSelFrame->SetButton(0); 
  fCherSelFrame->Connect("Pressed(Int_t)", "EventDisplay", this,
                         "SelectCherenkov(Int_t)");

  fCherGroup->Show();
  leftframe->AddFrame(fCherGroup, new TGLayoutHints(kLHintsCenterX | kLHintsExpandX));
  // -------------------------------------



  // ---- Plotting information -----------
  TGVButtonGroup *fPlotting = new TGVButtonGroup(leftframe, "Plotting");

  // Phi
  TGHorizontalFrame *gPhi = new TGHorizontalFrame(fPlotting, 150, 200, kLHintsExpandX);
  fPlotting->AddFrame(gPhi, new TGLayoutHints(kLHintsCenterX | kLHintsExpandX));

  TGLabel *lPhi = new TGLabel(gPhi, "Phi");
  gPhi->AddFrame(lPhi, new TGLayoutHints(kLHintsLeft | kLHintsCenterY));

  fPhi[0] = new TGNumberEntry(gPhi);
  gPhi->AddFrame(fPhi[0], new TGLayoutHints(kLHintsCenterX));
  fPhi[0]->SetText("0");

  fPhi[1] = new TGNumberEntry(gPhi);
  gPhi->AddFrame(fPhi[1], new TGLayoutHints(kLHintsRight));
  fPhi[1]->SetText("17");

  // Z
  TGHorizontalFrame *gZ = new TGHorizontalFrame(fPlotting, 150, 200, kLHintsExpandX);
  fPlotting->AddFrame(gZ, new TGLayoutHints(kLHintsCenterX | kLHintsExpandX));

  TGLabel *lZ = new TGLabel(gZ, "Z  ");
  gZ->AddFrame(lZ, new TGLayoutHints(kLHintsLeft | kLHintsCenterY));

  fZ[0] = new TGNumberEntry(gZ);
  gZ->AddFrame(fZ[0], new TGLayoutHints(kLHintsCenterX));
  fZ[0]->SetText("11");

  fZ[1] = new TGNumberEntry(gZ);
  gZ->AddFrame(fZ[1], new TGLayoutHints(kLHintsRight));
  fZ[1]->SetText("14");  


  fPlotting->Show();
  leftframe->AddFrame(fPlotting, new TGLayoutHints(kLHintsCenterX | kLHintsExpandX));
  // -------------------------------------



  // ---- Mapping information ------------
  TGVButtonGroup *fMapGroup = new TGVButtonGroup(leftframe, "Mapping");

  // Map directory
  TGLabel *lMapDir = new TGLabel(fMapGroup, "Directory");
  fMapGroup->AddFrame(lMapDir, new TGLayoutHints(kLHintsLeft));

  fMapDir = new TGTextEntry(fMapGroup);
  fMapGroup->AddFrame(fMapDir, new TGLayoutHints(kLHintsCenterX | kLHintsExpandX));
  fMapDir->SetText("/Users/jmcelwee/Documents/testbeam2023/tools/TestBeam23/Mapping/");


  // Map
  TGHorizontalFrame *gMapName = new TGHorizontalFrame(fMapGroup, 400, 50, kLHintsCenterX | kLHintsBottom);
  fMapGroup->AddFrame(gMapName, new TGLayoutHints(kLHintsExpandX | kLHintsCenterX));

  TGLabel *lMapName = new TGLabel(gMapName, "Name");
  gMapName->AddFrame(lMapName, new TGLayoutHints(kLHintsCenterY));

  fMapName = new TGTextEntry(gMapName);
  gMapName->AddFrame(fMapName, new TGLayoutHints(kLHintsCenterY | kLHintsRight));
  fMapName->SetText("Mapping2023_v2.txt");


  // Run Number 
  TGHorizontalFrame *gFERS = new TGHorizontalFrame(fMapGroup, 300, 50, kLHintsCenterX | kLHintsBottom);
  fMapGroup->AddFrame(gFERS, new TGLayoutHints(kLHintsExpandX | kLHintsCenterX));

  TGLabel *lFERS = new TGLabel(gFERS, "FERS");
  gFERS->AddFrame(lFERS, new TGLayoutHints(kLHintsCenterY));

  fFERS = new TGNumberEntry(gFERS);
  gFERS->AddFrame(fFERS, new TGLayoutHints(kLHintsCenterY | kLHintsRight));
  fFERS->SetText("8");

  // Run Number 
  TGHorizontalFrame *gAnodes = new TGHorizontalFrame(fMapGroup, 300, 50, kLHintsCenterX | kLHintsBottom);
  fMapGroup->AddFrame(gAnodes, new TGLayoutHints(kLHintsExpandX | kLHintsCenterX));

  TGLabel *lAnodes = new TGLabel(gAnodes, "Anodes");
  gAnodes->AddFrame(lAnodes, new TGLayoutHints(kLHintsCenterY));

  fAnodes = new TGNumberEntry(gAnodes);
  gAnodes->AddFrame(fAnodes, new TGLayoutHints(kLHintsCenterY | kLHintsRight));
  fAnodes->SetText("60");


  fMapGroup->Show();
  leftframe->AddFrame(fMapGroup, new TGLayoutHints(kLHintsCenterX | kLHintsExpandX));
  // -------------------------------------





  // Draw button
  TGTextButton *draw = new TGTextButton(leftframe,"&Draw");
  draw->Connect("Clicked()","EventDisplay",this,"DoDraw()");
  leftframe->AddFrame(draw, new TGLayoutHints(kLHintsCenterX,3,3,3,3));

 
  // Exit button
  TGTextButton *exit = new TGTextButton(leftframe,"&Exit",
                                        "gApplication->Terminate(0)");
  leftframe->AddFrame(exit, new TGLayoutHints(kLHintsCenterX,3,3,3,3));



  // Create canvas widgets
  fEcanvas = new TRootEmbeddedCanvas("Ecanvas",rightframe,600,600);
  rightframe->AddFrame(fEcanvas, new TGLayoutHints(kLHintsExpandX|kLHintsExpandY,3,3,3,3));


  // Cherenkov Canvas 
  fCherCanvas = new TRootEmbeddedCanvas("CherCanvas",leftframe,300,300);
  leftframe->AddFrame(fCherCanvas, new TGLayoutHints(kLHintsBottom | kLHintsRight));


  // Set a name to the main frame
  SetWindowName("ENUBET Event Display");

  // Map all subwindows of main frame
  MapSubwindows();

  // Initialize the layout algorithm
  //Resize(GetDefaultSize());
  Resize();

  // Map main frame
  MapWindow();

}

//**********************************************************





void EventDisplay::DoDraw() {

  // Cast GetText to string in order to add together
  iFile = (std::string)fDatDir->GetText() + (std::string)(fRunPre->GetText())
        + std::to_string(fNRun->GetIntNumber()) + ".root";
  std::cout << H_INFO << "The current file is: " << iFile << std::endl;
  gStyle->SetOptStat(0);

  // ---- Main Display Canvas ---- 

  fDisplay = new EDDisplay(iFile.c_str(), "t", 
                           (int)fFERS->GetIntNumber(), (int)fAnodes->GetIntNumber());
  fDisplay->SetBranches();
  fDisplay->LoadMap();

  int Phi_temp[2] = {(int) fPhi[0]->GetIntNumber(), (int)fPhi[1]->GetIntNumber()};
  int Z_temp[2] = {(int) fZ[0]->GetIntNumber(), (int)fZ[1]->GetIntNumber()};
  fDisplay->FillHist2((int)fNEvent->GetIntNumber(), Phi_temp, Z_temp);
  //fDisplay->FillHist((int)fNEvent->GetIntNumber());

  TCanvas *fCanvas = fEcanvas->GetCanvas();
  fCanvas->cd();
  gPad->SetPhi(-30);
  fDisplay->GetEventDisplay()->Draw("BOX2");
  fCanvas->Update();
  fDisplay->SetDrawn(true);

  // -----------------------------


  // ---- Cherenkov Canvas ----

  fCherenkov = new EDCherenkov(iFile.c_str(), "t");
  fCherenkov->SetBranches();
  fCherenkov->FillHist();

  fCherCanvas->GetCanvas()->cd();
  fCherCanvas->GetCanvas()->SetLogz(1);
  gPad->SetTopMargin(0.04);
  gPad->SetLeftMargin(0.12);

  fCherenkov->GetCherPH()->Draw("COLZ");
  fCherCanvas->GetCanvas()->Update();

  // --------------------------


}

void EventDisplay::Do2D(Int_t id) {

  fEcanvas->GetCanvas()->cd();

  if (fDisplay->IsDrawn()) 
  {
    if (id == 0) 
      fDisplay->GetEventDisplay()->Draw("BOX2");
    else if (id == 1)
      fDisplay->GetEventDisplay()->Project3D("zy")->Draw("COLZ");
    else if (id == 2)
      fDisplay->GetEventDisplay()->Project3D("xy")->Draw("COLZ");
    else if (id == 3)
      fDisplay->GetEventDisplay()->Project3D("zx")->Draw("COLZ");
  }

  fEcanvas->GetCanvas()->Update();

}

void EventDisplay::ShowCherenkov(Bool_t bShow)
{
  fCherCanvas->GetCanvas()->cd();

  if (bShow)
  {
    fCherLine[0] = new TLine(fCherCuts[0]->GetIntNumber(), 0, 
                             fCherCuts[0]->GetIntNumber(), 8000);
    fCherLine[0]->SetLineColor(kRed);
    fCherLine[0]->SetLineWidth(2);

    fCherLine[1] = new TLine(0,    fCherCuts[1]->GetIntNumber(), 
                             8000, fCherCuts[1]->GetIntNumber());
    fCherLine[1]->SetLineColor(kRed);
    fCherLine[1]->SetLineWidth(2);

    fCherLine[0]->Draw("SAME");
    fCherLine[1]->Draw("SAME");
  }
  else 
  {
    fCherCanvas->GetCanvas()->GetListOfPrimitives()->Remove(fCherLine[0]);
    fCherCanvas->GetCanvas()->GetListOfPrimitives()->Remove(fCherLine[1]);
    fCherCanvas->GetCanvas()->Modified();
  }

  fCherCanvas->GetCanvas()->Update();

}

void EventDisplay::SelectCherenkov(Int_t id)
{
  fCherCanvas->GetCanvas()->cd();

  if (id == 0)
    fCherenkov->GetCherPH()->Draw("COLZ");
  else if (id == 1)
    fCherenkov->GetCherPHT1()->Draw("COLZ");
  else if (id == 2)
    fCherenkov->GetCherPHT2()->Draw("COLZ");

  fCherCanvas->GetCanvas()->Update();
}


EventDisplay::~EventDisplay() {
  // Clean up used widgets: frames, buttons, layout hints
  //fMain->Cleanup();
  //delete fMain;
}
