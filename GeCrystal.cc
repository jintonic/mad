#include "GeCrystal.h"
using namespace MAD;

#include <cmath>
using namespace std;

#include <UNIC/Units.h>
#include <UNIC/Constants.h>
using namespace UNIC;

#include <TGraph.h>
#include <TAxis.h>

//______________________________________________________________________________
//

GeCrystal::GeCrystal(const char *name, const char *title) :
   Material(name, title), T(77*kelvin), gRhop(0), gRhon(0) {}; 

//______________________________________________________________________________
//

GeCrystal::~GeCrystal()
{
   if (gRhop) delete gRhop;
   if (gRhon) delete gRhon;
}

//______________________________________________________________________________
//

Double_t GeCrystal::Mun(const char *type, Int_t idx)
{
   // refer to Jing Liu's PhD thesis
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
   // refer to D. Chattopadhyay & H. Queisser, "Electron scattering by ionized
   // impurities in semiconductors" Rev. Mod. Phys., vol. 53, no. 4, pp.
   // 745–768, Oct. 1981. It is only valid up to n ~ 1e18 1/cm3
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

//______________________________________________________________________________
//

Double_t GeCrystal::MuHall(const char *type, Double_t n)
{
   // mu = v/E = (I/A/q/n)/(U/l) = 1/(Aqnl)/R = 1/(Aqn/l)/(rho*l/A) = 1/qn*rho
   Double_t e=abs(electron_charge);
   return 1./e/n/Rho(type,n);
}

//______________________________________________________________________________
//

Double_t GeCrystal::Rho(const char *type, Double_t n)
{
   // The relation between resistivity, rho, and impurity concentration, n, is
   // taken from S. M. Sze and J. C. Irvin, "Resistivity, mobility and impurity
   // levels in GaAs, Ge, and Si at 300 K" Solid. State. Electron., vol. 11,
   // no. 6, pp. 599–602, Jun. 1968. According to C. Hung and J. Gliessman,
   // "Resistivity and Hall Effect of Germanium at Low Temperatures" Phys.
   // Rev., vol. 96, no. 5, pp. 1226–1236, Dec. 1954, when n>4e18/cm3, the
   // resistivity does not change with temperature. The result from measurement
   // at 300K can also be used at 77K.
   const Int_t np=100; // number of data points
   Double_t c[np] = { // impurity concentration
      8e20,
      4e20,
      1e20,
      4e19,
      1e19,
      4e18,
      1e18,
      4e17,
      1e17,
      4e16,
      1e16,
      4e15,
      1e15,
      4e14,
      1e14,
   };
   Double_t rp[np] = { // resistivity for p-type Ge
      1.4e-4,  //8e20
      2.25e-4, //4e20
      5.0e-4,  //1e20
      1.0e-3,  //4e19
      2.1e-3,  //1e19
      4.0e-3,  //4e18 
      1.1e-2,  //1e18
      2.0e-2,  //4e17
      5.6e-2,  //1e17
      1.25e-1, //4e16
      4e-1,    //1e16
      8e-1,    //4e15
      3.5,     //1e15
      8,       //4e14
      30.,     //1e14
   };
   Double_t rn[np] = { // resistivity for n-type Ge
      1.0e-4, //8e20
      1.5e-4, //4e20
      3.5e-4, //1e20
      5.8e-4, //4e19
      1.5e-3, //1e19
      2.5e-3, //4e18
      7.0e-3, //1e18
      1.3e-2, //4e17
      3.5e-2, //1e17
      6.0e-2, //4e16
      2.0e-1, //1e16
      4.3e-1, //4e15
      1.5,    //1e15
      3.75,   //4e14
      20,     //1e14
   };

   gRhop = new TGraph(15,c,rp);
   gRhop->SetTitle("");
   gRhop->SetLineColor(kBlue);
   gRhop->GetXaxis()->SetTitle("impurity concentration [1/cm^{3}]");
   gRhop->GetYaxis()->SetTitle("resistivity [ohm #times cm]");

   gRhon = new TGraph(15,c,rn);
   gRhon->SetTitle("");
   gRhon->SetLineColor(kRed);
   gRhon->GetXaxis()->SetTitle("impurity concentration [1/cm^{3}]");
   gRhon->GetYaxis()->SetTitle("resistivity [ohm #times cm]");

   if (type[0]=='p') return gRhop->Eval(n/cm3)*ohm*cm;
   else return gRhon->Eval(n/cm3)*ohm*cm;
}
