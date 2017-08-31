#ifndef MATERIAL_H
#define MATERIAL_H

#include <TNamed.h>
class TObjArray;
class TGraph;
class TGraphErrors;

namespace MAD {
   class Material; 
   class Element;
}

class MAD::Material : public TNamed
{
   protected:
      unsigned short fNelements; ///< number of elements
      unsigned short *fNatoms; ///< number of atoms in chemical formula 
      double *fWeights; ///< percentages of elements by weight
      TObjArray *fElements; ///< array of elements
      TGraph *fSp; ///< electronic stopping power for proton

   public:
      Material() : TNamed(), fNelements(0), 
      fNatoms(0), fWeights(0), fElements(0), fSp(0) {};
      Material(const char* name, const char* title) : TNamed(name, title), 
      fNelements(0), fNatoms(0), fWeights(0), fElements(0), fSp(0) {};
      virtual ~Material();

      virtual void AddElement(Element *element, unsigned short nAtoms);
      Element* GetElement(unsigned short i=0); // return the i-th element

      unsigned short Nelements() { return fNelements; }

      /**
       * Stopping power (electronic).
       */
      virtual double Se();

      /**
       * Lindhard nuclear quenching.
       */
      virtual double Qn(double Enr);
      virtual double Qn(double *x, double *par); ///< Lindhard nuclear quenching

      /**
       * Scintillation quenching (Berk's Law).
       * Ref. p6, arXiv:0712.2470
       */
      virtual double Qs(double Enr);

      /**
       * Total quenching factor.
       * Q = Qn (nuclear quenching) + Qs (scintillation quenching)
       */
      virtual double Q(double Enr) { return 0; }

      virtual TGraphErrors* Q() { return 0; } ///< total quenching factor

      /**
       * Electronic stopping power for proton.
       */
      virtual double Sp(double protonEnergy) { return 0; }

      virtual TGraph* Sp(); ///< Electronic stopping power plot for proton

      virtual void Print(Option_t *option="");
      
      ClassDef(Material,1);
};

#endif
