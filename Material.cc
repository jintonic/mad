#include "Material.h"

#include <UNIC/Units.h>
using namespace UNIC;

//______________________________________________________________________________
//

void MAD::Material::Print(Option_t *option)
{
   Printf("Material %s A=%g g/mole, Z=%g", GetName(), fA/(gram/mole), fZ);
   Printf(" rho=%g g/cm3, radlen=%g, intlen=%g, index=%i",
         fDensity/(gram/cm3), fRadLen, fIntLen, fIndex);
   for (Int_t i=0; i<fNelements; i++) {
      if (fNatoms) 
         Printf(" Element %i: %s Z=%6.2f, A=%6.2f g/mole, w=%6.3f%%, natoms=%d",
               i, GetElement(i)->GetName(), fZmixture[i],
               fAmixture[i]/(gram/mole), fWeights[i]/perCent, fNatoms[i]);
      else 
         Printf(" Element %i: %s Z=%6.2f, A=%6.2f g/mole, w=%6.3f%%",
               i, GetElement(i)->GetName(), fZmixture[i],
               fAmixture[i]/(gram/mole), fWeights[i]/perCent);
   }
}

//______________________________________________________________________________
//

void MAD::Material::AddElement(TGeoElement *element, Int_t nAtoms)
{
   if (!fElements) fElements = new TObjArray(128);
   if (!fNelements) {
      fZmixture = new Double_t[1];
      fAmixture = new Double_t[1];
      fWeights  = new Double_t[1];
      fNatoms   = new Int_t[1];
   } else {   
      Int_t nelements = fNelements+1;
      Double_t *zmixture = new Double_t[nelements];
      Double_t *amixture = new Double_t[nelements];
      Double_t *weights  = new Double_t[nelements];
      Int_t *nnatoms  = new Int_t[nelements];
      for (Int_t i=0; i<fNelements; i++) {
         zmixture[i] = fZmixture[i];
         amixture[i] = fAmixture[i];
         weights[i]  = fWeights[i];
         nnatoms[i]  = fNatoms[i];
      }
      delete [] fZmixture;
      delete [] fAmixture;
      delete [] fWeights;
      delete [] fNatoms;
      fZmixture = zmixture;
      fAmixture = amixture;
      fWeights  = weights;
      fNatoms   = nnatoms;
   }
   fZmixture[fNelements] = element->Z();
   fAmixture[fNelements] = element->A();
   fNatoms[fNelements]  = nAtoms;
   fElements->AddAtAndExpand(element, fNelements);
   fNelements++;       
   Double_t amol = 0.;
   for (Int_t i=0; i<fNelements; i++) {
      if (fNatoms[i]<=0) return;
      amol += fAmixture[i]*fNatoms[i];
   }   
   for (Int_t i=0; i<fNelements; i++)
      fWeights[i] = fNatoms[i]*fAmixture[i]/amol;
   AverageProperties();
}
