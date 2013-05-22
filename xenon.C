#include "NaturalXe.h"
#include "LiquidXenon.h"
using namespace MAD;

using namespace UNIC;

#include <TCanvas.h>

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

   natXe->FormFactor2(nuclearRecoilEnergy=50*keV)->Draw();
   can->Print("xenon.ps");

   natXe->CNNSdXSF2()->Draw("colz");
   can->Print("xenon.ps");

   natXe->CNNSdXSFEr(neutrinoEnergy=50*MeV)->Draw();
   can->Print("xenon.ps");

   natXe->CNNSdXSFEv(nuclearRecoilEnergy=1*keV)->Draw();
   can->Print("xenon.ps");

   LiquidXenon *LXe = new LiquidXenon; // material
   LXe->SetElement(natXe);
   LXe->Print();

   can->SetLogx();
   LXe->Leff()->Draw("al");
   can->Print("xenon.ps");

   can->Print("xenon.ps]");
}
