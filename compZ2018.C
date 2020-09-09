//#include "/afs/cern.ch/user/p/pharris/NYStyle.h"

void xs(TTree* iTree, int id) { 
  TH1F *lH  = new TH1F("A","A",30,0,1200);
  iTree->Draw("(1==1)>>A","xs");
  cout << "xs : " << id << " -- " << lH->Integral()/iTree->GetEntries() << std::endl;
}

void compZ2018() { 
  //Prep();
  gStyle->SetOptStat(0);
  TFile *lHFile = new TFile("kfactors.root");
  TH1F  *lH2     = (TH1F*) lHFile->Get("ZJets_012j_NLO/nominal");
  TH1F  *lHB     = (TH1F*) lHFile->Get("ZJets_LO/inv_pt");
  lH2->SetLineColor(kBlue);
  lH2->SetMarkerColor(kBlue);
  TH1F  *lHD     = (TH1F*) lHFile->Get("EWKcorr/Z");
  TH1F  *forEW   = (TH1F*) lHFile->Get("ZJets_012j_NLO/nominal");
  //lHD->Divide(lH2);  lHD->SetMarkerStyle(kFullCircle);
  //lH2->Divide(lHB); lH2->SetMarkerStyle(kFullCircle);

  TFile *lFile0  = new TFile("/ceph/dschaefer/NLOVjets/zqq_ht400.root");
  TTree *lTree0  = (TTree*) lFile0->Get("Events");
  xs(lTree0,0);

  TFile *lFile1  = new TFile("/ceph/dschaefer/NLOVjets/zqq_ht600.root");
  TTree *lTree1  = (TTree*) lFile1->Get("Events");
  xs(lTree1,1);

  TFile *lFile2  = new TFile("/ceph/dschaefer/NLOVjets/zqq_ht800.root");
  TTree *lTree2  = (TTree*) lFile2->Get("Events");
  xs(lTree2,2);  

  TFile *lFile3  = new TFile("/ceph/dschaefer/NLOVjets/zqq_2016.root");
  TTree *lTree3  = (TTree*) lFile3->Get("Events");
  //xs(lTree2,2);  

  
  const Int_t NBINS=9;
  Double_t edges[NBINS+1] = {200.,250,300,400,500,600,800,1200,1600,3000};
  TH1F *ratio  = new TH1F("kfactor","kfactor",NBINS,edges); 
  TH1F *ew_corr  = (TH1F*) lHD->Clone("ewcorr");
  TH1F *lH  = new TH1F("A","A",NBINS,edges); lH->SetMarkerStyle(kFullCircle); 
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
  lH0 ->SetLineColor(kRed);    lH0 ->SetMarkerColor(kRed);
  lH00->SetLineColor(kRed);    lH00->SetMarkerColor(kRed);
  lH01->SetLineColor(kRed+2);  lH01->SetMarkerColor(kRed+2);
  lH02->SetLineColor(kRed+4);  lH02->SetMarkerColor(kRed+4);
  lH4 ->SetLineColor(kOrange); lH4 ->SetMarkerColor(kOrange);
  //17.72
  //37.77
  //156.5
  TCanvas* c1 = new TCanvas("c1","c1",600,400);
  //c1->SetLogy();
  lTree2->Draw("v_pt>>Hist0","18.67*(v_m > 0)"); lH00->Scale(1./lTree2->GetEntriesFast());
  lTree1->Draw("v_pt>>Hist1","34.0*(v_m > 0)"); lH01->Scale(1./lTree1->GetEntriesFast());
  //lTree1->Draw("v_pt>>Hist1","32.92*(v_m > 0)"); lH01->Scale(1./lTree1->GetEntriesFast());
  lTree0->Draw("v_pt>>Hist2","145.4*(v_m > 0)"); lH02->Scale(1./lTree0->GetEntriesFast());
  lH0->Add(lH00);
  lH0->Add(lH01);
  lH0->Add(lH02);
  lTree3->Draw("v_pt>>Hist4","1187.*(v_m > 0)"); lH4->Scale(1./lTree3->GetEntriesFast());
  //lTree3->Draw("v_pt>>Hist4","1283.*(v_m > 0)"); lH4->Scale(1./lTree3->GetEntriesFast());
  //lTree->Draw("g0_genvpt>>Hist","1187*1000.*(g0_genvm > 70 && g0_genvm < 110)");
  //lH1->Scale(1./lTree->GetEntries());

  //TFile *lZFile = new TFile("/eos/cms/store/cmst3/user/pharris/ajnlo/z12j.root");
  //TFile *lZFile = new TFile("/eos/cms/store/cmst3/user/pharris/ajnlo/z1j.root");
  //TFile *lZFile = new TFile("/tmp/pharris/z12j_shower.root");
  //TFile *lZFile = new TFile("/tmp/pharris/z12j_full_v1.root");
  //TFile *lZFile = new TFile("/tmp/pharris/z1j_full.root");
  TFile *lZFile = new TFile("/ceph/dschaefer/NLOVjets/z12j_v2.root");
  //TFile *lZFile = new TFile("/eos/cms/store/cmst3/user/pharris/ajnlo/unlops.root");
  TH1F *lH3 = (TH1F*) lH->Clone("NLO"); lH3->SetTitle("NLO"); lH3->SetName("NLO"); lH3->SetMarkerColor(kGreen+1); lH3->SetLineColor(kGreen+1); 
  for(int i0 = 0; i0 < lH3->GetNbinsX()+1; i0++) lH3->SetBinContent(i0,0);
  TTree *lZTree  = (TTree*) lZFile->Get("Events");
  //lZTree->Draw("v_pt>>NLO","evtweight*0.6991/0.2*3.*1./(1451.*10000.)*1000.");
  //lZTree->Draw("v_pt>>NLO","xs*1000.*evtweight*3.*0.6991/0.2");
  //lZTree->Draw("v_pt>>NLO","evtweight*3.*0.6991/0.2*(v_m > 70 && v_m < 110)"); //lZTree->Draw("v_pt>>NLO","evtweight*1000.*3.*0.6991/0.2*(v_m > 70 && v_m < 110)");
  lZTree->Draw("v_pt>>NLO","evtweight*0.6991/0.2*3.0*(1./1.73)"); //lZTree->Draw("v_pt>>NLO","evtweight*1000.*3.*0.6991/0.2*(v_m > 70 && v_m < 110)");
  //lZTree->Draw("v_pt>>NLO","evtweight*0.6991/0.2*3./(1083.+1097.)/10000."); //lZTree->Draw("v_pt>>NLO","evtweight*1000.*3.*0.6991/0.2*(v_m > 70 && v_m < 110)");
  //lZTree->Draw("v_pt>>NLO","3.*28.2*0.6991/0.2*evtweight*(v_m > 70 && v_m < 110)"); //lZTree->Draw("v_pt>>NLO","evtweight*1000.*3.*0.6991/0.2*(v_m > 70 && v_m < 110)");
  //lZTree->Draw("v_pt>>NLO","evtweight*1e9*1./1462.*3.*0.6991/0.2*1000.*(v_m > 70 && v_m < 110)");
  //lZTree->Draw("v_pt>>NLO","evtweight*1e9*1./1084.*3.*0.6991/0.2*(v_m > 70 && v_m < 110)");
  lH3->Scale(1./lZTree->GetEntries());
  TH1F *lHC = new TH1F("B","B",1,-200,1200);
  lZTree->Draw("1==1>>B","evtweight*3.*(0.6991/0.2)");
  //lH3->Scale(1./lHC->Integral());
  std::cout << "===> " << lH0->Integral() << " -- " << lH3->Integral() << " -- " << lHC->Integral()/lZTree->GetEntries() << std::endl;

  Int_t N = ratio->GetNbinsX();
  for ( int i=1; i < N+1; i++){
      
      ratio->SetBinContent(i,lH3->GetBinContent(i)/lH0->GetBinContent(i));
      
  }
  Int_t N2 = ew_corr->GetNbinsX();
  for ( int i=1; i < N2+1; i++){
    ew_corr->SetBinContent(i,lHD->GetBinContent(i)/forEW->GetBinContent(i));
    std::cout << "EWcorr/Z " << lHD->GetBinContent(i) << std::endl;
    std::cout << "ZJets_LO/inv_pt "  << forEW->GetBinContent(i) <<std::endl;
  }
  
  
  
  
  ratio->SetLineColor(kRed);
  ratio->SetMarkerColor(kRed); 
  
  
  lH3->GetYaxis()->SetTitle("Ratio/LO");
  lH3->GetXaxis()->SetTitle("Boson p_{T} (GeV)");
  //lH3->GetYaxis()->SetRangeUser(0.000001,3.0);
  //lH3->Draw();
  //lH0->Draw("sames");
  ratio->Draw();
  ew_corr->Draw("sames");
  //lH2->Draw("sames");
  //lHD->Draw("sames");
  //lH4->Draw("sames");
  
  
  TLegend *lL = new TLegend(0.6,0.7,0.8,0.85); lL->SetFillColor(0); lL->SetBorderSize(0); 
  //lL->AddEntry(lH3,"NLO k-factor");
  //lL->AddEntry(lH0,"LO (stat unc)");
  lL->AddEntry(ratio,"NLO k-factor");
  lL->AddEntry(ew_corr,"EWK Correction");
  //lL->AddEntry(lHD,"EWKcorr/Z");
  //lL->AddEntry(lH00,"LO 0 (stat unc)");
  //lL->AddEntry(lH01,"LO 1 (stat unc)");
  //lL->AddEntry(lH02,"LO 2 (stat unc)");
  //lL->AddEntry(lH2,"Old NLO k-factor");
  //lL->AddEntry(lHD,"EWK Correction");
  lL->Draw();

  c1->SaveAs("kfactor_Zjets.png");
  c1->SaveAs("kfactor_Zjets.pdf");
  TFile *lOFile = new TFile("ZJetsCorr.root","RECREATE");
  //lH3->Write();
  ratio->Write();
  ew_corr->Write();
}
