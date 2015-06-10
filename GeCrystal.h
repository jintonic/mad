#ifndef GECRYSTAL_H
#define GECRYSTAL_H

#include "Material.h"

class TGraph;

namespace MAD { class GeCrystal; }

class MAD::GeCrystal : public Material
{
   public:
      Double_t T; // temperature in K
      TGraph *gRhop, *gRhon;

   public:
      GeCrystal(const char *name="GeCrystal", const char *title="Ge Crystal");
      virtual ~GeCrystal();

      /**
       * Total mobility.
       */
      Double_t Mu(char type='e', Double_t n=0);
      /**
       * Measured mobility of HPGe at 77K.
       * Refer to Jing LIU's Ph.D. thesis.
       * Neutral impurity contributes most.
       */
      Double_t MuN(char type='e', Int_t idx=100);
      /**
       * Mobility based on BH model.
       * Refer to D. Chattopadhyay & H. Queisser, "Electron scattering by
       * ionized impurities in semiconductors", Rev. Mod. Phys., vol. 53, no.
       * 4, pp. 745–768, Oct. 1981. It is only valid up to n ~ 1e18 1/cm3.
       */
      Double_t MuBH(char type='e', Double_t n=0);
      /**
       * Hall Mobility.
       * mu = v/E = I/(enA)/(U/l) = 1/(enA/l*U/I) = 1/(enA/l*R) 
       *    = 1/(enA/l*rho*l/A) = 1/(e*n*rho)
       */
      Double_t MuHall(char type='e', Double_t n=0);
      /**
       * Resistivity
       * The relation between resistivity, rho, and impurity concentration, n,
       * is taken from S. M. Sze and J. C. Irvin, "Resistivity, mobility and
       * impurity levels in GaAs, Ge, and Si at 300 K", Solid. State.
       * Electron., vol. 11, no. 6, pp. 599–602, Jun. 1968. According to C.
       * Hung and J. Gliessman, "Resistivity and Hall Effect of Germanium at
       * Low Temperatures", Phys.  Rev., vol. 96, no. 5, pp. 1226–1236, Dec.
       * 1954, when n>4e18/cm3, the resistivity does not change with
       * temperature. The result obtained at 300K can also be used at 77K.
       */
      Double_t Rho(char type='n', Double_t n=0);
      /**
       * Relative dielectric constant
       */
      Double_t Epsilon() { return 16.2; }
      /**
       * m*_e/m_e or m*_h/m_e
       */
      Double_t EffectiveMassRatio(char type='e');

      ClassDef(GeCrystal,1);
};

#endif
