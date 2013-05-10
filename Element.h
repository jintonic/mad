#include <TGeoElement.h>
#include <CLHEP/Units/SystemOfUnits.h>

class Element : public TGeoElement
{
   public:
      Element() : TGeoElement() {};
      Element(Int_t nIsotopes) : TGeoElement("","",nIsotopes) {};
      virtual ~Element() {};

      Double_t Reff() const;
      Double_t Meff() const;

      Double_t F2(Double_t nuclearRecoilEnergy=0*CLHEP::keV,
            Double_t nuclearSkinThickness=1*CLHEP::fermi);
      Double_t FF(Double_t *x, Double_t *parameters)
      { return F2(*x, *parameters); }

      Double_t CNNSdXS(Double_t nuclearRecoilEnergy=0*CLHEP::keV,
            Double_t neutrinoEnergy=0*CLHEP::MeV);
      Double_t CNNSdXSF(Double_t *x, Double_t *parameters)
      { return CNNSdXS(x[0],x[1]); }
      Double_t CNNSdXSEr(Double_t *x, Double_t *parameters)
      { return CNNSdXS(x[0],parameters[0]); }
      Double_t CNNSdXSEv(Double_t *x, Double_t *parameters)
      { return CNNSdXS(parameters[0],x[0]); }

      ClassDef(Element,1);
};
