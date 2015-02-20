#include "GeCrystal.h"
using namespace MAD;

#include <UNIC/Units.h>
using namespace UNIC;

//______________________________________________________________________________
//

Double_t GeCrystal::MuE(Int_t idx, Double_t T, Double_t E)
{
   return 42420*cm2/(volt*s); //electron Mobility for <100> Ge crystal at 77K
}

//______________________________________________________________________________
//

Double_t GeCrystal::MuH(Int_t idx, Double_t T, Double_t E)
{
   return 66333*cm2/(volt*s); //hole moblity for <100> Ge crystal at 77K
}

//______________________________________________________________________________
//

Double_t GeCrystal::Epsilon()
{
   return 16.2; //dielectric constant of Ge
}

