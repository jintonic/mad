#ifndef MATERIAL_H
#define MATERIAL_H

#include <TGeoMaterial.h>

namespace MAD { class Material; }

class MAD::Material : public TGeoMixture
{
   public:
      Material() : TGeoMixture() {};
      virtual ~Material() {};

      virtual void AddElement(TGeoElement *element, Int_t nAtoms);

      virtual void Print(Option_t *option="");

      ClassDef(Material,1);
};

#endif
