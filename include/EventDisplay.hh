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

// Regular ROOT information
#include <TCanvas.h>
#include <TF1.h>
#include <TH3D.h>

// GUI Specific
#include <TGClient.h>
#include <TRandom.h>

#include <TGFrame.h>
#include <TGLabel.h>
#include <TGButtonGroup.h>
#include <TGButton.h>
#include <TRootEmbeddedCanvas.h>

#include <TGButton.h>
#include <TGNumberEntry.h>


#include "EDHist.hh"


class EventDisplay : public TGMainFrame {

  private:

  // Canvas to print plots on
  TRootEmbeddedCanvas *fEcanvas;
  TRootEmbeddedCanvas *fCherCanvas;

  TGTextEntry   *fDatDir;
  TGTextEntry   *fRunPre;
  TGNumberEntry *fNRun;

  bool fIsDrawn = false;
  TH3D *fHist3D = new TH3D();

  std::string iFile;
  std::string iPrefix = "run36";


public:

  // Class Definitions
  EventDisplay(const TGWindow *p,UInt_t w,UInt_t h);
  virtual ~EventDisplay();

  // Methods 
  void DoDraw();
  void DoWrite();
  void Do2D(Int_t id);



  ClassDef(EventDisplay,0)
};


#endif