#include "NaturalXe.h"
#include "LiquidXenon.h"
using namespace MAD;

#include "UNIC/Units.h"
using namespace UNIC;

#include <TF2.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TGraphErrors.h>

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

   LXe->EnrPE(14.7*PE/keV)->Draw("al");
   can->Print("xenon.ps");

   can->SetLogx();
   LXe->Leff()->Draw("al");
   can->Print("xenon.ps");

   can->Print("xenon.ps]");

   can->Clear();
   can->SetLogx(0);

   TF1 *f1fm = (TF1*) natXe->FF2()->Clone();
   natXe->SetS(0.5*fermi);
   TF1 *f5fm = (TF1*) natXe->FF2()->Clone();

   f1fm->SetLineColor(kGray);
   f1fm->SetLineWidth(2);
   f5fm->SetLineColor(kRed);
   f5fm->SetLineWidth(1);
   f5fm->SetLineStyle(kDashed);

   f1fm->Draw();
   f5fm->Draw("same");

   TLegend *leg = new TLegend(0.4,0.65,0.8,0.88);
   leg->SetFillColor(0);
   leg->SetBorderSize(0);
   leg->SetHeader("nuclear skin thickness:");
   leg->AddEntry(f1fm,"1 fm","l");
   leg->AddEntry(f5fm,"0.5 fm","l");
   leg->Draw();

   can->Print("f2.eps");
}
