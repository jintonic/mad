#ifndef MATERIAL_H
#define MATERIAL_H

#include <TNamed.h>
class TObjArray;

namespace MAD {
   class Material; 
   class Element;
}

class MAD::Material : public TNamed
{
   protected:
      UShort_t   fNelements; // number of elements
      UShort_t  *fNatoms;    // number of atoms in chemical formula 
      Double_t  *fWeights;   // percentages of elements by weight
      TObjArray *fElements;  // array of elements

   public:
      Material() : TNamed(), fNelements(0), 
      fNatoms(0), fWeights(0), fElements(0) {};
      Material(const char* name, const char* title) : TNamed(name, title), 
      fNelements(0), fNatoms(0), fWeights(0), fElements(0) {};
      virtual ~Material();

      virtual void AddElement(Element *element, UShort_t nAtoms);
      Element* GetElement(UShort_t i=0); // return the i-th element

      UShort_t Nelements() { return fNelements; }

      virtual void Print(Option_t *option="");
      
      ClassDef(Material,1);
};

#endif
