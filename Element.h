#ifndef ELEMENT_H
#define ELEMENT_H

#include <TF2.h>
#include <TGeoElement.h>

#include <UNIC/Units.h>

namespace MAD { class Element; }

class MAD::Element : public TGeoElement
{
   protected:
      Double_t FF(Double_t *x, Double_t *parameters);
      Double_t CNNSdXS2D(Double_t *x, Double_t *parameters);
      Double_t CNNSdXSEr(Double_t *x, Double_t *parameters);
      Double_t CNNSdXSEv(Double_t *x, Double_t *parameters);

      TF1 *fF2;    // form factor in TF1 format
      TF2 *fDXS2D; // CNNS differencial cross section in TF2 format
      TF1 *fDXSEr; // CNNS differencial cross section in TF1 format
      TF1 *fDXSEv; // CNNS differencial cross section in TF1 format

   public:
      Element() : TGeoElement(), fF2(0), fDXS2D(0), fDXSEr(0), fDXSEv(0) {};
      Element(const char* name, const char* title, Int_t nIsotopes) : 
         TGeoElement(name, title, nIsotopes), 
         fF2(0), fDXS2D(0), fDXSEr(0), fDXSEv(0) {};
      virtual ~Element();

      Double_t R() const; // average nuclear radius
      Double_t M() const; // average nuclear mass

      virtual void Print(Option_t *option="");

      Double_t F2(Double_t nuclearRecoilEnergy); // form factor squared
      TF1* FF2(Double_t maxNuclearRecoilEnergy=50*UNIC::keV);

      // CNNS differential cross section
      Double_t CNNSdXS(Double_t nuclearRecoilEnergy, Double_t neutrinoEnergy);
      TF2* FCNNSdXS2D(Double_t maxNuclearRecoilEnergy=50*UNIC::keV, 
            Double_t maxNeutrinoEnergy=100*UNIC::MeV);
      TF1* FCNNSdXSEr(Double_t neutrinoEnergy,
            Double_t maxNuclearRecoilEnergy=50*UNIC::keV);
      TF1* FCNNSdXSEv(Double_t nuclearRecoilEnergy,
            Double_t maxNeutrinoEnergy=100*UNIC::MeV);

      ClassDef(Element,1);
};

#endif
