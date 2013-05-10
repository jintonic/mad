#include "Isotope.h"
#include "Element.h"
using namespace CLHEP;

#include <TF2.h>
#include <TCanvas.h>

#include <iostream>
using namespace std;

int main()
{
   // nuclear masses: 
   // http://hyperphysics.phy-astr.gsu.edu/hbase/pertab/xe.html
   // nuclear radius:
   // doi:10.1006/adnd.1995.1007
   const Int_t ni = 7;
   Int_t n[ni] = {128, 129, 130, 131, 132, 134, 136};
   Double_t m[ni] = {119.1147*GeV, 120.0474*GeV, 120.0777*GeV, 121.9107*GeV,
      122.8413*GeV, 124.7055*GeV, 126.5702*GeV}; 
   Double_t r[ni] = {4.776*fermi, 4.776*fermi, 4.783*fermi, 4.781*fermi,
      4.787*fermi, 4.792*fermi, 4.799*fermi};
   Double_t abundance[ni] = {0.0191, 0.264, 0.041, 0.212, 0.269, 0.104, 0.089};
   Isotope *xe[ni];
   TF1 *f2[ni];
   Double_t nuclearSkinThickness = 1*fermi;

   Element *xenon = new Element(ni);
   for (Int_t i=0; i<ni; i++) {
      xe[i] = new Isotope(54,n[i]);
      xe[i]->SetM(m[i]);
      xe[i]->SetR(r[i]);

      xenon->AddIsotope(xe[i],abundance[i]);

      f2[i] = new TF1(Form("f2_%d",n[i]),xe[i],&Isotope::FF,0*keV,50*keV,1);
      f2[i]->SetParameter(0,nuclearSkinThickness);
      f2[i]->SetLineColor(i+2);
   }
   TF1 *fe = new TF1("fe",xenon,&Element::FF,0*keV,50*keV,1);
   fe->SetParameter(0,nuclearSkinThickness);
   fe->SetLineColor(kBlack);
   fe->SetLineWidth(2);

   TF2 *fxs = new TF2("fxs",xenon,&Element::CNNSdXSF,
         0*keV,50*keV,0*MeV,100*MeV,0,"Element","CNNSdXSF");
   TF1 *fEr = new TF1("fEr",xenon,&Element::CNNSdXSEr,
         0*keV,50*keV,1,"Element","CNNSdXSEr");
   fEr->SetParameter(0,50*MeV);
   TF1 *fEv = new TF1("fEv",xenon,&Element::CNNSdXSEv,
         0*MeV,100*MeV,1,"Element","CNNSdXSEv");
   fEv->SetParameter(0,50*keV);

   TCanvas *can = new TCanvas;
   can->Print("xenon.ps[");

   fe->Draw();
   for (Int_t i=0; i<ni; i++) f2[i]->Draw("same");
   can->Print("xenon.ps");

   fxs->Draw("colz");
   can->Print("xenon.ps");

   fEr->Draw();
   can->Print("xenon.ps");

   fEv->Draw();
   can->Print("xenon.ps");

   can->Print("xenon.ps]");
}
