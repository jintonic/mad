#ifndef ISOTOPE_H
#define ISOTOPE_H

#include <TNamed.h>

namespace MAD { class Isotope; }

class MAD::Isotope : public TNamed
{
   protected:
      UShort_t fZ; // atomic number
      UShort_t fN; // number of nucleons
      Double_t fA; // atomic mass
      Double_t fM; // nuclear mass
      Double_t fR; // nuclear radius
      Double_t fS; // nuclear skin thickness

   public:
      Isotope();
      Isotope(UShort_t z, UShort_t n);
      virtual ~Isotope() {};

      void SetZ(UShort_t atomicNumber) { fZ=atomicNumber; }
      UShort_t Z() { return fZ; }

      void SetN(UShort_t nNucleons) { fN=nNucleons; }
      UShort_t N() { return fN; }

      void SetA(Double_t atomicMass) { fA=atomicMass; }
      Double_t A() { return fA; }

      void SetM(Double_t nuclearMass) { fM=nuclearMass; }
      Double_t M() { return fM; }

      void SetR(Double_t atomicRadius) { fR=atomicRadius; }
      Double_t R() { return fR; }

      void SetS(Double_t nuclearSkinThickness) { fS=nuclearSkinThickness; }
      Double_t S() { return fS; }

      virtual void Print(Option_t *option="");

      Double_t F2(Double_t nuclearRecoilEnergy); // form factor squared

      // differential cross section of CNNS
      Double_t CNNSdXS(Double_t nuclearRecoilEnergy, Double_t neutrinoEnergy);

      ClassDef(Isotope,1);
};

#endif
