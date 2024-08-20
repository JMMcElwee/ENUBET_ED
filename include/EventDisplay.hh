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

#ifndef EVENTDISPLAY_HH
#define EVENTDISPLAY_HH

#include <string>
#include <memory>

// Regular ROOT information
#include <TCanvas.h>
#include <TF1.h>
#include <TH3D.h>
#include <TLine.h>

// GUI Specific
#include <TGClient.h>
#include <TRandom.h>

#include <TGFrame.h>
#include <TGLabel.h>
#include <TGButtonGroup.h>
#include <TRootEmbeddedCanvas.h>

#include <TGStatusBar.h>

#include <TGButton.h>
#include <TGNumberEntry.h>


#include "EDHist.hh"
#include "EDHitMap.hh"
#include "EDDisplay.hh"
#include "EDCherenkov.hh"


class EventDisplay : public TGMainFrame {

  private:

  // Canvas to print plots on
  TRootEmbeddedCanvas *fEcanvas;
  TRootEmbeddedCanvas *fCherCanvas;

  // ----- File information -----

  // Buttons 
  TGTextButton *fDraw;

  // Text Entry
  TGTextEntry   *fDatDir;
  TGTextEntry   *fRunPre;
  TGTextEntry   *fRunSuf;
  TGNumberEntry *fNRun;
  TGNumberEntry *fNEvent;
  int m_Evnt = 0;

  // ----------------------------

  // Mapping Info
  TGTextEntry   *fMapDir;
  TGTextEntry   *fMapName;
  TGNumberEntry *fFERS;
  TGNumberEntry *fAnodes;

  // Event display
  std::shared_ptr<EDDisplay>   fDisplay;
  std::shared_ptr<EDCherenkov> fCherenkov;
  TGStatusBar *fStatus[2];

  // ----- Plotting -------------

  TGNumberEntry *fPhi[2];
  TGNumberEntry *fZ[2]; 

  TGCheckButton *fIsArc;
  bool bIsArc = false;

  // ----------------------------

  // Cherenkov info
  TGNumberEntry *fCherCuts[2];
  TGCheckButton *fCherShow;
  TLine *fCherLine[2] = {nullptr};

  // Hit Map 
  TGNumberEntry *fZSlice;
  std::shared_ptr<EDHitMap> fHitMap{nullptr}; 
  bool          bHitMapDrawn = false;



  std::string iFile;


public:

  // ----- Enumeration -----
  enum ECanvas 
  {
    kRaw = 0,
    kProcessed = 1,
    kEvtMatch = 2
  };


  // ----- Definitions -----
  EventDisplay(const TGWindow *p,UInt_t w,UInt_t h);
  virtual ~EventDisplay();

  // ----- Methods -----
  void DoDraw();
  void DoHitMap();
  void DoWrite();
  void DoArc();
  void Do2D(Int_t id);

  void SwapRawProcessed(Int_t cSwitch);

  // ---- Hit Map ----
  void ResetHitMap();

  void ShowCherenkov(Bool_t bShow);
  void SelectCherenkov(Int_t id);

  // ---- Plotting ----
  void SetArc(bool isArc);



  ClassDef(EventDisplay,0)
};


#endif