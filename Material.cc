#include "Material.h"
#include "Element.h"

#include <TObjArray.h>

//______________________________________________________________________________
//

MAD::Material::~Material()
{
   if (fNatoms) delete[] fNatoms;
   if (fWeights) delete[] fWeights;
}

//______________________________________________________________________________
//

void MAD::Material::Print(Option_t *option)
{
   if (!fNelements) {
      Printf("No element in material %s", GetName());
      return;
   }

   Printf("There are %d elements in material %s :", fNelements, GetName());

   for (UShort_t i=0; i<fNelements; i++) {
      Element *element = (Element*) fElements->At(i);
      Printf("%d: %s weights=%5.2f%%", i,
            element->GetName(), fWeights[i]*100.);
      element->Print(option);
   }
}

//______________________________________________________________________________
//

void MAD::Material::AddElement(Element *element, UShort_t nAtoms)
{
   if (element==0) {
      Warning("AddElement", "Pointer to the element is NULL!");
      Warning("AddElement", "Failed to add element!");
      return;
   }

   if (nAtoms==0) {
      Warning("AddElement", "The 2nd argument is zero!");
      Warning("AddElement", "Failed to add element!");
      return;
   }

   if (fNelements==0) {
      fElements = new TObjArray(10);
      fNatoms   = new UShort_t[100];
      fWeights  = new Double_t[100];
      for (UShort_t i=0; i<100; i++) fNatoms[i]=0;
      for (UShort_t i=0; i<100; i++) fWeights[i]=0;
   }

   fElements->Add(element);
   fNatoms[fNelements]=nAtoms;
   fNelements++;

   Double_t totalWeight = 0.;
   for (UShort_t i=0; i<fNelements; i++) {
      Element *element = (Element*) fElements->At(i);
      Double_t a = element->A();
      if (a<=0) {
         Warning("AddElement", "Atomic mass of element <=0!");
         Warning("AddElement", "Failed to calculate weight percentage!");
         return;
      }
      totalWeight += element->A()*fNatoms[i];
   }
   for (UShort_t i=0; i<fNelements; i++) {
      Element *element = (Element*) fElements->At(i);
      fWeights[i] = element->A()*fNatoms[i]/totalWeight;
   }
}

//______________________________________________________________________________
//

MAD::Element* MAD::Material::GetElement(UShort_t i)
{
   if (i<fNelements) return ((Element*) fElements->At(i));
   return 0;
}
