#include "GeCrystal.h"
using namespace MAD;
#include <cmath>
using namespace std;
#include <UNIC/Units.h>
#include <UNIC/Constants.h>
using namespace UNIC;

GeCrystal::GeCrystal(const char *name, const char *title)
: Material(name, title), T(77*kelvin) {}; 
//______________________________________________________________________________
//
Double_t GeCrystal::MuEn(Int_t idx)
{
   return 40000*cm2/(volt*s);
}  
//______________________________________________________________________________
//

Double_t GeCrystal::MuHn(Int_t idx)
{
   return 40000*cm2/(volt*s);
}  

//______________________________________________________________________________
//

Double_t GeCrystal::MuEi(Double_t n)
{
   return 128*sqrt(2*pi)*pow(Epsilon()*epsilon0, 2)*pow(k_Boltzmann*T, 3/2.)
*pow(log(24*EffectiveMassRatio("e")*electron_mass_c2*pow(k_Boltzmann*T, 2)
/(n*pow(electron_charge, 2)*pow(hbar_Planck, 2))), -1)/
(sqrt(EffectiveMassRatio("e")*electron_mass_c2)*n*pow(electron_charge, 3))
*cm2/(volt*s);
}  

//______________________________________________________________________________
//


Double_t GeCrystal::MuHi(Double_t n)
{
   return 128*sqrt(2*pi)*pow(Epsilon()*epsilon0, 2)*pow(k_Boltzmann*T, 3/2.)*
pow(log(24*EffectiveMassRatio("h")*electron_mass_c2*pow(k_Boltzmann*T, 2)/
(n*pow(electron_charge, 2)*pow(hbar_Planck, 2))), -1)/
(sqrt(EffectiveMassRatio("h")*electron_mass_c2)*n*pow(electron_charge, 3))
*cm2/(volt*s);
}  

//______________________________________________________________________________
//

Double_t GeCrystal::MuE(Int_t idx, Double_t n)
{
  return pow(1/MuEn() + 1/MuEi(), -1)*cm2/(volt*s);
}

//______________________________________________________________________________
//

Double_t GeCrystal::MuH(Int_t idx, Double_t n)
{
  return pow(1/MuHn() + 1/MuHi(), -1)*cm2/(volt*s);
}

//______________________________________________________________________________
//

Double_t GeCrystal::Epsilon()
{
   return 16.2; //dielectric constant of Ge
}


//______________________________________________________________________________
//

Double_t GeCrystal::EffectiveMassRatio(const char * type)
{
   if (type[0]=='e') return 0.12;
   else return 0.21;
}
