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

// Regular ROOT information
#include <TCanvas.h>
#include <TF1.h>

// GUI Specific
#include <TGClient.h>
#include <TRandom.h>
#include <TGButton.h>
#include <TGFrame.h>
#include <TRootEmbeddedCanvas.h>


class EventDisplay : public TGMainFrame {

  private:

  // Canvas to print plots on
  TRootEmbeddedCanvas *fEcanvas;

public:

  // Class Definitions
  EventDisplay(const TGWindow *p,UInt_t w,UInt_t h);
  virtual ~EventDisplay();

  // Methods 
  void DoDraw();
  void DoWrite();


  ClassDef(EventDisplay,0)
};


#endif