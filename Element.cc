#include "Element.h"
#include "Isotope.h"

#include <TF1.h>
#include <TAxis.h>

#include <CLHEP/Units/SystemOfUnits.h>
using namespace CLHEP;

//______________________________________________________________________________
//

Double_t Element::Meff() const
{
   if (!fNisotopes) return 0;

   Isotope *isocrt;
   Double_t weight = 0.0;
   Double_t meff = 0.0;
   for (Int_t i=0; i<fNisotopes; i++) {
      isocrt = (Isotope*) fIsotopes->At(i);
      meff += fAbundances[i] * isocrt->M();
      weight += fAbundances[i];
   }
   meff /= weight;
   return meff;
}

//______________________________________________________________________________
//

Double_t Element::Reff() const
{
   if (!fNisotopes) return 0;

   Isotope *isocrt;
   Double_t weight = 0.0;
   Double_t reff = 0.0;
   for (Int_t i=0; i<fNisotopes; i++) {
      isocrt = (Isotope*) fIsotopes->At(i);
      reff += fAbundances[i] * isocrt->R();
      weight += fAbundances[i];
   }
   reff /= weight;
   return reff;
}

//______________________________________________________________________________
//

Double_t Element::F2(Double_t nuclearRecoilEnergy) 
{
   if (!fNisotopes) return 1.0;
   if (nuclearRecoilEnergy==0) return 1.0; // no momentum transfer

   Isotope *isocrt;
   Double_t weight = 0.0;
   Double_t feff = 0.0;
   for (Int_t i=0; i<fNisotopes; i++) {
      isocrt = (Isotope*) fIsotopes->At(i);
      feff += fAbundances[i] * 
         isocrt->F2(nuclearRecoilEnergy);
      weight += fAbundances[i];
   }
   feff /= weight;

   return feff;
}

//______________________________________________________________________________
//

Double_t Element::CNNSdXS(Double_t nuclearRecoilEnergy, Double_t neutrinoEnergy) 
{
   if (!fNisotopes) return 0.0;

   Isotope *isocrt;
   Double_t weight = 0.0;
   Double_t xseff = 0.0;
   for (Int_t i=0; i<fNisotopes; i++) {
      isocrt = (Isotope*) fIsotopes->At(i);
      xseff += fAbundances[i] * 
         isocrt->CNNSdXS(nuclearRecoilEnergy,neutrinoEnergy);
      weight += fAbundances[i];
   }
   xseff /= weight;

   return xseff;
}

//______________________________________________________________________________
//

Double_t Element::FF(Double_t *x, Double_t *parameters) 
{ return F2(x[0]*keV); }

//______________________________________________________________________________
//

TF1* Element::FormFactor2(Double_t maxNuclearRecoilEnergy) 
{
   if (!fF2) {
      fF2 = new TF1(Form("F2^%f_%f",Meff(),Reff()),
            this,&Element::FF,0,maxNuclearRecoilEnergy,0);
      fF2->SetLineColor(kBlack);
      fF2->SetTitle("Nuclear form factor squared");
      fF2->GetXaxis()->SetTitle("nuclear recoil energy [keVnr]");
      fF2->GetYaxis()->SetTitle("F^{2}");
   }
   return fF2;
}

//______________________________________________________________________________
//

Double_t Element::CNNSdXSF(Double_t *x, Double_t *parameters)
{ return CNNSdXS(x[0]*keV,x[1]*MeV); }

//______________________________________________________________________________
//

Double_t Element::CNNSdXSEr(Double_t *x, Double_t *parameters)
{ return CNNSdXS(x[0]*keV,parameters[0]*MeV); }

//______________________________________________________________________________
//

Double_t Element::CNNSdXSEv(Double_t *x, Double_t *parameters)
{ return CNNSdXS(parameters[0]*keV,x[0]*MeV); }

//______________________________________________________________________________
//

