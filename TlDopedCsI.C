#include <iostream>
using namespace std;
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
   double Enr=1; //keV
   cout<<"QF @ "<<Enr<<" keV: "<<crystal->QF(Enr)<<endl;
   can->Print("TlDopedCsI.pdf");

   can->Print("TlDopedCsI.pdf]");
}
