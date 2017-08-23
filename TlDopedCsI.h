#ifndef MAD_TLDOPED_CSI_H
#define MAD_TLDOPED_CSI_H

#include "Material.h"
#include "Cs.h"
#include "I.h"
class TGraphErrors;
class TF1;

namespace MAD { class TlDopedCsI; }

class MAD::TlDopedCsI: public Material
{
   protected:
      TGraphErrors* fQFvsEnr;
      TF1* fLindhardQF;

      /**
       * Lindhard quenching factor.
       * Ref. to page 10, https://arxiv.org/pdf/1203.4620.pdf
       */
      double LindhardQF(double *x, double *par);

   public:
      TlDopedCsI(const char *name="TlDopedCsI", const char *title="TlDopedCsI")
         :Material(name , title), fQFvsEnr(0), fLindhardQF(0)
         { AddElement(new I(),1); AddElement(new Cs(),1); }
      virtual ~TlDopedCsI();

      TGraphErrors* QFvsEnr();
      double QF(double Enr);

      ClassDef(TlDopedCsI,1);
};

#endif
