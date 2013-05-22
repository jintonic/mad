#ifndef LIQUIDXENON_H
#define LIQUIDXENON_H

#include "Material.h"
#include <TGraphErrors.h>

namespace MAD { class LiquidXenon; }

class MAD::LiquidXenon : public Material
{
   protected:
      TGraphErrors *fLeff;

   public:
      LiquidXenon() 
         : Material(), fLeff(0) 
      { SetName("LXe"); SetTitle("liquid xenon"); }
      virtual ~LiquidXenon() { if (fLeff) delete fLeff; }

      TGraphErrors *Leff();

      Double_t Eee(Double_t nuclearRecoilEnergy); // recoil energy in keVee

      ClassDef(LiquidXenon,1);
};

#endif
