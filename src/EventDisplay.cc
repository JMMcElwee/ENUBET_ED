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
  TGVerticalFrame *rightframe = new TGVerticalFrame(this, 600, 600, kLHintsExpandX | kLHintsExpandY);

  AddFrame(leftframe, new TGLayoutHints(kLHintsLeft | kFixedWidth ));
  AddFrame(rightframe,new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));


  // --- Run information button group ---- 
  TGVButtonGroup *fRunInfo = new TGVButtonGroup(leftframe, "Data Information");


  // Data Directory
  TGLabel *lDatDir = new TGLabel(fRunInfo, "Directory");
  fRunInfo->AddFrame(lDatDir, new TGLayoutHints(kLHintsLeft));

  fDatDir = new TGTextEntry(fRunInfo);
  fRunInfo->AddFrame(fDatDir, new TGLayoutHints(kLHintsCenterX | kLHintsExpandX));
  fDatDir->SetText("/Users/jmcelwee/Documents/testbeam2023/data/2023/");


  TGHorizontalFrame *fRunInfoFrame2 = new TGHorizontalFrame(fRunInfo, 20, 20, kLHintsCenterX | kLHintsBottom);
  fRunInfo->AddFrame(fRunInfoFrame2, new TGLayoutHints(kLHintsExpandX | kLHintsCenterX));

  // Run Prefix
  TGVerticalFrame *fPrefixFrame = new TGVerticalFrame(fRunInfoFrame2, 50, 30, kLHintsCenterX);
  fRunInfoFrame2->AddFrame(fPrefixFrame, new TGLayoutHints(kLHintsExpandX));

  TGLabel *lRunPre = new TGLabel(fPrefixFrame, "Prefix");
  fPrefixFrame->AddFrame(lRunPre, new TGLayoutHints(kLHintsLeft));

  fRunPre = new TGTextEntry(fPrefixFrame);
  fPrefixFrame->AddFrame(fRunPre, new TGLayoutHints(kLHintsExpandX | kLHintsLeft));
  fRunPre->SetText("run36");

  // Run Number 
  TGVerticalFrame *fRunNumFrame = new TGVerticalFrame(fRunInfoFrame2, 30, 30, kLHintsCenterX);
  fRunInfoFrame2->AddFrame(fRunNumFrame, new TGLayoutHints(kLHintsExpandX | kLHintsLeft));

  TGLabel *lNRun = new TGLabel(fRunNumFrame, "Number");
  fRunNumFrame->AddFrame(lNRun, new TGLayoutHints(kLHintsLeft));

  fNRun = new TGNumberEntry(fRunNumFrame);
  fRunNumFrame->AddFrame(fNRun, new TGLayoutHints(kLHintsExpandX | kLHintsLeft));
  fNRun->SetText("1684");

  // Event Number 
  TGVerticalFrame *fSufFrame = new TGVerticalFrame(fRunInfoFrame2, 30, 30, kLHintsCenterX | kLHintsBottom);
  fRunInfoFrame2->AddFrame(fSufFrame, new TGLayoutHints(kLHintsExpandX | kLHintsCenterX));

  TGLabel *lRunSuf = new TGLabel(fSufFrame, "Suffix");
  fSufFrame->AddFrame(lRunSuf, new TGLayoutHints(kLHintsLeft));

  fRunSuf = new TGTextEntry(fSufFrame);
  fSufFrame->AddFrame(fRunSuf, new TGLayoutHints(kLHintsExpandX | kLHintsLeft));
  fRunSuf->SetText("");

  // Select Data Type
  TGHorizontalFrame *gDataSelFrame = new TGHorizontalFrame(fRunInfo, 400, 30, kLHintsCenterX);
  fRunInfo->AddFrame(gDataSelFrame, new TGLayoutHints(kLHintsExpandX));

  TGVButtonGroup *gDataSel = new TGVButtonGroup(gDataSelFrame);
  gDataSelFrame->AddFrame(gDataSel, new TGLayoutHints(kLHintsExpandX));

  new TGRadioButton(gDataSel, "Processed", kProcessed);
  new TGRadioButton(gDataSel, "Raw", kRaw);
  new TGRadioButton(gDataSel, "Evt. Match", kEvtMatch);
  gDataSel->SetButton(kProcessed); 
  gDataSel->Connect("Pressed(Int_t)", "EventDisplay", this,
                       "SwapRawProcessed(Int_t)");


  // Event Number
  TGVerticalFrame *fEvtNumFrame = new TGVerticalFrame(gDataSelFrame, 30, 30, kLHintsCenterX);
  gDataSelFrame->AddFrame(fEvtNumFrame, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY));

  TGLabel *lNEvent = new TGLabel(fEvtNumFrame, "Event");
  fEvtNumFrame->AddFrame(lNEvent, new TGLayoutHints(kLHintsLeft));

  fNEvent = new TGNumberEntry(fEvtNumFrame);
  fEvtNumFrame->AddFrame(fNEvent, new TGLayoutHints(kLHintsExpandX | kLHintsRight));
  fNEvent->SetNumber(m_Evnt);
  //fNEvent->SetState(TGNumberEntry::kNESInteger);
  //fNEvent->Connect("ValueSet(Long_t)","EventDisplay", this, "DoDraw()");

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
  fPhi[0]->SetText("-8");
  fPhi[0]->SetLimits(TGNumberEntry::kNELLimitMinMax,-8,17);

  fPhi[1] = new TGNumberEntry(gPhi);
  gPhi->AddFrame(fPhi[1], new TGLayoutHints(kLHintsRight));
  fPhi[1]->SetText("17");
  fPhi[1]->SetLimits(TGNumberEntry::kNELLimitMinMax,-8,17);

  // Z
  TGHorizontalFrame *gZ = new TGHorizontalFrame(fPlotting, 150, 200, kLHintsExpandX);
  fPlotting->AddFrame(gZ, new TGLayoutHints(kLHintsCenterX | kLHintsExpandX));

  TGLabel *lZ = new TGLabel(gZ, "Z  ");
  gZ->AddFrame(lZ, new TGLayoutHints(kLHintsLeft | kLHintsCenterY));

  fZ[0] = new TGNumberEntry(gZ);
  gZ->AddFrame(fZ[0], new TGLayoutHints(kLHintsCenterX));
  fZ[0]->SetText("8");
  fZ[0]->SetLimits(TGNumberEntry::kNELLimitMinMax,0,14);

  fZ[1] = new TGNumberEntry(gZ);
  gZ->AddFrame(fZ[1], new TGLayoutHints(kLHintsRight));
  fZ[1]->SetText("14");
  fZ[1]->SetLimits(TGNumberEntry::kNELLimitMinMax,0,14);


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

  TGHorizontalFrame *fMapFrame2 = new TGHorizontalFrame(fMapGroup, 400, 50, kLHintsCenterX | kLHintsBottom);
  fMapGroup->AddFrame(fMapFrame2, new TGLayoutHints(kLHintsExpandX | kLHintsCenterX));

  // Map
  TGVerticalFrame *gMapName = new TGVerticalFrame(fMapFrame2, 400, 50, kLHintsLeft);
  fMapFrame2->AddFrame(gMapName, new TGLayoutHints(kLHintsExpandX));

  TGLabel *lMapName = new TGLabel(gMapName, "Name");
  gMapName->AddFrame(lMapName, new TGLayoutHints(kLHintsLeft));

  fMapName = new TGTextEntry(gMapName);
  gMapName->AddFrame(fMapName, new TGLayoutHints(kLHintsLeft | kLHintsExpandX));
  fMapName->SetText("Mapping_Left_9FERS.txt");


  // FERS Number
  TGVerticalFrame *gFERS = new TGVerticalFrame(fMapFrame2, 200, 50, kLHintsLeft);
  fMapFrame2->AddFrame(gFERS, new TGLayoutHints(kLHintsLeft));

  TGLabel *lFERS = new TGLabel(gFERS, "FERS");
  gFERS->AddFrame(lFERS, new TGLayoutHints(kLHintsLeft));

  fFERS = new TGNumberEntry(gFERS);
  gFERS->AddFrame(fFERS, new TGLayoutHints(kLHintsLeft | kLHintsExpandX));
  fFERS->SetText("9");

  // Anode Number 
  /*TGHorizontalFrame *gAnodes = new TGHorizontalFrame(fMapGroup, 300, 50, kLHintsCenterX | kLHintsBottom);
  fMapGroup->AddFrame(gAnodes, new TGLayoutHints(kLHintsExpandX | kLHintsCenterX));

  TGLabel *lAnodes = new TGLabel(gAnodes, "Anodes");
  gAnodes->AddFrame(lAnodes, new TGLayoutHints(kLHintsCenterY));

  fAnodes = new TGNumberEntry(gAnodes);
  gAnodes->AddFrame(fAnodes, new TGLayoutHints(kLHintsCenterY | kLHintsRight));
  fAnodes->SetText("60");*/

  fMapGroup->Show();
  leftframe->AddFrame(fMapGroup, new TGLayoutHints(kLHintsCenterX | kLHintsExpandX));
  // -------------------------------------



  // ---- Hit Map ------------------------
  TGVButtonGroup *fHitMapGroup = new TGVButtonGroup(leftframe, "Raw Hit Map");

  // Z Slice 
  TGLabel *lZSlice = new TGLabel(fHitMapGroup, "Z Slice");
  fHitMapGroup->AddFrame(lZSlice, new TGLayoutHints(kLHintsLeft | kLHintsCenterY));

  fZSlice = new TGNumberEntry(fHitMapGroup);
  fHitMapGroup->AddFrame(fZSlice, new TGLayoutHints(kLHintsCenterX));
  fZSlice->SetText("14");
  fZSlice->Connect("ValueSet(Long_t)","EventDisplay", this, "DoHitMap()");
  fZSlice->SetLimits(TGNumberEntry::kNELLimitMinMax,0,14);

  fHitMapGroup->Show();
  leftframe->AddFrame(fHitMapGroup, new TGLayoutHints(kLHintsCenterX | kLHintsExpandX));
  // -------------------------------------



  // ---- Buttons ------------------------

  // Draw buttons
  fDraw = new TGTextButton(leftframe,"&Draw");
  leftframe->AddFrame(fDraw, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY));
  fDraw->Connect("Clicked()","EventDisplay",this,"DoDraw()");
 
  // Exit button
  TGTextButton *exit = new TGTextButton(leftframe,"&Exit",
                                        "gApplication->Terminate(0)");
  leftframe->AddFrame(exit, new TGLayoutHints(kLHintsCenterX,3,3,3,3));

  // -------------------------------------



  // ---- Draw Canvas' -------------------

  // Create canvas widgets
  fEcanvas = new TRootEmbeddedCanvas("Ecanvas",rightframe,600,600);
  rightframe->AddFrame(fEcanvas, new TGLayoutHints(kLHintsExpandX|kLHintsExpandY,3,3,3,3));

  // Add frame for cherenkov and information 
  TGHorizontalFrame *cherInfoFrame = new TGHorizontalFrame(rightframe, 200, 600, kLHintsCenterX | kLHintsBottom);
  rightframe->AddFrame(cherInfoFrame, new TGLayoutHints(kLHintsRight | kLHintsExpandX));

  // Info Out Frame
  TGVerticalFrame *fInfoOutFrame = new TGVerticalFrame(cherInfoFrame, 200, 400, kLHintsCenterX);
  cherInfoFrame->AddFrame(fInfoOutFrame, new TGLayoutHints(kLHintsLeft | kLHintsExpandX));

  fStatus[0] = new TGStatusBar(fInfoOutFrame, 200, 400, kVerticalFrame | kLHintsCenterX);
  fInfoOutFrame->AddFrame(fStatus[0], new TGLayoutHints( kLHintsCenterX | kLHintsExpandX));
  fStatus[0]->Draw3DCorner(kFALSE);

  fStatus[1] = new TGStatusBar(fInfoOutFrame, 200, 400, kVerticalFrame | kLHintsCenterX);
  fStatus[1]->Draw3DCorner(kFALSE);
  int parts[] = {30,30,30};
  fStatus[1]->SetParts(parts, 3);
  fInfoOutFrame->AddFrame(fStatus[1], new TGLayoutHints( kLHintsCenterX | kLHintsExpandX));
 

  // Cherenkov Canvas 
  fCherCanvas = new TRootEmbeddedCanvas("CherCanvas",cherInfoFrame,200,200);
  cherInfoFrame->AddFrame(fCherCanvas, new TGLayoutHints(kLHintsBottom));

  // -------------------------------------



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



