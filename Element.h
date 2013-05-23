#ifndef ELEMENT_H
#define ELEMENT_H

#include <TNamed.h>

class TF1;
class TF2;
class TObjArray;

namespace MAD { 
   class Element;
   class Isotope;
}

class MAD::Element : public TNamed
{
   protected:
      UShort_t   fNisotopes;  // number of isotopes
      Double_t  *fAbundances; // array of relative abundances
      TObjArray *fIsotopes;   // list of isotopes

      TF1 *fF2;        // form factor squared in TF1 format
      TF2 *fCNNSdXS2D; // CNNS differencial cross section in TF2 format
      TF1 *fCNNSdXSEr; // CNNS differencial cross section(Er) in TF1 format
      TF1 *fCNNSdXSEv; // CNNS differencial cross section(Ev) in TF1 format

      Double_t CNNSdXS2D(Double_t *x, Double_t *parameters);
      Double_t CNNSdXSEr(Double_t *x, Double_t *parameters);
      Double_t CNNSdXSEv(Double_t *x, Double_t *parameters);
      Double_t FormFactor2(Double_t *x, Double_t *parameters);

   public:
      Element() :
         TNamed(), fNisotopes(0), fAbundances(0), fIsotopes(0),
         fF2(0), fCNNSdXS2D(0), fCNNSdXSEr(0), fCNNSdXSEv(0) {};
      Element(const char* name, const char* title) : 
         TNamed(name, title), fNisotopes(0), fAbundances(0), fIsotopes(0), 
         fF2(0), fCNNSdXS2D(0), fCNNSdXSEr(0), fCNNSdXSEv(0) {};
      virtual ~Element();

      void AddIsotope(Isotope *isotope, Double_t abundance);
      Isotope* GetIsotope(UShort_t i=0) const; // return the i-th isotope

      UShort_t Nisotopes() { return fNisotopes; }
      UShort_t Z() const; // atomic number
      Double_t N() const; // average number of nucleons
      Double_t A() const; // average atomic mass
      Double_t M() const; // average nuclear mass
      Double_t R() const; // average nuclear radius
      Double_t S() const; // nuclear skin thickness

      virtual void Print(Option_t *option="");

      Double_t F2(Double_t Er); // form factor squared
      TF1* FF2(Double_t maxEr=50./*keV*/);

      // CNNS differential cross section
      Double_t CNNSdXS(Double_t Er, Double_t Ev);
      TF2* FCNNSdXS2D(Double_t maxEr=50./*keV*/, Double_t maxEv=100./*MeV*/);
      TF1* FCNNSdXSEr(Double_t Ev=15./*MeV*/, Double_t maxEr=50./*keV*/);
      TF1* FCNNSdXSEv(Double_t Er=10./*keV*/, Double_t maxEv=100./*MeV*/);

      ClassDef(Element,1);
};

#endif
