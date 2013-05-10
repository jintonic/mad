#include "Element.h"
#include "Isotope.h"

//______________________________________________________________________________
//

Double_t Element::Meff() const
{
   if (!fNisotopes) return 0;

   Isotope *isocrt;
   Double_t weight = 0.0;
   Double_t meff = 0.0;
   for (Int_t i=0; i<fNisotopes; i++) {
      isocrt = (Isotope*) fIsotopes->At(i);
      meff += fAbundances[i] * isocrt->M();
      weight += fAbundances[i];
   }
   meff /= weight;
   return meff;
}

//______________________________________________________________________________
//

Double_t Element::Reff() const
{
   if (!fNisotopes) return 0;

   Isotope *isocrt;
   Double_t weight = 0.0;
   Double_t reff = 0.0;
   for (Int_t i=0; i<fNisotopes; i++) {
      isocrt = (Isotope*) fIsotopes->At(i);
      reff += fAbundances[i] * isocrt->R();
      weight += fAbundances[i];
   }
   reff /= weight;
   return reff;
}

//______________________________________________________________________________
//

Double_t Element::F2(Double_t nuclearRecoilEnergy,Double_t nuclearSkinThickness) 
{
   if (!fNisotopes) return 1.0;
   if (nuclearRecoilEnergy==0) return 1.0; // no momentum transfer

   Isotope *isocrt;
   Double_t weight = 0.0;
   Double_t feff = 0.0;
   for (Int_t i=0; i<fNisotopes; i++) {
      isocrt = (Isotope*) fIsotopes->At(i);
      feff += fAbundances[i] * 
         isocrt->F2(nuclearRecoilEnergy,nuclearSkinThickness);
      weight += fAbundances[i];
   }
   feff /= weight;

   return feff;
}

//______________________________________________________________________________
//

Double_t Element::CNNSdXS(Double_t nuclearRecoilEnergy, Double_t neutrinoEnergy) 
{
   if (!fNisotopes) return 0.0;

   Isotope *isocrt;
   Double_t weight = 0.0;
   Double_t xseff = 0.0;
   for (Int_t i=0; i<fNisotopes; i++) {
      isocrt = (Isotope*) fIsotopes->At(i);
      xseff += fAbundances[i] * 
         isocrt->CNNSdXS(nuclearRecoilEnergy,neutrinoEnergy);
      weight += fAbundances[i];
   }
   xseff /= weight;

   return xseff;
}
