#ifndef LIQUIDXENON_H
#define LIQUIDXENON_H

#include <TGeoMaterial.h>
#include <TGraphErrors.h>

namespace MAD { class LiquidXenon; }

class MAD::LiquidXenon : public TGeoMaterial
{
   protected:
      TGraphErrors *fLeff;

   public:
      LiquidXenon() 
         : TGeoMaterial(), fLeff(0) 
      { SetName("LXe"); SetTitle("liquid xenon"); }
      virtual ~LiquidXenon() { if (fLeff) delete fLeff; }

      void SetElement(TGeoElement *element=NULL);

      TGraphErrors *Leff();

      Double_t Eee(Double_t nuclearRecoilEnergy); // recoil energy in keVee

      ClassDef(LiquidXenon,1);
};

#endif
