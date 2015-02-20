#ifndef GECRYSTAL_H
#define GECRYSTAL_H

#include "Material.h"

namespace MAD { class GeCrystal; }

class MAD::GeCrystal : public Material
{
   public:
      GeCrystal(const char *name="GeCry", const char *title="Ge Crystal") 
         : Material(name, title); 
      virtual ~GeCrystal() {};

      Double_t MuE(Double_t T=0, Double_t E=0);
      Double_t MuH(Double_t T=0, Double_t E=0);
      Double_t Epsilon();

      ClassDef(GeCrystal,1);
};

#endif