//**********************************************************
//***** SWAP DISPLAYS **************************************

// - - - - - - - - - - - - - - - - - - - - 
void EventDisplay::SwapRawProcessed(Int_t cSwitch)
{
  /* 
    Need to change the buttons and text in order to read in
    the values differently.
  */

  std::string DrawFunc, datDir, runPre, runSuf, runNum, mapDir, mapJanus;

  // Reconnect draw button 
  fDraw->Disconnect("Clicked()");  

  switch(cSwitch) 
  {

  // Raw data, no processing
  case kRaw:
    DrawFunc = "DoHitMap()";
    datDir = "/Users/jmcelwee/Documents/testbeam2023/data/2024/RAW/";
    runPre = "Run";
    runSuf = "_list";
    runNum = "32";
    mapDir = "/Users/jmcelwee/Documents/testbeam2023/tools/TestBeam24/Mapping/";
    mapJanus = "IC-Janus.txt";
    break;

  // Processed through data chain
  case kProcessed:
    DrawFunc = "DoDraw()";
    datDir = "/Users/jmcelwee/Documents/testbeam2023/data/2023/";
    runPre = "run36";
    runSuf = "";
    runNum = "1684";
    mapDir = "/Users/jmcelwee/Documents/testbeam2023/tools/TestBeam23/Mapping/";
    mapJanus = "Mapping_Left_9FERS.txt";
    break;

  // Event matched using Luca's code
  case kEvtMatch:
    DrawFunc = "DoHitMap()";
    datDir = "/Users/jmcelwee/Documents/testbeam2023/data/2024/RAW/";
    runPre = "Run";
    runSuf = "_sorted";
    runNum = "32";
    mapDir = "/Users/jmcelwee/Documents/testbeam2023/tools/TestBeam24/Mapping/";
    mapJanus = "IC-Janus.txt";
    break;

  // Default value is the processed
  default:
    DrawFunc = "DoDraw()";
    datDir = "/Users/jmcelwee/Documents/testbeam2023/data/2023/";
    runPre = "run36";
    runSuf = "";
    runNum = "1684";
    mapDir = "/Users/jmcelwee/Documents/testbeam2023/tools/TestBeam23/Mapping/";
    mapJanus = "Mapping_Left_9FERS.txt";
  }

  // Set values for output
  fDraw->Connect("Clicked()","EventDisplay",this,DrawFunc.c_str());
  fDatDir->SetText(datDir.c_str());
  fRunPre->SetText(runPre.c_str());
  fRunSuf->SetText(runSuf.c_str());
  fNRun->SetText(runNum.c_str());
  fMapDir->SetText(mapDir.c_str());
  fMapName->SetText(mapJanus.c_str());
}
// - - - - - - - - - - - - - - - - - - - - 

