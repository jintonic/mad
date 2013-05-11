#include "NaturalXe.h"
#include "LiquidXenon.h"

#include <TF2.h>
#include <TCanvas.h>

#include <iostream>
using namespace std;

int main()
{
   NaturalXe *natXe = new NaturalXe; // element
   LiquidXenon *LXe = new LiquidXenon; // material
   LXe->SetElement(natXe);

   natXe->Print();
   LXe->Print();

   TF2 *fxs = new TF2("fxs",natXe,&Element::CNNSdXSF,
         0,50/*keV*/,0,100/*MeV*/,0,"Element","CNNSdXSF");
   TF1 *fEr = new TF1("fEr",natXe,&NaturalXe::CNNSdXSEr,0,50/*keV*/,1);
   fEr->SetParameter(0,50/*MeV*/);
   TF1 *fEv = new TF1("fEv",natXe,&NaturalXe::CNNSdXSEv,0,100/*MeV*/,1);
   fEv->SetParameter(0,50/*keV*/);

   TCanvas *can = new TCanvas;
   can->Print("xenon.ps[");

   natXe->FormFactor2()->Draw();
   can->Print("xenon.ps");

   fxs->Draw("colz");
   can->Print("xenon.ps");

   fEr->Draw();
   can->Print("xenon.ps");

   fEv->Draw();
   can->Print("xenon.ps");

   can->SetLogx();
   LXe->Leff()->Draw("al");
   can->Print("xenon.ps");

   can->Print("xenon.ps]");
}
