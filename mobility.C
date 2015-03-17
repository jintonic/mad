#include <iostream>
using namespace std;

#include <UNIC/Units.h>
using namespace UNIC;

#include <TF1.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TGraph.h>

#include "GeCrystal.h"
using namespace MAD;

GeCrystal *ge = new GeCrystal;

double mhn(double *x, double *p)
{
   return ge->Mun("h",100)/cm2*volt*s;
}

double mhi(double *x, double *p)
{
   return ge->Mui("h",x[0]/cm3)/cm2*volt*s;
}

double mht(double *x, double *p)
{
   return ge->Mu("h",100,x[0]/cm3)/cm2*volt*s;
}

double men(double *x, double *p)
{
   return ge->Mun("e",100)/cm2*volt*s;
}

double mei(double *x, double *p)
{
   return ge->Mui("e",x[0]/cm3)/cm2*volt*s;
}

double met(double *x, double *p)
{
   return ge->Mu("e",100,x[0]/cm3)/cm2*volt*s;
}

int main()
{
   TCanvas *can = new TCanvas;
   can->SetLogx();
   can->SetLeftMargin(0.15);
   can->Print("mobility.pdf[");

   TF1 *fht = new TF1("fht",mht,1e9,1e18,0);
   fht->SetLineStyle(kDashed);
   fht->GetXaxis()->SetTitle("charge carrier concentration [1/cm^{3}]");
   fht->GetXaxis()->SetTitleOffset(1.2);
   fht->GetYaxis()->SetTitle("mobility[cm^{2}/(Vs)]");
   fht->GetYaxis()->SetTitleOffset(1.5);
   fht->Draw();

   TF1 *fet = new TF1("fet",met,1e9,1e18,0);
   fet->Draw("same");

   TF1 *fen = new TF1("fen",men,1e9,1e18,0);
   fen->SetLineColor(kBlue);
   fen->Draw("same");

   TF1 *fei = new TF1("fei",mei,1e9,1e18,0);
   fei->SetLineColor(kRed);
   fei->Draw("same");

   TF1 *fhn = new TF1("fhn",mhn,1e9,1e18,0);
   fhn->SetLineStyle(kDashed);
   fhn->SetLineColor(kBlue);
   fhn->Draw("same");

   TF1 *fhi = new TF1("fhi",mhi,1e9,1e18,0);
   fhi->SetLineStyle(kDashed);
   fhi->SetLineColor(kRed);
   fhi->Draw("same");

   can->Print("mobility.pdf");

   can->Clear();
   can->SetLogy();
   cout<<ge->Rho("p",1e18/cm3)<<endl;
   ge->gMuHallp->Draw("ac*");
   ge->gMuHalln->Draw("c*");
   can->Print("mobility.pdf");

   can->Print("mobility.pdf]");

   return 0;
}
