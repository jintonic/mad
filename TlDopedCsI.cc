#include "TlDopedCsI.h"
#include <TGraphErrors.h>
#include <TAxis.h>

MAD::TlDopedCsI::~TlDopedCsI() { if (fQFvsEnr) delete fQFvsEnr; }
      
TGraphErrors* MAD::TlDopedCsI::QFvsEnr()
{
   if (fQFvsEnr) return fQFvsEnr;

   const Int_t n = 32;
   Double_t x[n] = {22, 31, 38, 48, 71, 98, 127, 26, 42, 65, 91, 124, 190, 196,
      281, 323, 409, 446, 503, 94, 94, 183, 183, 314, 314, 402, 402, 511, 512,
      170, 248, 652};
   Double_t y[n] = {173, 212, 224, 229, 245, 237, 238, 245, 265, 310, 336, 341,
      366, 367, 358, 357, 346, 324, 343, 332, 391, 248, 283, 249, 216, 255,
      281, 246, 280, 291, 228, 275};
   Double_t dx[n] ={6, 6, 6, 6, 10, 11, 14, 7, 7, 7, 7, 10, 13, 11, 14, 19, 24,
      26, 33, 6, 6, 26, 28, 12, 11, 12, 13, 14, 14, 17, 24, 30};
   Double_t dy[n] ={65, 45, 45, 39, 36, 34, 34, 28, 26, 25, 25, 24, 25, 25, 21,
      21, 21, 21, 21, 47, 62, 15, 25, 32, 38, 15, 17, 28, 39, 73, 48, 50};
   for (Int_t i=0; i<n; i++) {
      x[i] = x[i]/696.*90.;
      y[i] = y[i]/465.*0.14;
      dx[i]=dx[i]/696.*90.;
      dy[i]=dy[i]/465.*0.14;
   }

   fQFvsEnr = new TGraphErrors(n,x,y,dx,dy);
   fQFvsEnr->SetTitle("Nuclear quenching of CsI(Tl), DOI:10.1126/science.aao0990");
   fQFvsEnr->GetXaxis()->SetTitle("Nuclear recoil energy [keV]");
   fQFvsEnr->GetYaxis()->SetTitle("Quenching factor");
   fQFvsEnr->GetYaxis()->SetRangeUser(0,0.15);
   fQFvsEnr->GetYaxis()->SetTitleOffset(1.2);

   return fQFvsEnr;
}
