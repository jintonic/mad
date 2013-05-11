#ifndef LIQUIDXENON_HH
#define LIQUIDXENON_HH

#include <TGeoMaterial.h>
#include <TGraphErrors.h>

class LiquidXenon : public TGeoMaterial
{
   protected:
      TGraphErrors *fLeff;

   public:
      LiquidXenon() : TGeoMaterial(), fLeff(0) { SetName("LXe"); }
      virtual ~LiquidXenon() { if (fLeff) delete fLeff; }

      void SetElement(TGeoElement *element=NULL);

      TGraphErrors *Leff();

      Double_t Eee(Double_t nuclearRecoilEnergy); // recoil energy in keVee

      ClassDef(LiquidXenon,1);
};

#endif // LIQUIDXENON_HH
