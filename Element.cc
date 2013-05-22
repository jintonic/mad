#include "Element.h"
#include "Isotope.h"

#include <TAxis.h>

using namespace UNIC;

//______________________________________________________________________________
//

MAD::Element::~Element()
{
   if (fF2) delete fF2;
   if (fDXS) delete fDXS;
   if (fDXSEr) delete fDXSEr;
   if (fDXSEv) delete fDXSEv;
}

//______________________________________________________________________________
//

Double_t MAD::Element::M() const
{
   if (!fNisotopes) return 0;

   Isotope *isotope;
   Double_t weight = 0.0;
   Double_t meff = 0.0;
   for (Int_t i=0; i<fNisotopes; i++) {
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
   for (Int_t i=0; i<fNisotopes; i++) {
      isotope = (Isotope*) fIsotopes->At(i);
      reff += fAbundances[i] * isotope->R();
      weight += fAbundances[i];
   }
   reff /= weight;
   return reff;
}

//______________________________________________________________________________
//

Double_t MAD::Element::F2(Double_t nuclearRecoilEnergy) 
{
   if (!fNisotopes) return 1.0;
   if (nuclearRecoilEnergy==0) return 1.0; // no momentum transfer

   Isotope *isotope;
   Double_t weight = 0.0;
   Double_t feff = 0.0;
   for (Int_t i=0; i<fNisotopes; i++) {
      isotope = (Isotope*) fIsotopes->At(i);
      feff += fAbundances[i] * 
         isotope->F2(nuclearRecoilEnergy);
      weight += fAbundances[i];
   }
   feff /= weight;

   return feff;
}

//______________________________________________________________________________
//

Double_t MAD::Element::CNNSdXS(Double_t nuclearRecoilEnergy, Double_t neutrinoEnergy) 
{
   if (!fNisotopes) return 0.0;

   Isotope *isotope;
   Double_t weight = 0.0;
   Double_t xseff = 0.0;
   for (Int_t i=0; i<fNisotopes; i++) {
      isotope = (Isotope*) fIsotopes->At(i);
      xseff += fAbundances[i] * 
         isotope->CNNSdXS(nuclearRecoilEnergy,neutrinoEnergy);
      weight += fAbundances[i];
   }
   xseff /= weight;

   return xseff;
}

//______________________________________________________________________________
//

Double_t MAD::Element::FF(Double_t *x, Double_t *parameters) 
{
   return F2(x[0]*keV);
}

//______________________________________________________________________________
//

TF1* MAD::Element::FormFactor2(Double_t maxNuclearRecoilEnergy) 
{
   if (!fF2) {
      fF2 = new TF1(Form("F2^%f_%f",M(),R()),
            this,&Element::FF,0,maxNuclearRecoilEnergy/keV,0);
      fF2->SetLineColor(kBlack);
      fF2->SetTitle(Form("%s nuclear form factor squared",GetTitle()));
      fF2->GetXaxis()->SetTitle("nuclear recoil energy [keVnr]");
      fF2->GetYaxis()->SetTitle("F^{2}");
   }
   return fF2;
}

//______________________________________________________________________________
//

Double_t MAD::Element::CNNSdXSF(Double_t *x, Double_t *parameters)
{
   return CNNSdXS(x[0]*keV,x[1]*MeV)*GeV*GeV*GeV;
}

//______________________________________________________________________________
//

TF2* MAD::Element::CNNSdXSF2(
      Double_t maxNuclearRecoilEnergy, Double_t maxNeutrinoEnergy) 
{
   if (!fDXS) {
      fDXS = new TF2(Form("fxs^%f_%f",M(),R()),
            this,&MAD::Element::CNNSdXSF,0.,maxNuclearRecoilEnergy/keV,
            0.,maxNeutrinoEnergy/MeV,0,"MAD::Element","CNNSdXSF");
      fDXS->GetXaxis()->SetTitle("nuclear recoil energy [keVnr]");
      fDXS->GetYaxis()->SetTitle("neutrino energy [MeV]");
      fDXS->GetZaxis()->SetTitle("differential cross section [1/GeV^{3}]");
      fDXS->GetZaxis()->CenterTitle();
      fDXS->GetZaxis()->SetTitleOffset(-0.5);
   }
   return fDXS;
}

//______________________________________________________________________________
//

Double_t MAD::Element::CNNSdXSEr(Double_t *x, Double_t *parameters)
{
   return CNNSdXS(x[0]*keV,parameters[0]*MeV)*GeV*GeV*GeV;
}

//______________________________________________________________________________
//

TF1* MAD::Element::CNNSdXSFEr(
      Double_t neutrinoEnergy, Double_t maxNuclearRecoilEnergy) 
{
   if (!fDXSEr) {
      fDXSEr = new TF1(Form("fxser^%f_%f",M(),R()),
            this,&MAD::Element::CNNSdXSEr,0.,maxNuclearRecoilEnergy/keV,1);
      fDXSEr->SetParameter(0,neutrinoEnergy/MeV);
      fDXSEr->SetTitle(Form("%.1f MeV neutrino", neutrinoEnergy/MeV));
      fDXSEr->GetXaxis()->SetTitle("nuclear recoil energy [keVnr]");
      fDXSEr->GetYaxis()->SetTitle("differential cross section [1/GeV^{3}]");
   }
   return fDXSEr;
}

//______________________________________________________________________________
//

Double_t MAD::Element::CNNSdXSEv(Double_t *x, Double_t *parameters)
{
   return CNNSdXS(parameters[0]*keV,x[0]*MeV)*GeV*GeV*GeV;
}

//______________________________________________________________________________
//

TF1* MAD::Element::CNNSdXSFEv(
      Double_t nuclearRecoilEnergy, Double_t maxNeutrinoEnergy) 
{
   if (!fDXSEv) {
      fDXSEv = new TF1(Form("fxsev^%f_%f",M(),R()),
            this,&MAD::Element::CNNSdXSEv,0.,maxNeutrinoEnergy/MeV,1);
      fDXSEv->SetParameter(0,nuclearRecoilEnergy/keV);
      fDXSEv->SetTitle(Form("%.1f keVnr nuclear recoil",
               nuclearRecoilEnergy/keV));
      fDXSEv->GetXaxis()->SetTitle("neutrino energy [MeV]");
      fDXSEv->GetYaxis()->SetTitle("differential cross section [1/GeV^{3}]");
   }
   return fDXSEv;
}

//______________________________________________________________________________
//

