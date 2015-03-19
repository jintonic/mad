#include <iostream>
using namespace std;

#include <UNIC/Units.h>
using namespace UNIC;

#include <TF1.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TLegend.h>

#include "GeCrystal.h"
using namespace MAD;

GeCrystal *ge = new GeCrystal;

double mh(double *x, double *p)
{ return ge->Mu('h',100)/(cm2/(volt*s)); }

double mhBH(double *x, double *p)
{ return ge->MuBH('h',x[0]/cm3)/(cm2/(volt*s)); }

double mhHall(double *x, double *p)
{ return ge->MuHall('h',x[0]/cm3)/(cm2/(volt*s)); }

double me(double *x, double *p)
{ return ge->Mu('e',100)/cm2*volt*s; }

double meBH(double *x, double *p)
{ return ge->MuBH('e',x[0]/cm3)/cm2*volt*s; }

double meHall(double *x, double *p)
{ return ge->MuHall('e',x[0]/cm3)/cm2*volt*s; }

int main()
{
   TCanvas *can = new TCanvas;
   can->SetLogx();
   can->SetLogy();
   can->SetLeftMargin(0.15);
   can->Print("mobility.pdf[");

   TF1 *fh = new TF1("fh",mh,1e9,1e21,0);
   fh->GetXaxis()->SetTitle("charge carrier concentration [1/cm^{3}]");
   fh->GetXaxis()->SetTitleOffset(1.2);
   fh->GetYaxis()->SetTitle("mobility[cm^{2}/(Vs)]");
   fh->GetYaxis()->SetTitleOffset(1.5);
   fh->GetYaxis()->SetRangeUser(1,1e6);
   fh->Draw();

   TF1 *fhh = new TF1("fhh",mhHall,4e18,8e20,0);
   fhh->SetLineStyle(kDashed);
   fhh->Draw("same");

   TF1 *fhb = new TF1("fhb",mhBH,1e14,1e18,0);
   fhb->SetLineStyle(kDotted);
   fhb->Draw("same");

   can->Print("mobility.pdf");
   can->Clear();

   TF1 *fe = new TF1("fe",me,1e9,1e21,0);
   fe->GetXaxis()->SetTitle("charge carrier concentration [1/cm^{3}]");
   fe->GetXaxis()->SetTitleOffset(1.2);
   fe->GetYaxis()->SetTitle("mobility[cm^{2}/(Vs)]");
   fe->GetYaxis()->SetTitleOffset(1.5);
   fe->GetYaxis()->SetRangeUser(1,1e6);
   fe->Draw();

   TF1 *feh = new TF1("feh",meHall,4e18,8e20,0);
   feh->SetLineStyle(kDashed);
   cout<<ge->Rho('n',8e20/cm3)/ohm/cm<<", "<<ge->MuHall('e',8e20/cm3)/cm3*volt*s<<endl;
   feh->Draw("same");

   TF1 *feb = new TF1("feb",meBH,1e14,1e18,0);
   feb->SetLineStyle(kDotted);
   feb->Draw("same");
   can->Print("mobility.pdf");

   //cout<<ge->Rho("p",1e18/cm3)<<endl;
   //ge->gRhop->Draw("ac*");
   //ge->gRhon->Draw("c*");

   //TLegend *leg = new TLegend(0.4,0.65,0.8,0.88);
   ////leg->SetFillColor(0);
   ////leg->SetBorderSize(0);
   //leg->AddEntry(ge->gRhop,"p-type","l");
   //leg->AddEntry(ge->gRhon,"n-type","l");
   //leg->Draw();

   //can->Print("mobility.pdf");

   can->Print("mobility.pdf]");

   return 0;
}
