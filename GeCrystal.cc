#include "GeCrystal.h"
using namespace MAD;

#include <cmath>
//#include <iostream>
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

Double_t GeCrystal::Mu(char type, Double_t n)
{
   if (n<1e10/cm3) n=1e10/cm3;
   if (n>1e21/cm3) n=1e21/cm3;
   if (type=='e')
      return 1/(1/MuN(type)+1/(pow(10, -0.46*log10(n*cm3)+11.51)*cm2/volt/s));  
   else
      return 1/(1/MuN(type)+1/(pow(10, -0.44*log10(n*cm3)+10.98)*cm2/volt/s));
}

//______________________________________________________________________________
//

Double_t GeCrystal::MuN(char type, Int_t idx)
{
   // refer to Jing Liu's PhD thesis
   if (type=='e') {
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

Double_t GeCrystal::MuBH(char type, Double_t n)
{
   Double_t kT=k_Boltzmann*T;
   Double_t eps=Epsilon()*epsilon0;
   Double_t m=EffectiveMassRatio(type)*electron_mass_c2/c_light/c_light;
   Double_t e=abs(electron_charge);
   Double_t up=24.*m*eps*kT*kT;
   Double_t dn=e*hbar_Planck*e*hbar_Planck;
   return 128.*sqrt(2*pi*kT*kT*kT/m)*eps*eps/n/e/e/e/log(up/dn/n);

}

//______________________________________________________________________________
//

Double_t GeCrystal::EffectiveMassRatio(char type)
{
   if (type=='e') return 0.12;
   else return 0.21;
}

//______________________________________________________________________________
//

Double_t GeCrystal::MuHall(char type, Double_t n)
{
   Double_t e=abs(electron_charge);
   if (type=='e') 
      return 1./e/n/Rho('n',n);
   else 
      return 1./e/n/Rho('p',n);
}

//______________________________________________________________________________
//

Double_t GeCrystal::Rho(char type, Double_t n)
{
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
   Double_t rp[np] = { // resistivity for p-type Ge at 300K
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
   Double_t rn[np] = { // resistivity for n-type Ge at 300K
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

   if (type=='p') return gRhop->Eval(n*cm3)*ohm*cm;
   else return gRhon->Eval(n*cm3)*ohm*cm;
}
