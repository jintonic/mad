#ifndef GECRYSTAL_H
#define GECRYSTAL_H

#include "Material.h"

class TGraph;

namespace MAD { class GeCrystal; }

class MAD::GeCrystal : public Material
{
   public:
      Double_t T; // temperature in K
      TGraph *gMuHallp, *gMuHalln;

   public:
      GeCrystal(const char *name="GeCrystal", const char *title="Ge Crystal");
      virtual ~GeCrystal();

      /**
       * Mobility determined by neutral impurity.
       */
      Double_t Mun(const char *type="e", Int_t idx=100);
      /**
       * Mobility determined by ionized impurity.
       */
      Double_t Mui(const char *type="e", Double_t n=0);
      /**
       * Hall Mobility.
       */
      Double_t MuHall(const char *type="n", Double_t n=0);
      /**
       * Resistivity at n>1e18/cm3
       */
      Double_t Rho(const char *type="n", Double_t n=0);
      Double_t Mu(const char *type="e", Int_t idx=100, Double_t n=0)
      { return 1./(1./Mun(type,idx) + 1./Mui(type,n)); }

      Double_t Epsilon() ///< relative diaelectric constant
      { return 16.2; }

      Double_t EffectiveMassRatio(const char *type="e"); ///< m_e*/m_e

      ClassDef(GeCrystal,1);
};

#endif
