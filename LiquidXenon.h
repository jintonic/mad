#ifndef LIQUIDXENON_H
#define LIQUIDXENON_H

#include "Material.h"
class TGraphErrors;

namespace MAD { class LiquidXenon; }

class MAD::LiquidXenon : public Material
{
   protected:
      TGraphErrors *fLeff; // Graph of Leff VS Enr
      TGraphErrors *fEnrPE; // Graph of Enr VS PE

   public:
      LiquidXenon(const char *name="LXe", const char *title="liquid xenon") 
         : Material(name, title), fLeff(0), fEnrPE(0) {};
      virtual ~LiquidXenon();

      TGraphErrors* Leff();
      TGraphErrors* EnrPE(Double_t lightYield);

      ClassDef(LiquidXenon,1);
};

#endif
