#ifndef ELEMENT_HH
#define ELEMENT_HH

class TF1;
#include <TGeoElement.h>

class Element : public TGeoElement
{
   private:
      Double_t FF(Double_t *x, Double_t *parameters);

   protected:
      TF1*     fF2;// form factor in TF1 format

   public:
      Element() : TGeoElement(), fF2(0) {};
      Element(Int_t nIsotopes) : TGeoElement("","",nIsotopes), fF2(0) {};
      virtual ~Element() {};

      Double_t Reff() const;
      Double_t Meff() const;

      Double_t F2(Double_t nuclearRecoilEnergy);
      TF1* FormFactor2(Double_t maxNuclearRecoilEnergy=50/*keV*/);

      Double_t CNNSdXS(Double_t nuclearRecoilEnergy, Double_t neutrinoEnergy);
      Double_t CNNSdXSF(Double_t *x, Double_t *parameters);
      Double_t CNNSdXSEr(Double_t *x, Double_t *parameters);
      Double_t CNNSdXSEv(Double_t *x, Double_t *parameters);

      ClassDef(Element,1);
};

#endif // ELEMENT_HH
