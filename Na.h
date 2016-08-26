#ifndef MAD_NA_H
#define MAD_NA_H

#include "Element.h"
namespace MAD{class Na;}

class MAD:: Na : public Element
{
  public:
    Na(const  char *name="Na", const char *title="Na");
    virtual ~Na(){};

    ClassDef(Na,1);
};


#endif
