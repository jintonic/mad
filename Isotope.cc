#include "Isotope.h"

#include <UNIC/Constants.h>
using namespace UNIC;

#include <TMath.h>
using namespace TMath;

//______________________________________________________________________________
//

Double_t MAD::Isotope::F2(Double_t nuclearRecoilEnergy) 
{
   if (nuclearRecoilEnergy==0) return 1.0; // no momentum transfer

   Double_t q2 = 2*fM*nuclearRecoilEnergy;
   Double_t q = Sqrt(q2); // MeV
   Double_t r0= Sqrt(fR*fR-5*fS*fS); // mm
   Double_t qr0 = q*r0/hbarc; // convert r0 from mm to natural unit MeV^-1
   Double_t j1= (Sin(qr0)-qr0*Cos(qr0))/(qr0)/(qr0); // Levin & Smith, 1996
   Double_t s2= fS/hbarc * fS/hbarc;
   Double_t f =3.*j1/qr0*Exp(-q2*s2/2.);
   return f*f;
}

//______________________________________________________________________________
//

Double_t MAD::Isotope::CNNSdXS(Double_t nuclearRecoilEnergy, Double_t neutrinoEnergy) 
{
   // incident neutrinos must be energetic enough to cause a nuclear recoil
   Double_t evmin = (nuclearRecoilEnergy+Sqrt(2*fM*nuclearRecoilEnergy))/2;
   if (neutrinoEnergy<=evmin) return 0;

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
