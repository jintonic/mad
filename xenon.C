#include "NaturalXe.h"
#include "LiquidXenon.h"
using namespace MAD;

#include <TF2.h>
#include <TCanvas.h>
#include <TGraphErrors.h>

#include <iostream>
using namespace std;

int main()
{
   NaturalXe *natXe = new NaturalXe; // element
   LiquidXenon *LXe = new LiquidXenon; // material
   LXe->AddElement(natXe,1);
   LXe->Print();

   TCanvas *can = new TCanvas;
   can->SetRightMargin(0.15);
   can->Print("xenon.ps[");

   natXe->FF2()->Draw();
   can->Print("xenon.ps");

   natXe->FCNNSdXS2D()->Draw("colz");
   can->Print("xenon.ps");

   natXe->FCNNSdXSEr()->Draw();
   can->Print("xenon.ps");

   natXe->FCNNSdXSEv()->Draw();
   can->Print("xenon.ps");

   can->SetLogx();
   LXe->Leff()->Draw("al");
   can->Print("xenon.ps");

   can->Print("xenon.ps]");
}
