#ifndef MAD_TLDOPED_CSI_H
#define MAD_TLDOPED_CSI_H

#include "Material.h"
#include "Cs.h"
#include "I.h"
class TGraphErrors;

namespace MAD { class TlDopedCsI; }

class MAD::CsI: public Material
{
  public:
    TlDopedCsI(const char *name="TlDopedCsI", const char *title="TlDopedCsI")
      :Material(name , title) { AddElement(new I(),1); AddElement(new Cs(),1); }
    virtual ~TlDopedCsI() { if (fQFvsEnr) delete fQFvsEnr; }

    TGraphErrors* QFvsEnr();

    classDef(TlDopedCsI,1);

  protected:
    TGraphErrors* fQFvsEnr;
}

#endif
