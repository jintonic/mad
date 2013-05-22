#include "NaturalXe.h"
#include "Isotope.h"

#include <UNIC/Units.h>
using namespace UNIC;

//______________________________________________________________________________
//

MAD::NaturalXe::NaturalXe(const char *name, const char *title)
: Element(name, title, 7)
{
   // Add xenon isotopes based on the information listed below:
   // * nuclear masses and abundance: 
   //     http://hyperphysics.phy-astr.gsu.edu/hbase/pertab/xe.html
   // * nuclear radius:
   //     doi:10.1006/adnd.1995.1007
   const Int_t ni = 10; // reserve enough space
   Int_t n[ni] = {128, 129, 130, 131, 132, 134, 136};
   Double_t a[ni] = {127.903531*gram/mole, 128.904780*gram/mole,
      129.903509*gram/mole, 130.905072*gram/mole, 131.904144*gram/mole,
      133.905395*gram/mole, 135.907213*gram/mole};
   Double_t m[ni] = {119.1147*GeV, 120.0474*GeV, 120.0777*GeV, 121.9107*GeV,
      122.8413*GeV, 124.7055*GeV, 126.5702*GeV}; 
   Double_t r[ni] = {4.776*fermi, 4.776*fermi, 4.783*fermi, 4.781*fermi,
      4.787*fermi, 4.792*fermi, 4.799*fermi};
   Double_t abundance[ni] = {0.0191, 0.264, 0.041, 0.212, 0.269, 0.104, 0.089}; 
   Isotope *xe[ni];

   for (Int_t i=0; i<fNisotopes; i++) {
      xe[i] = new Isotope(54,n[i]);
      xe[i]->SetA(a[i]);
      xe[i]->SetM(m[i]);
      xe[i]->SetR(r[i]);
      xe[i]->SetName(Form("Xe-%d",n[i]));

      AddIsotope(xe[i],abundance[i]);
   }
}

//______________________________________________________________________________
//

MAD::NaturalXe::~NaturalXe()
{
   // Set fIsotopes to be its own owner, 
   // so that it will delete all its contents when it is deleted
   fIsotopes->SetOwner();
}
