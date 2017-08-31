#include <TObjArray.h>
#include <TGraph.h>

#include "Material.h"
#include "Element.h"
using namespace MAD;

//______________________________________________________________________________
//

Material::~Material()
{
   if (fNatoms) delete[] fNatoms;
   if (fWeights) delete[] fWeights;
   if (fElements) delete[] fElements;
   if (fSp) delete fSp;
}

//______________________________________________________________________________
//

void Material::Print(Option_t *option)
{
   if (!fNelements) {
      Printf("No element in material %s", GetName());
      return;
   }

   Printf("There are %d elements in material %s :", fNelements, GetName());

   for (unsigned short i=0; i<fNelements; i++) {
      Element *element = (Element*) fElements->At(i);
      Printf("%d: %s weights=%5.2f%%", i,
            element->GetName(), fWeights[i]*100.);
      element->Print(option);
   }
}

//______________________________________________________________________________
//

void Material::AddElement(Element *element, unsigned short nAtoms)
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
      fNatoms   = new unsigned short[100];
      fWeights  = new double[100];
      for (unsigned short i=0; i<100; i++) fNatoms[i]=0;
      for (unsigned short i=0; i<100; i++) fWeights[i]=0;
   }

   fElements->Add(element);
   fNatoms[fNelements]=nAtoms;
   fNelements++;

   double totalWeight = 0.;
   for (unsigned short i=0; i<fNelements; i++) {
      Element *element = (Element*) fElements->At(i);
      double a = element->A();
      if (a<=0) {
         Warning("AddElement", "Atomic mass of element <=0!");
         Warning("AddElement", "Failed to calculate weight percentage!");
         return;
      }
      totalWeight += element->A()*fNatoms[i];
   }
   for (unsigned short i=0; i<fNelements; i++) {
      Element *element = (Element*) fElements->At(i);
      fWeights[i] = element->A()*fNatoms[i]/totalWeight;
   }
}

//______________________________________________________________________________
//

Element* Material::GetElement(unsigned short i)
{
   if (i<fNelements) return ((Element*) fElements->At(i));
   return 0;
}

//______________________________________________________________________________
//

double Material::Qn(double *x, double *par)
{
   double k = par[0];
   double Enr = x[0];
   double z = 0;
   for (unsigned short i=0; i<fNelements; i++) {
      Element *element = (Element*) fElements->At(i);
      z = element->Z();
   }
   z/=fNelements; // averaged z
   double eps = 11.5*Enr*pow(z,-7./3);
   double g = 3*pow(eps,0.15) + 0.7*pow(eps,0.6) + eps;
   return k*g/(1+k*g);
}

//______________________________________________________________________________
//

double Material::Qn(double Enr)
{
   double averageZ = 0, averageA = 0;
   for (unsigned short i=0; i<fNelements; i++) {
      Element *element = (Element*) fElements->At(i);
      averageZ = element->Z();
      averageA = element->A();
   }
   averageZ/=fNelements, averageA/=fNelements;

   double k = 0.133 * pow(averageZ, 2./3.) * pow(averageA, -0.5);

   return Qn(&Enr, &k);
}

//______________________________________________________________________________
//

double Material::Qs(double Enr)
{
   return 0;
}

//______________________________________________________________________________
//

double Material::Se()
{
   return 0;
}

//______________________________________________________________________________
//

TGraph* Material::Sp()
{
   if (fSp) return fSp;
   return 0;
}
