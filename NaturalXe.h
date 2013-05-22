#ifndef NATURALXE_H
#define NATURALXE_H

#include "Element.h"

namespace MAD { class NaturalXe; }

class MAD::NaturalXe : public Element
{
   public:
      NaturalXe();
      virtual ~NaturalXe();

      ClassDef(NaturalXe,1);
};

#endif
