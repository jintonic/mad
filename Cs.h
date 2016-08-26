#ifndef MAD_CS_H
#define MAD_CS_H

#include "Element.h"
namespace MAD{class Cs;}

class MAD:: Cs : public Element
{
  public:
    Cs(const  char *name="Cs", const char *title="Cs");
    virtual ~Cs(){};

    ClassDef(Cs,1);
};


#endif
