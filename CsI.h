#ifndef MAD_CSI_H
#define MAD_CSI_H

#include "Material.h"
#include "Cs.h"
#include "I.h"
class TGraphErrors;

namespace MAD{class CsI;}
class MAD::CsI:public Material
{
  public:
    CsI(const char *name="CsI", const char *title="CsI")
      :Material(name , title){AddElement(new I(),1);AddElement(new Cs(),1);};
    virtual ~CsI();

    classDef(CsI,1);
}

#endif
