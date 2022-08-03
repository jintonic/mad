#ifndef MAD_NAI_H
#define MAD_NAI_H

#include "Material.h"
#include "Na.h"
#include "I.h"
class TGraphErrors;

namespace MAD{class NaI;}
class MAD::NaI:public Material
{
  public:
    NaI(const char *name="NaI", const char *title="NaI")
      :Material(name , title){AddElement(new I(),1);AddElement(new Na(),1);};
    virtual ~NaI();

    ClassDef(NaI,1);
};

#endif
