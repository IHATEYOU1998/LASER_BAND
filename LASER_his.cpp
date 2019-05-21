
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <math.h> 

#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TVector3.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TLegendEntry.h"
using namespace std;

// given by Andrew on Friday April 12th 2019; modified after

int main(int argc, char ** argv){

  if( argc != 3){
    
    cerr<<"Wrong number of arguments. Instead try:\n\t"
	<< "src_reader /path/to/input/nucleus/file /path/to/output/file \n";

    return -1;
    
  }
  
//Get D and A trees. Open output file.
  TFile * DataH = new TFile(argv[1]);
  TFile * fo = new TFile(argv[2],"RECREATE");
  
  cerr<<"File has been open from: "<<argv[1]<<"\n";
  
//Make trees and histograms for the nuclei
  TTree * TreeH = (TTree*)DataH->Get("T");
  TH1D * his_ADC_0 = new TH1D("DA00","D.A00 [PD #1]",400.,0.,4000.);
  TH1D * his_ADC_1 = new TH1D("DA01","D.A01 [PD #2]",400.,0.,4000.);
  TH1D * his_ADC_2 = new TH1D("DA02","D.A02 [PD #3]",400.,0.,4000.);
  TH1D * his_ADC_3 = new TH1D("DA03","D.A03 [PMT #1]",400.,0.,4000.);
  TH1D * his_ADC_4 = new TH1D("DA04","D.A04 [PMT #2]",400.,0.,4000.);

  TH1D * his_TDC_1 = new TH1D("DT001","D.T001 [PD #1]",400.,0.,4000.);
  TH1D * his_TDC_2 = new TH1D("DT002","D.T002 [PD #2]",400.,0.,4000.);
  TH1D * his_TDC_3 = new TH1D("DT003","D.T003 [PD #3]",400.,0.,4000.);
  TH1D * his_TDC_4 = new TH1D("DT004","D.T004 [PMT #1]",400.,0.,4000.);
  TH1D * his_TDC_5 = new TH1D("DT005","D.T005 [PMT #2]",400.,0.,4000.);

  cerr<<"Histograms and Trees successfully created\n";

//Define variables needed for histograms
  //double D_A00, D_A01, D_A02, D_A03, D_A04, D_T001, D_T002, D_T003, D_T004, D_T005;
  int D_A00_size, D_A01_size, D_A02_size, D_A03_size, D_A04_size;
  int D_T001_size, D_T002_size, D_T003_size, D_T004_size, D_T005_size;
  
	double D_A00[99] = {0.};
	double D_A01[99] = {0.};
	double D_A02[99] = {0.};
	double D_A03[99] = {0.};
	double D_A04[99] = {0.};
	double D_T001[99] = {0.};
	double D_T002[99] = {0.};
	double D_T003[99] = {0.};
	double D_T004[99] = {0.};
	double D_T005[99] = {0.};

//Set addresses for data (D_A00) as well as size (Ndata_D_A00)
  TreeH->SetBranchAddress("Ndata.D.A00",&D_A00_size);
  TreeH->SetBranchAddress("Ndata.D.A01",&D_A01_size);
  TreeH->SetBranchAddress("Ndata.D.A02",&D_A02_size);
  TreeH->SetBranchAddress("Ndata.D.A03",&D_A03_size);
  TreeH->SetBranchAddress("Ndata.D.A04",&D_A04_size);

  TreeH->SetBranchAddress("Ndata.D.T001",&D_T001_size);
  TreeH->SetBranchAddress("Ndata.D.T002",&D_T002_size);
  TreeH->SetBranchAddress("Ndata.D.T003",&D_T003_size);
  TreeH->SetBranchAddress("Ndata.D.T004",&D_T004_size);
  TreeH->SetBranchAddress("Ndata.D.T005",&D_T005_size);
  
  TreeH->SetBranchAddress("D.A00",&D_A00);
  TreeH->SetBranchAddress("D.A01",&D_A01);
  TreeH->SetBranchAddress("D.A02",&D_A02);
  TreeH->SetBranchAddress("D.A03",&D_A03);
  TreeH->SetBranchAddress("D.A04",&D_A04);

  TreeH->SetBranchAddress("D.T001",&D_T001);
  TreeH->SetBranchAddress("D.T002",&D_T002);
  TreeH->SetBranchAddress("D.T003",&D_T003);
  TreeH->SetBranchAddress("D.T004",&D_T004);
  TreeH->SetBranchAddress("D.T005",&D_T005);
  

  
// PMT #1 
  vector<double> ADC_3_x; // event #
  vector<double> ADC_3_y; // ADC value
// PMT #2
  vector<double> ADC_4_x; // event #
  vector<double> ADC_4_y; // ADC value

  
//Loop to get vector of events (x) and corresponding ADC_PMT Data (y)
  for(int i = 0; i < TreeH->GetEntries(); i = i + 100){
    TreeH->GetEntry(i);
    ADC_3_x.push_back(i);
    ADC_3_y.push_back(D_A03[0]);
    ADC_4_x.push_back(i);
    ADC_4_y.push_back(D_A04[0]);
  }
  TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",900,900);
  // c1->Divide(2,1);
  c1->cd(1);
  TGraphErrors * ADC_3 = new TGraphErrors(ADC_3_x.size(),&ADC_3_x[0],&ADC_3_y[0]);
  ADC_3->SetName("gr");                                      // canvas title
   ADC_3->SetTitle("Right (Furthest to Computer) PMT");      // graph title
   ADC_3->SetLineColor(kRed);                                
   ADC_3->SetLineWidth(2);                                   
   ADC_3->SetMarkerStyle(48);                                // rad style for point
   ADC_3->SetMarkerSize(1.1);                                // point size
   ADC_3->SetMarkerColor(46);                                // cool color points
   ADC_3->GetYaxis()->SetTitle("ADC Integration of Event");  // y-axis title
   ADC_3->GetYaxis()->SetTitleOffset(1.5);                   // y-axis title offset from axis
   ADC_3->GetYaxis()->CenterTitle(true);                     // center on axis
   ADC_3->GetXaxis()->SetTitle("Event");                     // X-axis title
   ADC_3->GetXaxis()->CenterTitle(true);                     // Center on axis
   ADC_3->SetMinimum(0);                                     // y-axis minimum
   ADC_3->SetMaximum(4000);                                  // y-axis maximum
   ADC_3->Draw("AP");                                        // Draw on canvas
   
   /** c1->cd(2);
  TGraphErrors * ADC_4 = new TGraphErrors(ADC_4_x.size(),&ADC_4_x[0],&ADC_4_y[0]);
   ADC_4->SetName("gr");
   ADC_4->SetTitle("Right (Furthest to Computer) PMT");
   ADC_4->SetLineColor(kRed);
   ADC_4->SetLineWidth(2);
   ADC_4->SetMarkerStyle(48);
   ADC_4->SetMarkerSize(1.1);
   ADC_4->SetMarkerColor(38);
   ADC_4->GetYaxis()->SetTitle("ADC Integration of Event");
   ADC_4->GetYaxis()->SetTitleOffset(1.5);
   ADC_4->GetYaxis()->CenterTitle(true);
   ADC_4->GetXaxis()->SetTitle("Event");
   ADC_4->GetXaxis()->CenterTitle(true);
   ADC_4->Draw("AP");**/
  
  c1->Modified(); c1->Update();



  
//Loop over TTree
  for(int i = 0; i < TreeH->GetEntries(); i++){
    TreeH->GetEntry(i);
    //his_ADC_0->Fill(D_A00);
    //his_ADC_1->Fill(D_A01);
    //his_ADC_2->Fill(D_A02);
    //his_ADC_3->Fill(D_A03);
    //his_ADC_4->Fill(D_A04);
    //
    //his_TDC_1->Fill(D_T001);
    //his_TDC_2->Fill(D_T002);
    //his_TDC_3->Fill(D_T003);
    //his_TDC_4->Fill(D_T004);
    //his_TDC_5->Fill(D_T005);

  }
    cerr<<"Finished filling histogram\n";


    DataH->Close();
    his_ADC_0->Write();
    his_ADC_1->Write();
    his_ADC_2->Write();
    his_ADC_3->Write();
    his_ADC_4->Write();

    his_TDC_1->Write();
    his_TDC_2->Write();
    his_TDC_3->Write();
    his_TDC_4->Write();
    his_TDC_5->Write();

    ADC_3->Write();
    //ADC_4->Write();
    c1->Write();

    fo->Close();
  cerr<< argv[3]<<" has been completed. \n\n\n";
  
  return 0;
}
