#include "Na.h"
#include "Isotope.h"

#include <TObjArray.h>

#include <UNIC/Units.h>
using namespace UNIC;

MAD::Na::Na(const char *name, const char *title)
  : Element(name, title)
{
  const Int_t ni=3;
  Int_t n[ni]={22,23,24};
  Double_t a[ni]={21.994434*gram/mole,22.989768*gram/mole,23.990961*gram/mole};
  Double_t m[ni]={20.4822*GeV,21.4094*GeV,22.3420*GeV};
  Double_t r[ni]={2.9852*fermi,2.9936*fermi,2.9735*fermi};
  Double_t abundance[ni]={0,1,0};
  Isotope *Na[ni];
  for (int i=0;i<ni;i++)
  {
    Na[i]=new iostope(11,n[i]);
    Na[i]->SetA(a[i]);
    Na[i]->SetM(m[i]);
    Na[i]->SetR(r[i]);
    Na[i]->SetName(Form("Na-%d",n[i]));

    AddIsotope(Na[i],abundance[i]);
  }
  fIsotopes->SetOwner();
}
