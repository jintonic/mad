#ifndef NATURALGE_H
#define NATURALGE_H

#include "Element.h"

namespace MAD { class NaturalGe; }

class MAD::NaturalGe : public Element
{
   public:
      NaturalGe(const char *name="NaturalGe", const char *title="Natural Ge");
      virtual ~NaturalGe() {};

      Double EffectiveMassRatio(const char* type="e");

      ClassDef(NaturalGe,1);
};

#endif

