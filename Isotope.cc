#include "Isotope.h"

#include <UNIC/Units.h>
#include <UNIC/Constants.h>
using namespace UNIC;

#include <cmath>
using namespace std;

//______________________________________________________________________________
//

MAD::Isotope::Isotope() :
   TNamed(), fZ(0), fN(0), fA(0), fM(0), fR(0), fS(1*UNIC::fermi) {};

//______________________________________________________________________________
//

MAD::Isotope::Isotope(UShort_t z, UShort_t n) :
   TNamed(), fZ(z), fN(n), fA(0), fM(0), fR(0), fS(1*UNIC::fermi) {};

//______________________________________________________________________________
//

void MAD::Isotope::Print(Option_t *option)
{
   Printf("Isotope %s Z=%d, N=%d, A=%.2f g/mole, M=%.2f GeV/c2",
         GetName(), fZ, fN, fA/(gram/mole), fM/GeV);
}

//______________________________________________________________________________
//

Double_t MAD::Isotope::F2(Double_t nuclearRecoilEnergy) 
{
   if (nuclearRecoilEnergy==0) return 1.0; // no momentum transfer

   Double_t q2 = 2*fM*nuclearRecoilEnergy;
   Double_t q = sqrt(q2); // MeV
   Double_t r0= sqrt(fR*fR-5*fS*fS); // mm
   Double_t qr0 = q*r0/hbarc; // convert r0 from mm to natural unit MeV^-1
   Double_t j1= (sin(qr0)-qr0*cos(qr0))/(qr0)/(qr0); // Levin & Smith, 1996
   Double_t s2= fS/hbarc * fS/hbarc;
   Double_t f =3.*j1/qr0*exp(-q2*s2/2.);
   return f*f;
}

//______________________________________________________________________________
//

Double_t MAD::Isotope::CNNSdXS(
      Double_t nuclearRecoilEnergy, Double_t neutrinoEnergy) 
{
   // incident neutrinos must be energetic enough to cause a nuclear recoil
   Double_t minEv = (nuclearRecoilEnergy+sqrt(2*fM*nuclearRecoilEnergy))/2;
   if (neutrinoEnergy<=minEv) return 0;

   Double_t sin2thetaw = 0.231;
   Double_t qw = (fN-fZ) - (1-4*sin2thetaw) * fZ;

   Double_t f2 = F2(nuclearRecoilEnergy);

   return GF*GF*fM/8/pi * (1+
         (1-nuclearRecoilEnergy/neutrinoEnergy)*
         (1-nuclearRecoilEnergy/neutrinoEnergy) -
         fM*nuclearRecoilEnergy/neutrinoEnergy/neutrinoEnergy) *qw*qw*f2;
}

//______________________________________________________________________________
//

