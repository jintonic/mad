#include "GeCrystal.h"
using namespace MAD;

#include <cmath>
using namespace std;

#include <UNIC/Units.h>
#include <UNIC/Constants.h>
using namespace UNIC;

//______________________________________________________________________________
//

GeCrystal::GeCrystal(const char *name, const char *title) :
   Material(name, title), T(77*kelvin) {}; 

//______________________________________________________________________________
//

Double_t GeCrystal::Mun(const char *type, Int_t idx)
{
   if (type[0]=='e') {
      if (idx==111) return 42420*cm2/(volt*s);
      else if (idx==100) return 40180*cm2/(volt*s);
      else return (42420+40180)/2*cm2/(volt*s);
   } else {
      if (idx==111) return 107270*cm2/(volt*s);
      else if (idx==100) return 66333*cm2/(volt*s);
      else return (107270+66333.)/2*cm2/(volt*s);
   }
}

//______________________________________________________________________________
//

Double_t GeCrystal::Mui(const char *type, Double_t n)
{
   Double_t kT=k_Boltzmann*T;
   Double_t eps=Epsilon()*epsilon0;
   Double_t m=EffectiveMassRatio("e")*electron_mass_c2/c_light/c_light;
   if (type[0]=='h')
      m=EffectiveMassRatio("h")*electron_mass_c2/c_light/c_light;
   Double_t e=abs(electron_charge);
   Double_t up=24.*m*eps*kT*kT;
   Double_t dn=e*hbar_Planck*e*hbar_Planck;
   return 128.*sqrt(2*pi*kT*kT*kT/m)*eps*eps/n/e/e/e/log(up/dn/n);
}

//______________________________________________________________________________
//

Double_t GeCrystal::EffectiveMassRatio(const char * type)
{
   if (type[0]=='e') return 0.12;
   else return 0.21;
}
