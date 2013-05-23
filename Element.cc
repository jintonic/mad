#include "Element.h"
#include "Isotope.h"

#include <TF2.h>
#include <TAxis.h>

#include <UNIC/Units.h>
using namespace UNIC;

//______________________________________________________________________________
//

MAD::Element::~Element()
{
   if (fF2) delete fF2;
   if (fCNNSdXS2D) delete fCNNSdXS2D;
   if (fCNNSdXSEr) delete fCNNSdXSEr;
   if (fCNNSdXSEv) delete fCNNSdXSEv;
   if (fAbundances) delete[] fAbundances;
}

//______________________________________________________________________________
//

void MAD::Element::AddIsotope(Isotope *isotope, Double_t abundance)
{
   if (isotope==0) {
      Warning("AddIsotope", "Pointer to the isotope is NULL!");
      Warning("AddIsotope", "Failed to add isotope!");
      return;
   }

   if (abundance<=0) {
      Warning("AddIsotope", "The abundance <= zero!");
      Warning("AddIsotope", "Failed to add isotope!");
      return;
   }

   if (fNisotopes==0) {
      fIsotopes = new TObjArray(10); // initial capacity is 10 isotopes
      fAbundances = new Double_t[100]; // make an array big enough
      for (UShort_t i=0; i<100; i++) fAbundances[i]=0; // initialize array
   }

   if (fNisotopes>0) {
      UShort_t z = ((Isotope*) fIsotopes->At(0))->Z();
      if (z!=isotope->Z()) {
         Warning("AddIsotope", "Failed to add isotope with different Z!");
         return;
      }
   }

   Double_t totalAbundance=0;
   for (UShort_t i=0; i<fNisotopes; i++) totalAbundance+=fAbundances[i];
   if (totalAbundance>=1.) {
      Warning("AddIsotope", "Total abundance exceeds 100%%!");
      Warning("AddIsotope", "Failed to add new isotope!");
      return;
   }

   fIsotopes->Add(isotope);
   fAbundances[fNisotopes]=abundance;
   fNisotopes++;
}

//______________________________________________________________________________
//

MAD::Isotope* MAD::Element::GetIsotope(UShort_t i) const
{
   if (i<fNisotopes) return (Isotope*) fIsotopes->At(i);
   return 0;
}

//______________________________________________________________________________
//

Double_t MAD::Element::M() const
{
   if (!fNisotopes) return 0;

   Isotope *isotope;
   Double_t weight = 0.0;
   Double_t meff = 0.0;
   for (UShort_t i=0; i<fNisotopes; i++) {
      isotope = (Isotope*) fIsotopes->At(i);
      meff += fAbundances[i] * isotope->M();
      weight += fAbundances[i];
   }
   meff /= weight;
   return meff;
}

//______________________________________________________________________________
//

Double_t MAD::Element::R() const
{
   if (!fNisotopes) return 0;

   Isotope *isotope;
   Double_t weight = 0.0;
   Double_t reff = 0.0;
   for (UShort_t i=0; i<fNisotopes; i++) {
      isotope = (Isotope*) fIsotopes->At(i);
      reff += fAbundances[i] * isotope->R();
      weight += fAbundances[i];
   }
   reff /= weight;
   return reff;
}

//______________________________________________________________________________
//

Double_t MAD::Element::A() const
{
   if (!fNisotopes) return 0;

   Isotope *isotope;
   Double_t weight = 0.0;
   Double_t aeff = 0.0;
   for (UShort_t i=0; i<fNisotopes; i++) {
      isotope = (Isotope*) fIsotopes->At(i);
      aeff += fAbundances[i] * isotope->A();
      weight += fAbundances[i];
   }
   aeff /= weight;
   return aeff;
}

//______________________________________________________________________________
//

Double_t MAD::Element::N() const
{
   if (!fNisotopes) return 0;

   Isotope *isotope;
   Double_t weight = 0.0;
   Double_t neff = 0.0;
   for (UShort_t i=0; i<fNisotopes; i++) {
      isotope = (Isotope*) fIsotopes->At(i);
      neff += fAbundances[i] * isotope->N();
      weight += fAbundances[i];
   }
   neff /= weight;
   return neff;
}

//______________________________________________________________________________
//

Double_t MAD::Element::S() const
{
   if (fNisotopes) return ((Isotope*) fIsotopes->At(0))->S();
   return 0.;
}

//______________________________________________________________________________
//

UShort_t MAD::Element::Z() const
{
   if (fNisotopes) return ((Isotope*) fIsotopes->At(0))->Z();
   return 0;
}

//______________________________________________________________________________
//

void MAD::Element::Print(Option_t *option)
{
   if (!fNisotopes) {
      Printf("No isotope in element %s", GetName());
      return;
   }

   Printf("There are %d isotopes in element %s (N=%.2f, A=%.2f g/mole) :", 
         fNisotopes, GetName(), N(), A()/(gram/mole));

   for (UShort_t i=0; i<fNisotopes; i++) {
      Isotope *isotope = (Isotope*) fIsotopes->At(i);
      Printf("%d: %s abundance=%5.2f%%", i, 
            isotope->GetName(), fAbundances[i]/perCent);
      isotope->Print(option);
   }
}

