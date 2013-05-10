#include <TGeoElement.h>
#include <CLHEP/Units/SystemOfUnits.h>

class Isotope : public TGeoIsotope
{
   protected:
      Double_t fM; // nuclear mass
      Double_t fR; // nuclear radius

   public:
      Isotope() : TGeoIsotope(), fM(0), fR(0) {};
      Isotope(Int_t z, Int_t n) : TGeoIsotope(), fM(0), fR(0) { fZ=z; fN=n; }
      virtual ~Isotope() {};

      void SetR(Double_t atomicRadius) { fR=atomicRadius; }
      Double_t R() { return fR; }

      void SetM(Double_t nuclearMass) { fM=nuclearMass; }
      Double_t M() { return fM; }

      Double_t A() { return fA; }
      Int_t Z() { return fZ; }
      Int_t N() { return fN; }

      Double_t F2(Double_t nuclearRecoilEnergy=0*CLHEP::keV,
            Double_t nuclearSkinThickness=1*CLHEP::fermi);
      Double_t FF(Double_t *x, Double_t *parameters)
      { return F2(*x, *parameters); }

      Double_t CNNSdXS(Double_t nuclearRecoilEnergy=0*CLHEP::keV,
            Double_t neutrinoEnergy=0*CLHEP::MeV);
      Double_t CNNSdXSF(Double_t *x, Double_t *parameters)
      { return CNNSdXS(x[0],x[1]); }

      ClassDef(Isotope,1);
};
