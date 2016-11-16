#include "Cs.h"
#include "Isotope.h"

#include <TObjArray.h>

#include <UNIC/Units.h>
using namespace UNIC;

MAD::Cs::Cs(const char *name, const char *title)
  : Element(name, title)
{
  const Int_t ni=3;
  Int_t n[ni]={133,135,137};
  Double_t a[ni]={132.905429*gram/mole,134.905885*gram/mole,136.907074*gram/mole};
  Double_t m[ni]={123.7735*GeV,125.6369*GeV,127.5011*GeV};
  Double_t r[ni]={4.8041*fermi,4.8067*fermi,4.8128*fermi};
  Double_t abundance[ni]={1,0,0};
  Isotope *Cs[ni];
  for (int i=0;i<ni;i++)
  {
    Cs[i]=new Isotope(55,n[i]);
    Cs[i]->SetA(a[i]);
    Cs[i]->SetM(m[i]);
    Cs[i]->SetR(r[i]);
    Cs[i]->SetName(Form("Cs-%d",n[i]));

    AddIsotope(Cs[i],abundance[i]);
  }
  fIsotopes->SetOwner();
}
