#include "I.h"
#include "Isotope.h"

#include <TObjArray.h>

#include <UNIC/Units.h>
using namespace UNIC;

MAD::I::I(const char *name, const char *title)
  : Element(name, title)
{
  const Int_t ni=1;
  Int_t n[ni]={127};
  Double_t a[ni]={126.904473*gram/mole};
  Double_t m[ni]={118.1846*GeV};
  Double_t r[ni]={4.7500*fermi};
  Double_t abundance[ni]={1};
  Isotope *I[ni];
  for (int i=0;i<ni;i++)
  {
    I[i]=new Isotope(53,n[i]);
    I[i]->SetA(a[i]);
    I[i]->SetM(m[i]);
    I[i]->SetR(r[i]);
    I[i]->SetName(Form("I-%d",n[i]));

    AddIsotope(I[i],abundance[i]);
  }
  fIsotopes->SetOwner();
}
