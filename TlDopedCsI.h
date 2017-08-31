#ifndef MAD_TLDOPED_CSI_H
#define MAD_TLDOPED_CSI_H

#include "CsI.h"
class TGraphErrors;
class TF1;

namespace MAD { class TlDopedCsI; }

class MAD::TlDopedCsI: public CsI
{
   protected:
      TGraphErrors* fQ; ///< Total quenching factor VS Enr
      TF1* fLindhardQF;

   public:
      TlDopedCsI(const char *name="TlDopedCsI", const char *title="TlDopedCsI")
         :CsI(name , title), fQ(0), fLindhardQF(0) {};
      virtual ~TlDopedCsI();

      TGraphErrors* Q();
      double Q(double Enr);

      ClassDef(TlDopedCsI,1);
};

#endif
