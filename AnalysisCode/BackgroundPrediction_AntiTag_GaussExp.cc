#include <TH1F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TProfile.h>
#include <iostream>
#include <TStyle.h>
#include <TPaveText.h>
#include <THStack.h>
#include <TF1.h>
#include <TSystem.h>
#include <TGraphErrors.h>
#include <TF1.h>

int iPeriod = 4;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV 
int iPos = 20;

void BackgroundPrediction_AntiTag_GaussExp(double plot_lo, double plot_hi, double rebin,
                                           double fit_lo, double fit_hi, 
                                           double gaussexp_mean_lo, double gaussexp_mean_hi, 
                                           double gaussexp_width_lo, double gaussexp_width_hi,
                                           double gaussexp_exp_lo, double gaussexp_exp_hi,
                                           std::string hist1="h_mX_SB_kinFit", std::string hist2="h_mX_SR_kinFit", 
                                           std::string log="lin")
{
  gROOT->SetStyle("Plain");
  gROOT->LoadMacro("tdrstyle.C");
  gStyle->SetPadGridX(0);
  gStyle->SetPadGridY(0);
  gStyle->SetOptStat(0000);
  //gROOT->LoadMacro("CMS_lumi.C");
  /*writeExtraText = false;       // if extra text
  extraText  = "Preliminary";  // default extra text is "Preliminary"
  lumi_8TeV  = "17.9 fb^{-1}"; // default is "19.7 fb^{-1}"
  lumi_13TeV  = "2.2 fb^{-1}";  // default is "5.1 fb^{-1}"
 */

  TFile *f_data=new TFile("Histograms_Data_BTagCSV_2015_Skim.root");
  TH1F *h_mX_SB=(TH1F*)f_data->Get(hist1.c_str());
  TH1F *h_mX_SR=(TH1F*)f_data->Get(hist2.c_str());
  h_mX_SB->Rebin(rebin);
  h_mX_SR->Rebin(rebin);
  h_mX_SB->Scale(1./h_mX_SB->GetSumOfWeights());
  h_mX_SR->Scale(1./h_mX_SR->GetSumOfWeights());
  h_mX_SB->GetXaxis()->SetRangeUser(plot_lo, plot_hi);
  h_mX_SR->GetXaxis()->SetRangeUser(plot_lo, plot_hi);
  
  RooRealVar *x;
  x=new RooRealVar("x", "m_{X} (GeV)", plot_lo, plot_hi);
  
  // SB Fit
  RooRealVar bC_p0("bC_p0", "bC_p0", gaussexp_mean_lo, gaussexp_mean_hi);
  RooRealVar bC_p1("bC_p1", "bC_p1", gaussexp_width_lo, gaussexp_width_hi);
  RooRealVar bC_p2("bC_p2", "bC_p2", gaussexp_exp_lo, gaussexp_exp_hi);
  GaussExp bC_fit("bC_fit", "bC Fit", *x, bC_p0, bC_p1, bC_p2);
  RooDataHist bC_data("bC_data", "bC Data", RooArgList(*x), h_mX_SB);
  RooFitResult *r_bC_fit=bC_fit.fitTo(bC_data, RooFit::Range(fit_lo, fit_hi), RooFit::SumW2Error(kTRUE), RooFit::Save());
  RooPlot *bC_plot=x->frame();
  bC_data.plotOn(bC_plot);
  // bC_fit.plotOn(bC_plot, RooFit::VisualizeError(*r_bC_fit), RooFit::FillColor(kGray+1), RooFit::FillStyle(3001));
  bC_fit.plotOn(bC_plot, RooFit::LineColor(kBlack));
  bC_data.plotOn(bC_plot, RooFit::LineColor(kBlack), RooFit::MarkerColor(kBlack));

  // bS
  RooRealVar bS_p0("bS_p0", "bS_p0", gaussexp_mean_lo, gaussexp_mean_hi);
  RooRealVar bS_p1("bS_p1", "bS_p1", gaussexp_width_lo, gaussexp_width_hi);
  RooRealVar bS_p2("bS_p2", "bS_p2", gaussexp_exp_lo, gaussexp_exp_hi);
  GaussExp bS_fit("bS_fit", "bS Fit", *x, bS_p0, bS_p1, bS_p2);
  RooDataHist bS_data("bS_data", "bS Data", RooArgList(*x), h_mX_SR);
  RooFitResult *r_bS_fit=bS_fit.fitTo(bS_data, RooFit::Range(fit_lo, fit_hi), RooFit::SumW2Error(kTRUE), RooFit::Save()); 
  RooPlot *bS_plot=x->frame();
  bS_data.plotOn(bS_plot);
  // bS_fit.plotOn(bS_plot,RooFit::VisualizeError(*r_bS_fit), RooFit::FillColor(kBlue+1), RooFit::FillStyle(3001));
  bS_fit.plotOn(bS_plot, RooFit::LineColor(kBlue+1));
  bS_data.plotOn(bS_plot, RooFit::LineColor(kBlue+1), RooFit::MarkerColor(kBlue+1));

  // Ratio plot
  TH1F *h_ratio=(TH1F*)h_mX_SR->Clone("h_ratio");
  h_ratio->Divide(h_mX_SB);
  h_ratio->SetTitle("; m_{X} (GeV); SR/SB");
  
  TCanvas *c_AntiTag_GaussExp=new TCanvas("c_AntiTag_GaussExp", "c_AntiTag_GaussExp", 700, 700);
  TPad *p_1=new TPad("p_1", "p_1", 0, 0.35, 1, 1);
  TPad *p_2=new TPad("p_2", "p_2", 0, 0, 1, 0.35);
  p_2->SetFillColor(0);
  p_2->SetBorderMode(0);
  p_2->SetBorderSize(2);
  p_2->SetTopMargin(0.018);
  p_2->SetBottomMargin(0.30);
  p_2->SetFrameBorderMode(0);
  p_1->Draw();
  p_2->Draw();
  p_1->cd();
  double max1=h_mX_SR->GetMaximum();
  double max2=h_mX_SB->GetMaximum();
  double maxy=(max1>max2) ? max1 : max2;
  if (log=="log") bC_plot->GetYaxis()->SetRangeUser(1e-4, maxy*1.5);
  else bC_plot->GetYaxis()->SetRangeUser(0, maxy*1.5);
  bC_plot->SetTitle("; m_{X} (GeV); Normalized units");
  bC_plot->Draw();
  bS_plot->Draw("same");
  if (log=="log") p_1->SetLogy();
  
  TPaveText *pave = new TPaveText(0.60, 0.60, 0.89, 0.69, "NDC");
  pave->SetBorderSize(0);
  pave->SetTextSize(0.03);
  pave->SetLineColor(1);
  pave->SetLineStyle(1);
  pave->SetLineWidth(2);
  pave->SetFillColor(0);
  pave->SetFillStyle(0);
  pave->AddText("AntiTag selection");
  char name[100];
  //sprintf(name,"SB #chi^{2}/ndof = %.2f",bC_plot->chiSquare());
  //pave->AddText(name);
  //sprintf(name,"SR #chi^{2}/ndof = %.2f",bS_plot->chiSquare());
  //pave->AddText(name);
  pave->Draw();
  
  TLegend *leg = new TLegend(0.65,0.73,0.89,0.89);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(2);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  h_mX_SB->SetMarkerStyle(20);
  h_mX_SB->SetMarkerColor(kBlack);
  leg->AddEntry(h_mX_SB, "Data shape in SB", "lep");
  h_mX_SR->SetLineColor(kBlue+1);
  h_mX_SR->SetMarkerColor(kBlue+1);  
  h_mX_SR->SetMarkerStyle(20);
  leg->AddEntry(h_mX_SR, "Data shape in SR", "lep");
  leg->Draw();
  
  p_2->cd();
  h_ratio->GetYaxis()->SetRangeUser(0, 2.);
  h_ratio->GetYaxis()->SetLabelSize(0.06);
  h_ratio->GetYaxis()->SetTitleSize(0.05);
  h_ratio->GetXaxis()->SetTitleSize(0.1);
  h_ratio->GetXaxis()->SetTitleOffset(1.0);
  h_ratio->GetXaxis()->SetLabelSize(0.1);
  h_ratio->SetMarkerStyle(20);
  h_ratio->SetLineColor(kBlack);
  h_ratio->Draw();
  TLine *m_one_line = new TLine(plot_lo,1,plot_hi,1);
  m_one_line->Draw("same");
  
  c_AntiTag_GaussExp->SaveAs("c_AntiTag_GaussExp.png");
  c_AntiTag_GaussExp->SaveAs("c_AntiTag_GaussExp.pdf");
  
   
  std::cout<<" === === "<<std::endl;
  std::cout<<"chi^2/ndof of bC = "<<bC_plot->chiSquare()<<std::endl;
  std::cout<<"chi^2/ndof of bS = "<<bS_plot->chiSquare()<<std::endl;
  std::cout<<" === === "<<std::endl;
  
}
  
  
  
