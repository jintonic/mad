#include "TlDopedCsI.h"
using namespace MAD;

#include <TCanvas.h>
#include <TGraphErrors.h>

int main()
{
   TlDopedCsI *crystal = new TlDopedCsI;
   crystal->Print();

   TCanvas *can = new TCanvas;
   can->SetRightMargin(0.01);
   can->SetLeftMargin(0.11);
   can->Print("TlDopedCsI.pdf[");

   crystal->QFvsEnr()->Draw("ap");
   can->Print("TlDopedCsI.pdf");

   can->Print("TlDopedCsI.pdf]");
}
