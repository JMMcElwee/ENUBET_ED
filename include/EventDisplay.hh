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
#include "EDRaw.hh"
#include "EDEvtMatch.hh"
#include "EDProcessed.hh"
#include "EDCherenkov.hh"
#include "EDSim.hh"


class EventDisplay : public TGMainFrame {

public:

  // ----- Enumeration -----
  enum ECanvas 
  {
    kRaw = 0,
    kProcessed = 1,
    kEvtMatch = 2,
    kSimulation = 3
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
  void Set2D(Bool_t is2D);

  // ---- Hit Map ----
  void ResetHitMap();

  void ShowCherenkov(Bool_t bShow);
  void SelectCherenkov(Int_t id);

  // ---- Plotting ----
  void SetArc(bool isArc);


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

  // ----- Plotting -------------
 
  bool  bHMvs3D = false;
  TGNumberEntry *fPhi[2];
  TGNumberEntry *fZ[2]; 

  // Hit Map 
  TGVButtonGroup *f3DType;
  TGLabel *lZSlice;
  TGNumberEntry *fZSlice;
  TGVButtonGroup *fHitMapGroup;
  std::shared_ptr<EDHitMap> fHitMap{nullptr}; 
  ECanvas m_datatype = kProcessed;
  bool  bHitMapDrawn = false;

  TGCheckButton *fIsArc;
  bool bIsArc = false;

  bool bIs2D = false; 

  // ----------------------------


  // Mapping Info
  TGTextEntry   *fMapDir;
  TGTextEntry   *fMapName;
  TGNumberEntry *fFERS;
  TGNumberEntry *fAnodes;

  // Event display
  std::shared_ptr<EDHitMap> fDisplay;
  std::shared_ptr<EDCherenkov> fCherenkov;
  TGStatusBar *fStatus[2];



  // Cherenkov info
  TGNumberEntry *fCherCuts[2];
  TGCheckButton *fCherShow;
  TLine *fCherLine[2] = {nullptr};



  std::string iFile;



  ClassDef(EventDisplay,0)
};


#endif