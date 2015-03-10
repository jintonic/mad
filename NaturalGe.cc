#include "NaturalGe.h"
using namespace MAD;
#include "Isotope.h"

#include <TObjArray.h>

//______________________________________________________________________________
//

NaturalGe::NaturalGe(const char *name, const char *title) : Element(name, title)
{
   // Add Ge isotopes
   const Int_t ni = 5;
   Int_t n[ni] = {70, 72, 73, 74, 76}; //Ge-70, Ge-72, Ge-73, Ge-74 and Ge-76
   //Natural abundance for Ge isotopes
   Double_t abundance[ni] = {0.2084, 0.2754, 0.0773, 0.3628, 0.0761}; 
   Isotope *ge[ni];

   for (Int_t i=0; i<ni; i++) {
      ge[i] = new Isotope(32,n[i]);
      ge[i]->SetName(Form("Ge-%d",n[i]));
      AddIsotope(ge[i],abundance[i]);
   }

   // Set fIsotopes to be its own owner, 
   // so that it will delete all its contents when it is deleted
   fIsotopes->SetOwner();
}

//______________________________________________________________________________
//

Double_t NaturalGe::EffectiveMassRatio(const char * type)
{
   if (type=='e') return 0.12;
   else return 0.21;
}