//**********************************************************



//**********************************************************
//***** DISPLAY DRAWING ************************************

// - - - - - - - - - - - - - - - - - - - - 
void EventDisplay::DoDraw() {

  gStyle->SetOptStat(0);

  // Cast GetText to string in order to add together
  iFile = (std::string)fDatDir->GetText() + (std::string)(fRunPre->GetText())
        + std::to_string(fNRun->GetIntNumber()) + ".root";
  fStatus[0]->SetText(iFile.c_str());


  // ---- Main Display Canvas ---- 

  fDisplay = std::make_shared<EDDisplay>(iFile.c_str(), "t",
                           (int)fFERS->GetIntNumber());
  fDisplay->SetBranches();
  fDisplay->LoadMap(fMapName->GetText(), fMapDir->GetText());

  int Phi_temp[2] = {(int) fPhi[0]->GetIntNumber(), (int)fPhi[1]->GetIntNumber()};
  int Z_temp[2] = {(int) fZ[0]->GetIntNumber(), (int)fZ[1]->GetIntNumber()};
  fDisplay->FillHist2((int)fNEvent->GetIntNumber(), Phi_temp, Z_temp);

  std::string evtOut = "Event " + std::to_string(fNEvent->GetIntNumber());
  fStatus[1]->SetText(evtOut.c_str(), 0);



  TCanvas *fCanvas = fEcanvas->GetCanvas();
  fCanvas->cd();
  gPad->SetPhi(-30);
  fDisplay->GetEventDisplay()->Draw("BOX2");
  fCanvas->Update();
  fDisplay->SetDrawn(true);

  // -----------------------------


  // ---- Cherenkov Canvas ----

  fCherenkov = std::make_shared<EDCherenkov>(iFile.c_str(), "t");
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
// - - - - - - - - - - - - - - - - - - - - 

//**********************************************************


//**********************************************************
//***** HITMAP *********************************************

// - - - - - - - - - - - - - - - - - - - - 
void EventDisplay::DoHitMap()
{
  // Remove stat box 
  gStyle->SetOptStat(0);

  // If the map is already drawn, don't redraw
  if (!bHitMapDrawn)
  {
    // Set new EDHitMap object
    std::string infile = (std::string)fDatDir->GetText() +
                         (std::string)fRunPre->GetText() +
                         std::to_string(fNRun->GetIntNumber()) +
                         ".root";
    fHitMap = std::make_shared<EDHitMap>(infile.c_str());
    fHitMap->SetBranches();

    // Load IC to Concentrator and IC to Janus maps
    fHitMap->LoadMap(( (std::string)fMapDir->GetText() + "IC-Concentrator.txt").c_str(),
                     ( (std::string)fMapDir->GetText() + (std::string)fMapName->GetText()).c_str());

    // Fill histograms for the certain event
    fHitMap->FillHist((int)fNEvent->GetIntNumber());

    // Check if built 
    bHitMapDrawn = true;
  }

  // Draw onto Canvas
  fEcanvas->GetCanvas()->cd();
  fHitMap->GetHitMap()[(int)fZSlice->GetIntNumber()]->Draw("COLZ");
  fEcanvas->GetCanvas()->Update();
}
// - - - - - - - - - - - - - - - - - - - - 


// - - - - - - - - - - - - - - - - - - - - 
void EventDisplay::ResetHitMap()
{
  bHitMapDrawn = false;
}
// - - - - - - - - - - - - - - - - - - - - 

//**********************************************************




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

}
