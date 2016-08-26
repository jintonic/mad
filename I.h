#ifndef MAD_I_H
#define MAD_I_H

#include "Element.h"
namespace MAD{class I;}

class MAD:: I : public Element
{
  public:
    I(const  char *name="I", const char *title="I");
    virtual ~I(){};

    ClassDef(I,1);
};


#endif
