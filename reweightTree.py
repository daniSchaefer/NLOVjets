#!/usr/bin/env/ python

import ROOT
from array import array
import sys

def getWeight(gen_pt,hist):
      if gen_pt > 3000:
          gen_pt = 2800
      if gen_pt < 200.:
          gen_pt = 205.
      binw=hist.GetXaxis().FindBin(gen_pt)
      reweight= hist.GetBinContent(binw)
      return reweight


def getEWCorr(gen_pt,hist):
      if gen_pt > 1205:
          gen_pt = 1205
      if gen_pt < 160.:
          gen_pt = 165.
      binw=hist.GetXaxis().FindBin(gen_pt)
      reweight= hist.GetBinContent(binw)
      return reweight
  
  
def PrintHisto(hist):
    for b in range(0,hist.GetNbinsX()+1):
        print "bin "+str(hist.GetBinCenter(b))+"  weight "+str(hist.GetBinContent(b))
  

if __name__=="__main__":
    V = sys.argv[1]
    fw = ROOT.TFile("/portal/ekpbms2/home/dschaefer/NLOVjets/"+V+"JetsCorr.root","READ")
    h = fw.Get("kfactor")
    h_ew = fw.Get("ewcorr")
    
    
    
    f = ROOT.TFile("/ceph/dschaefer/VJets2017/"+V+"JetsToQQ_HT800toInf_new.root","UPDATE")
    tree = f.Get("tree;1")
    
    ######## get weights #########
    
    
    kfactor = array( 'f', [ 0. ] )
    branch = tree.Branch("kfactor",kfactor,"kfactor/F")
    
    nevents =0
    weights =0
    for event in tree:
        w = 1.
        w_ew = 1.
        if event.jj_l1_mergedVTruth[0] ==1:
            w = getWeight(event.jj_l1_gen_pt[0],h)
            w_ew = getEWCorr(event.jj_l1_gen_pt[0],h_ew)
        else:
            w = getWeight(event.jj_l2_gen_pt[0],h)
            w_ew =  getEWCorr(event.jj_l2_gen_pt[0],h_ew)
        kfactor[0]=w*w_ew
        branch.Fill()
        #tree.Fill()
        print w*w_ew
        weights+=w*w_ew
        nevents+=1
        #print w
    print "mean weights "
    print weights/float(nevents)
        
    tree.Print()
    
    fw.Close()
    del fw
    f.cd()
    tree.Write()
    #branch.Write()
    f.Close()
    del f
    
    
    
    
    
