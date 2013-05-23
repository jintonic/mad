#ifndef LIQUIDXENON_H
#define LIQUIDXENON_H

#include "Material.h"
class TGraphErrors;

namespace MAD { class LiquidXenon; }

class MAD::LiquidXenon : public Material
{
   protected:
      TGraphErrors *fLeff;

   public:
      LiquidXenon(const char *name="LXe", const char *title="liquid xenon") 
         : Material(name, title), fLeff(0) {};
      virtual ~LiquidXenon();

      TGraphErrors *Leff();

      Double_t Eee(Double_t nuclearRecoilEnergy); // recoil energy in keVee

      ClassDef(LiquidXenon,1);
};

#endif
