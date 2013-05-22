#ifndef ELEMENT_HH
#define ELEMENT_HH

#include <TF2.h>
#include <TGeoElement.h>

#include <UNIC/Units.h>

class Element : public TGeoElement
{
   private:
      Double_t FF(Double_t *x, Double_t *parameters);
      Double_t CNNSdXSF(Double_t *x, Double_t *parameters);
      Double_t CNNSdXSEr(Double_t *x, Double_t *parameters);
      Double_t CNNSdXSEv(Double_t *x, Double_t *parameters);

   protected:
      TF1 *fF2;    // form factor in TF1 format
      TF2 *fDXS;   // CNNS differencial cross section in TF2 format
      TF1 *fDXSEr; // CNNS differencial cross section in TF1 format
      TF1 *fDXSEv; // CNNS differencial cross section in TF1 format

   public:
      Element() : TGeoElement(), fF2(0), fDXS(0), fDXSEr(0), fDXSEv(0) {};
      Element(Int_t nIsotopes) : TGeoElement("","",nIsotopes), 
      fF2(0), fDXS(0), fDXSEr(0), fDXSEv(0) {};
      virtual ~Element();

      Double_t R() const; // average nuclear radius
      Double_t M() const; // average nuclear mass

      Double_t F2(Double_t nuclearRecoilEnergy); // form factor squared
      TF1* FormFactor2(Double_t maxNuclearRecoilEnergy=50*UNIC::keV);

      // CNNS differential cross section
      Double_t CNNSdXS(Double_t nuclearRecoilEnergy, Double_t neutrinoEnergy);
      TF2* CNNSdXSF2(Double_t maxNuclearRecoilEnergy=50*UNIC::keV, 
            Double_t maxNeutrinoEnergy=100*UNIC::MeV);
      TF1* CNNSdXSFEr(Double_t neutrinoEnergy,
            Double_t maxNuclearRecoilEnergy=50*UNIC::keV);
      TF1* CNNSdXSFEv(Double_t nuclearRecoilEnergy,
            Double_t maxNeutrinoEnergy=100*UNIC::MeV);

      ClassDef(Element,1);
};

#endif // ELEMENT_HH
