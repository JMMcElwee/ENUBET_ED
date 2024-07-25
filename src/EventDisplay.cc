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
  TGVerticalFrame *leftframe = new TGVerticalFrame(this,100,500,kLHintsLeft|kLHintsCenterY);
  TGVerticalFrame *rightframe = new TGVerticalFrame(this,500,500,kLHintsRight | kLHintsExpandX | kLHintsExpandY);

  AddFrame(leftframe, new TGLayoutHints(kLHintsLeft | kFixedWidth ));
  AddFrame(rightframe,new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));


  TGTextButton *draw = new TGTextButton(leftframe,"&Draw");
  draw->Connect("Clicked()","EventDisplay",this,"DoDraw()");
  leftframe->AddFrame(draw, new TGLayoutHints(kLHintsCenterX,3,3,3,3));

 

  TGTextButton *exit = new TGTextButton(leftframe,"&Exit",
                                        "gApplication->Terminate(0)");
  leftframe->AddFrame(exit, new TGLayoutHints(kLHintsCenterX,3,3,3,3));

  // Create canvas widgets
  fEcanvas = new TRootEmbeddedCanvas("Ecanvas",rightframe,500,500);
  rightframe->AddFrame(fEcanvas, new TGLayoutHints(kLHintsExpandX|kLHintsExpandY,3,3,3,3));



  // Set a name to the main frame
  SetWindowName("ENUBET Event Display");

  // Map all subwindows of main frame
  MapSubwindows();

  // Initialize the layout algorithm
  Resize(GetDefaultSize());

  // Map main frame
  MapWindow();
}

void EventDisplay::DoDraw() {
  // Draws function graphics in randomly chosen interval
  TF1 *f1 = new TF1("f1","sin(x)/x",0,gRandom->Rndm()*10);
  f1->SetLineWidth(3);
  f1->Draw();
  TCanvas *fCanvas = fEcanvas->GetCanvas();
  fCanvas->cd();
  fCanvas->Update();
}

void EventDisplay::DoWrite() {
  std::cout << "something as a quick test" << std::endl;
}

EventDisplay::~EventDisplay() {
  // Clean up used widgets: frames, buttons, layout hints
  //fMain->Cleanup();
  //delete fMain;
}
