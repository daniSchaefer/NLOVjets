//#include "/afs/cern.ch/user/p/pharris/NYStyle.h"

void xs(TTree* iTree, int id) { 
  TH1F *lH  = new TH1F("A","A",30,0,1200);
  iTree->Draw("(1==1)>>A","xs");
  cout << "xs : " << id << " -- " << lH->Integral()/iTree->GetEntries() << std::endl;
}

void compW2018() { 
  gStyle->SetOptStat(0);  
  TFile *lHFile = new TFile("kfactors.root");
  TH1F  *lH2     = (TH1F*) lHFile->Get("WJets_012j_NLO/nominal");
  TH1F  *lHB     = (TH1F*) lHFile->Get("WJets_LO/inv_pt");
  TH1F  *lHD     = (TH1F*) lHFile->Get("EWKcorr/W");
  TH1F  *forEW   = (TH1F*) lHFile->Get("WJets_012j_NLO/nominal");
  
  
  lHD->SetLineColor(kBlue);
  lHD->SetMarkerColor(kBlue);

  TFile *lFile0  = new TFile("/ceph/dschaefer/NLOVjets/wqq_ht400.root");
  TTree *lTree0  = (TTree*) lFile0->Get("Events");
  //xs(lTree0,0);

  TFile *lFile1  = new TFile("/ceph/dschaefer/NLOVjets/wqq_ht600.root");
  TTree *lTree1  = (TTree*) lFile1->Get("Events");
  //xs(lTree1,1);

  TFile *lFile2  = new TFile("/ceph/dschaefer/NLOVjets/wqq_ht800.root");
  TTree *lTree2  = (TTree*) lFile2->Get("Events");
  //xs(lTree2,2);

  TFile *lFile3  = new TFile("/ceph/dschaefer/NLOVjets/wqq_2016.root");
  TTree *lTree3  = (TTree*) lFile3->Get("Events");
  //xs(lTree2,2);
  
  const Int_t NBINS=9;
  Double_t edges[NBINS+1] = {200.,250,300,400,500,600,800,1200,1600,3000};
  
  TH1F *lH  = new TH1F("A","A",NBINS,edges); lH->SetMarkerStyle(kFullCircle); 
  TH1F *ratio  = new TH1F("kfactor","kfactor",NBINS,edges); 
  TH1F *ew_corr  = (TH1F*) lHD->Clone("ewcorr");
  
  TH1F *lH0  = (TH1F*) lH->Clone("Hist0B");
  TH1F *lH00 = (TH1F*) lH->Clone("Hist0");
  TH1F *lH01 = (TH1F*) lH->Clone("Hist1");
  TH1F *lH02 = (TH1F*) lH->Clone("Hist2");
  TH1F *lH4  = (TH1F*) lH->Clone("Hist4");
  for(int i0 = 0; i0 < lH0 ->GetNbinsX()+1; i0++) lH0 ->SetBinContent(i0,0);
  for(int i0 = 0; i0 < lH00->GetNbinsX()+1; i0++) lH00->SetBinContent(i0,0);
  for(int i0 = 0; i0 < lH01->GetNbinsX()+1; i0++) lH01->SetBinContent(i0,0);
  for(int i0 = 0; i0 < lH02->GetNbinsX()+1; i0++) lH02->SetBinContent(i0,0);
  for(int i0 = 0; i0 < lH4 ->GetNbinsX()+1; i0++) lH4 ->SetBinContent(i0,0);
  lH0 ->SetLineColor(kRed);   lH0 ->SetMarkerColor(kRed);
  lH00->SetLineColor(kRed);   lH00->SetMarkerColor(kRed);
  lH01->SetLineColor(kRed+2); lH01->SetMarkerColor(kRed+2);
  lH02->SetLineColor(kRed+4); lH02->SetMarkerColor(kRed+4);
  lH4 ->SetLineColor(kOrange); lH4 ->SetMarkerColor(kOrange);
  TCanvas* c1 = new TCanvas("c1","c1",600,400);
  //c1->SetLogy();
  lTree2->Draw("v_pt>>Hist0","34.9*(v_m > -40)"); lH00->Scale(1./lTree2->GetEntriesFast());
  lTree1->Draw("v_pt>>Hist1","68.57*(v_m > -40)"); lH01->Scale(1./lTree1->GetEntriesFast());
  lTree0->Draw("v_pt>>Hist2","315.6*(v_m > -40)"); lH02->Scale(1./lTree0->GetEntriesFast());
  lTree3->Draw("v_pt>>Hist4","2788.*(v_m > -40)"); lH4 ->Scale(1./lTree3->GetEntriesFast());

 
  lH0->Add(lH00);
  lH0->Add(lH01);
  lH0->Add(lH02);

  TFile *lZFile = new TFile("Comb_w12j.root");
  TTree *lZTree  = (TTree*) lZFile->Get("Events");
  TH1F *lH3 = (TH1F*) lH->Clone("NLO"); lH3->SetTitle("NLO"); lH3->SetName("NLO"); lH3->SetMarkerColor(kGreen+1); lH3->SetLineColor(kGreen+1);
  for(int i0 = 0; i0 < lH3->GetNbinsX()+1; i0++) lH3->SetBinContent(i0,0);
  //lZTree->Draw("v_pt>>NLO","evtweight*67.6/10.8*1000.*1./(1837*10000.)");
  lH3->Sumw2(); lH3->SetMarkerStyle(kFullCircle);
  lZTree->Draw("v_pt>>NLO","evtweight*67.6/10.8/(10000.*(1094.))");//*(v_m > 60 && v_m < 100)");
  //lZTree->Draw("v_pt>>NLO","evtweight*67.6/10.8*1./1.35*(v_m > 60 && v_m < 100)");
  //lZTree->Draw("v_pt>>NLO","1000.*evtweight*67.6/10.8");
  TH1F *lHC = new TH1F("B","B",1,-200,1200);
  //lZTree->Draw("1==1>>B","evtweight");
  //lH3->Scale(7980./lHC->Integral());
  //lH3->Scale(float(lZTree->GetEntries())/(40000.*3898.));
  //lH3->Scale(1./(40000.*3898.));
  cout << "==> " << lH0->Integral() << " -- " << lH3->Integral() << endl;
  
  // calculate the ratio of nlo/lo i.e. lH3/lH0 
  
  Int_t N = ratio->GetNbinsX();
  for ( int i=1; i < N+1; i++){
      
      ratio->SetBinContent(i,lH3->GetBinContent(i)/lH0->GetBinContent(i));
      
  }
  Int_t N2 = ew_corr->GetNbinsX();
  for ( int i=1; i < N2+1; i++){
    ew_corr->SetBinContent(i,lHD->GetBinContent(i)/forEW->GetBinContent(i));
    std::cout << lHD->GetBinContent(i)/forEW->GetBinContent(i) <<std::endl;
    std::cout << "EWcorr/Z " << lHD->GetBinContent(i) << std::endl;
    std::cout << "ZJets_LO/inv_pt "  << forEW->GetBinContent(i) <<std::endl;
  }
  ratio->SetLineColor(kBlue);
  ratio->SetMarkerColor(kBlue);
 
  lH3->GetYaxis()->SetTitle("Ratio/LO");
  lH3->GetXaxis()->SetTitle("Boson p_{T} (GeV)");
  lH3->GetYaxis()->SetRangeUser(0.000005,200.0);
 
  //lH3->Draw();
  //lH0->Draw("sames");
  //lH2->Draw("sames");
  ratio->SetLineColor(kRed);
  ratio->Draw();
  ew_corr->Draw("sames");
  //lHD->Draw("sames");
  //lH4->Draw("sames");
  TLegend *lL = new TLegend(0.5,0.65,0.8,0.88); lL->SetFillColor(0); lL->SetBorderSize(0); 
  //lL->AddEntry(lH3,"NLO k-factor");
  //lL->AddEntry(lH0,"LO (stat unc");
  lL->AddEntry(ratio,"NLO k-factor");
  lL->AddEntry(ew_corr,"EWK Correction");
  //lL->AddEntry(lH4,"LO 2016");
  lL->Draw();
  c1->SaveAs("kfactor_Wjets.png");
  //lH2->Draw("sames");
  //lH ->Draw("sames");
  TFile *lOFile = new TFile("WJetsCorr.root","RECREATE");
  //lH3->Write();
  ratio->Write();
  ew_corr->Write();
  
}
