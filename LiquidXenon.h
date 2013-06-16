#ifndef LIQUIDXENON_H
#define LIQUIDXENON_H

#include "Material.h"
class TGraphErrors;

namespace MAD { class LiquidXenon; }

class MAD::LiquidXenon : public Material
{
   protected:
      TGraphErrors *fLeff;
      TGraphErrors *fEnrEee;
      TGraphErrors *fEnrPE;

   public:
      LiquidXenon(const char *name="LXe", const char *title="liquid xenon") 
         : Material(name, title), fLeff(0), fEnrEee(0) {};
      virtual ~LiquidXenon();

      TGraphErrors* Leff();
      TGraphErrors* EnrEee();
      TGraphErrors* EnrPE(Double_t lightYield);

      Double_t Eee(Double_t energy_keVnr); // recoil energy in keVee
      Double_t Enr(Double_t energy_keVee); // recoil energy in keVnr

      ClassDef(LiquidXenon,1);
};

#endif
