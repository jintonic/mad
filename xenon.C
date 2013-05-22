#include "NaturalXe.h"
#include "LiquidXenon.h"
using namespace MAD;

using namespace UNIC;

#include <TCanvas.h>
#include <TGraphErrors.h>

#include <iostream>
using namespace std;

int main()
{
   TCanvas *can = new TCanvas;
   can->SetRightMargin(0.15);
   can->Print("xenon.ps[");

   NaturalXe *natXe = new NaturalXe; // element
   natXe->Print();

   Double_t neutrinoEnergy, nuclearRecoilEnergy;

   natXe->FF2(nuclearRecoilEnergy=50*keV)->Draw();
   can->Print("xenon.ps");

   natXe->FCNNSdXS2D()->Draw("colz");
   can->Print("xenon.ps");

   natXe->FCNNSdXSEr(neutrinoEnergy=50*MeV)->Draw();
   can->Print("xenon.ps");

   natXe->FCNNSdXSEv(nuclearRecoilEnergy=1*keV)->Draw();
   can->Print("xenon.ps");

   LiquidXenon *LXe = new LiquidXenon; // material
   LXe->AddElement(natXe,1);
   LXe->Print();

   can->SetLogx();
   LXe->Leff()->Draw("al");
   can->Print("xenon.ps");

   can->Print("xenon.ps]");
}
