#ifndef GECRYSTAL_H
#define GECRYSTAL_H

#include "Material.h"

namespace MAD { class GeCrystal; }

class MAD::GeCrystal : public Material
{
   public:
      Double_t T; // temperature in K
   public:
      GeCrystal(const char *name="GeCrystal", const char *title="Ge Crystal")
         : Material(name, title) {}; 
      virtual ~GeCrystal() {};

      Double_t MuEn(Int_t idx=100);
      Double_t MuHn(Int_t idx=100);
      Double_t MuEi(Double_t n=0);
      Double_t MuHi(Double_t n=0);
      Double_t MuE(Int_t idx=100, Double_t n=0);
      Double_t MuH(Int_t idx=100, Double_t n=0);
      Double_t Epsilon();

      ClassDef(GeCrystal,1);
};

#endif