//______________________________________________________________________________
//

Double_t MAD::Element::F2(Double_t Er) 
{
   if (!fNisotopes) return 1.0;
   if (Er==0) return 1.0; // no momentum transfer

   Isotope *isotope;
   Double_t weight = 0.0;
   Double_t feff = 0.0;
   for (UShort_t i=0; i<fNisotopes; i++) {
      isotope = (Isotope*) fIsotopes->At(i);
      feff += fAbundances[i] * isotope->F2(Er);
      weight += fAbundances[i];
   }
   feff /= weight;

   return feff;
}

//______________________________________________________________________________
//

Double_t MAD::Element::CNNSdXS(Double_t Er, Double_t Ev) 
{
   if (!fNisotopes) return 0.0;

   Isotope *isotope;
   Double_t weight = 0.0;
   Double_t xseff = 0.0;
   for (Int_t i=0; i<fNisotopes; i++) {
      isotope = (Isotope*) fIsotopes->At(i);
      xseff += fAbundances[i] * isotope->CNNSdXS(Er,Ev);
      weight += fAbundances[i];
   }
   xseff /= weight;

   return xseff;
}

//______________________________________________________________________________
//

Double_t MAD::Element::FormFactor2(Double_t *x, Double_t *parameters) 
{
   return F2(x[0]*keV);
}

//______________________________________________________________________________
//

TF1* MAD::Element::FF2(Double_t maxEr) 
{
   if (fF2) return fF2;
   fF2 = new TF1(Form("F2^%f_%f",M(),R()),
         this, &Element::FormFactor2, 0, maxEr, 0);
   fF2->SetLineColor(kBlack);
   fF2->SetTitle(Form("%s nuclear form factor squared",GetTitle()));
   fF2->GetXaxis()->SetTitle("nuclear recoil energy [keV]");
   fF2->GetYaxis()->SetTitle("F^{2}");
   return fF2;
}

//______________________________________________________________________________
//

Double_t MAD::Element::CNNSdXS2D(Double_t *x, Double_t *parameters)
{
   return CNNSdXS(x[0]*keV,x[1]*MeV)*GeV*GeV*GeV;
}

//______________________________________________________________________________
//

TF2* MAD::Element::FCNNSdXS2D(Double_t maxEr, Double_t maxEv) 
{
   if (fCNNSdXS2D) return fCNNSdXS2D;
   fCNNSdXS2D = new TF2(Form("fCNNSdXS2D^%f_%f",M(),R()), this,
         &Element::CNNSdXS2D, 0., maxEr, 0., maxEv, 0, "Element", "CNNSdXS2D");
   fCNNSdXS2D->GetXaxis()->SetTitle("nuclear recoil energy [keV]");
   fCNNSdXS2D->GetYaxis()->SetTitle("neutrino energy [MeV]");
   fCNNSdXS2D->GetZaxis()->SetTitle("differential cross section [1/GeV^{3}]");
   fCNNSdXS2D->GetZaxis()->CenterTitle();
   fCNNSdXS2D->GetZaxis()->SetTitleOffset(-0.5);
   return fCNNSdXS2D;
}

//______________________________________________________________________________
//

Double_t MAD::Element::CNNSdXSEr(Double_t *x, Double_t *parameters)
{
   return CNNSdXS(x[0]*keV,parameters[0]*MeV)*GeV*GeV*GeV;
}

//______________________________________________________________________________
//

TF1* MAD::Element::FCNNSdXSEr(Double_t Ev, Double_t maxEr) 
{
   if (fCNNSdXSEr) return fCNNSdXSEr;
   fCNNSdXSEr = new TF1(Form("fCNNSdXSEr^%f_%f",M(),R()),
         this, &Element::CNNSdXSEr, 0., maxEr, 1);
   fCNNSdXSEr->SetParameter(0,Ev);
   fCNNSdXSEr->SetTitle(Form("%.1f MeV neutrino", Ev));
   fCNNSdXSEr->GetXaxis()->SetTitle("nuclear recoil energy [keV]");
   fCNNSdXSEr->GetYaxis()->SetTitle("differential cross section [1/GeV^{3}]");
   return fCNNSdXSEr;
}

//______________________________________________________________________________
//

Double_t MAD::Element::CNNSdXSEv(Double_t *x, Double_t *parameters)
{
   return CNNSdXS(parameters[0]*keV,x[0]*MeV)*GeV*GeV*GeV;
}

//______________________________________________________________________________
//

TF1* MAD::Element::FCNNSdXSEv(Double_t Er, Double_t maxEv) 
{
   if (fCNNSdXSEv) return fCNNSdXSEv;
   fCNNSdXSEv = new TF1(Form("fCNNSdXSEv^%f_%f",M(),R()),
         this, &Element::CNNSdXSEv, 0., maxEv, 1);
   fCNNSdXSEv->SetParameter(0,Er);
   fCNNSdXSEv->SetTitle(Form("%.1f keV nuclear recoil", Er));
   fCNNSdXSEv->GetXaxis()->SetTitle("neutrino energy [MeV]");
   fCNNSdXSEv->GetYaxis()->SetTitle("differential cross section [1/GeV^{3}]");
   return fCNNSdXSEv;
}

//______________________________________________________________________________
//

