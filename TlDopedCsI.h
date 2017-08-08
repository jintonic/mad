#ifndef MAD_TLDOPED_CSI_H
#define MAD_TLDOPED_CSI_H

#include "Material.h"
#include "Cs.h"
#include "I.h"
class TGraphErrors;

namespace MAD { class TlDopedCsI; }

class MAD::TlDopedCsI: public Material
{
   protected:
      TGraphErrors* fQFvsEnr;

   public:
      TlDopedCsI(const char *name="TlDopedCsI", const char *title="TlDopedCsI")
         :Material(name , title), fQFvsEnr(0)
         { AddElement(new I(),1); AddElement(new Cs(),1); }
      virtual ~TlDopedCsI();

      TGraphErrors* QFvsEnr();

      ClassDef(TlDopedCsI,1);
};

#endif
