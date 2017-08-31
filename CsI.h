#ifndef MAD_CSI_H
#define MAD_CSI_H

#include "Material.h"
#include "Cs.h"
#include "I.h"

namespace MAD { class CsI; }

class MAD::CsI: public Material
{
   public:
      CsI(const char *name="CsI", const char *title="CsI")
         :Material(name , title)
         { AddElement(new I(), 1); AddElement(new Cs(), 1); }
      virtual ~CsI() {};

      TGraph* Sp(); ///< Electronic stopping power plot for proton

      /**
       * Electronic stopping power for proton.
       * Ref. https://physics.nist.gov/PhysRefData/Star/Text/PSTAR.html
       */
      double Sp(double protonEnergy);

      ClassDef(CsI,1);
};

#endif
