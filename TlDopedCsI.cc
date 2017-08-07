#include "TlDopedCsI.h"

#include <UNIC/Units.h>
using namespace UNIC;

#include <TGraphErrors.h>
#include <TAxis.h>

//______________________________________________________________________________
//

TGraphErrors* MAD::TlDopedCsI::QFvsEnr()
{
   if (fQFvsEnr) return fQFvsEnr;

   const Int_t n = 32;
   Double_t x[n] = {22, 31, 38, 48, 71, 98, 127, 26, 42, 65, 91, 124, 190, 196,
      281, 323, 409, 446, 503, 94, 94, 183, 183, 314, 314, 402, 402, 511, 512,
      170, 248, 652};
   Double_t y[n] = {173, 212, 224, 229, 245, 237, 238, 245, 265, 155, 129, 121,
      99, 98, 107, 108, 119, 141, 143, 133, 74, 217, 182, 249, 223, 210, 184,
      219, 185, 174, 237, 190};
   Double_t dx[n] ={6, 6, 6, 6, 10, 11, 14, 7, 7, 7, 7, 10, 13, 11, 14, 19, 24,
      26, 33, 6, 6, 26, 28, 12, 11, 12, 13, 14, 14, 17, 24, 30};
   Double_t dy[n] ={65, 45, 45, 39, 36, 34, 34, 28, 26, 25, 25, 24, 25, 25, 21,
      21, 21, 21, 21, 47, 62, 15, 25, 32, 38, 15, 17, 28, 39, 73, 48, 50};
   Double_t dx[n], dy[n];
   for (Int_t i=0; i<n; i++) {
      x[i] = x[i]/465.*0.14.;
      y[i] = y[i]/696.*90.;
      dx[i]=dx[i]/465.*0.14.;
      dy[i]=dy[i]/696.*90.;
   }

   fQFvsEnr = new TGraphErrors(n,x,y,dx,dy);
   fQFvsEnr->SetTitle("Nuclear quenching of CsI(Tl), DOI:10.1126/science.aao0990");
   fQFvsEnr->GetXaxis()->SetTitle("Nuclear recoil energy [keV]");
   fQFvsEnr->GetYaxis()->SetTitle("Quenching factor (%)");
   fQFvsEnr->GetYaxis()->SetRangeUser(0,0.2);

   return fQFvsEnr;
}
