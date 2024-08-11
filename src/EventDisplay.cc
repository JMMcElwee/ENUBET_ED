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
  TGHButtonGroup *fCherenkov = new TGHButtonGroup(leftframe, "Cherenkov");

  TGVerticalFrame *fCherCutFrame = new TGVerticalFrame(fCherenkov, 150, 200, kLHintsExpandX | kLHintsExpandY);
  TGVButtonGroup *fCherSelFrame = new TGVButtonGroup(fCherenkov);
  fCherenkov->AddFrame(fCherCutFrame, new TGLayoutHints(kLHintsLeft | kLHintsExpandX));
  fCherenkov->AddFrame(fCherSelFrame, new TGLayoutHints(kLHintsLeft | kLHintsExpandX));

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

  fCherenkov->Show();
  leftframe->AddFrame(fCherenkov, new TGLayoutHints(kLHintsCenterX | kLHintsExpandX));
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

void EventDisplay::DoDraw() {

  // Cast GetText to string in order to add together
  iFile = (std::string)fDatDir->GetText() + (std::string)(fRunPre->GetText())
        + std::to_string(fNRun->GetIntNumber()) + ".root";
  std::cout << H_INFO << "The current file is: " << iFile << std::endl;


  EDHist *temp = new EDHist(iFile.c_str(), "t", 8, 60);
  temp->SetBranches();
  temp->LoadMap();
  temp->FillHist();
  temp->FillCherenkov();

  TCanvas *fCanvas = fEcanvas->GetCanvas();
  fCanvas->cd();
  gPad->SetPhi(-30);
  temp->GetED()->Draw("BOX2");
  fCanvas->Update();
  fIsDrawn = true;
  temp->GetED()->Copy(*fHist3D);


  fCherCanvas->GetCanvas()->cd();
  fCherCanvas->GetCanvas()->SetLogz(1);
  gPad->SetTopMargin(0.04);
  gPad->SetLeftMargin(0.12);
  temp->GetCher("PHPH")->Draw("COLZ");
//  temp->GetCher("PHPH")->Copy(fCherHist[0]);
//  temp->GetCher("PHT1")->Copy(*fCherHist[1]);
//  temp->GetCher("PHT2")->Copy(*fCherHist[2]);

  gStyle->SetOptStat(0);
  //gStyle->SetPalette(kLake);
  fCherCanvas->GetCanvas()->Update();

}

void EventDisplay::Do2D(Int_t id) {

  fEcanvas->GetCanvas()->cd();

  if (fIsDrawn) 
  {
    if (id == 0) 
      fHist3D->Draw("BOX2");
    else if (id == 1)
      fHist3D->Project3D("zy")->Draw("COLZ");
    else if (id == 2)
      fHist3D->Project3D("xy")->Draw("COLZ");
    else if (id == 3)
      fHist3D->Project3D("zx")->Draw("COLZ");
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
    fCherHist[0]->Draw("COLZ");
  else if (id == 1)
    fCherHist[1]->Draw("COLZ");
  else if (id == 2)
    fCherHist[2]->Draw("COLZ");

  fCherCanvas->GetCanvas()->Update();
}


EventDisplay::~EventDisplay() {
  // Clean up used widgets: frames, buttons, layout hints
  //fMain->Cleanup();
  //delete fMain;
}
