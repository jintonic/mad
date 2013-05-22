#ifndef ISOTOPE_H
#define ISOTOPE_H

#include <TGeoElement.h>

namespace MAD { class Isotope; }

class MAD::Isotope : public TGeoIsotope
{
   protected:
      Double_t fM; // nuclear mass
      Double_t fR; // nuclear radius
      Double_t fS; // nuclear skin thickness

   public:
      Isotope();
      Isotope(Int_t z, Int_t n);
      virtual ~Isotope() {};

      void SetA(Double_t atomicMass) { fA=atomicMass; }
      Double_t A() { return fA; }

      void SetM(Double_t nuclearMass) { fM=nuclearMass; }
      Double_t M() { return fM; }

      void SetR(Double_t atomicRadius) { fR=atomicRadius; }
      Double_t R() { return fR; }

      void SetS(Double_t nuclearSkinThickness) { fS=nuclearSkinThickness; }
      Double_t S() { return fS; }

      Int_t Z() { return fZ; }
      Int_t N() { return fN; }

      virtual void Print(Option_t *option="");

      Double_t F2(Double_t nuclearRecoilEnergy); // form factor squared

      // differential cross section of CNNS
      Double_t CNNSdXS(Double_t nuclearRecoilEnergy, Double_t neutrinoEnergy);

      ClassDef(Isotope,1);
};

#endif
