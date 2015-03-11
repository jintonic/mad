#ifndef NATURALGE_H
#define NATURALGE_H

#include "Element.h"

namespace MAD { class NaturalGe; }

class MAD::NaturalGe : public Element
{
   public:
      NaturalGe(const char *name="NaturalGe", const char *title="Natural Ge");
      virtual ~NaturalGe() {};


      ClassDef(NaturalGe,1);
};

#endif

