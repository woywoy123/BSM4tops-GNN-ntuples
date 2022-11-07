#!/usr/bin/env python

# Copyright (C) 2002-2017 CERN for the benefit of the ATLAS collaboration
import TopExamples.grid
import MC16_precent

config = TopExamples.grid.Config()



config.gridUsername = "tnommens"
# skip shower check because people updated TDP in 21.2.168 but did not think of updating the HARD-CODED :( showering names in the grid submission script.

camp = "e"
config.code          = 'top-xaod'
config.settingsFile  = "SingleLeptonJet_MC_d.txt"
config.suffix        = 'bsm4t-gnn-mc' + camp
config.mergeType     = 'None' #'None', 'Default' or 'xAOD'
config.otherOptions  = "--nGBPerJob=20" 

config.otherOptions  = "" 

def List(camp):
    names = [
    "tZ_mc16" + camp,
    "ttZnunu_mc16" + camp,
    "ttbarHT1k_mc16" + camp,
    "ZqqZvv_mc16" + camp,
    "Zmumu_mc16" + camp,
    "singletop_mc16" + camp,
    "WH125_mc16" + camp,
    "WqqZll_mc16" + camp,
    "WlvZqq_mc16" + camp,
    "Wtaunu_mc16" + camp,
    "ttZqq_mc16" + camp,
    "tt_mc16" + camp,
    "Wmunu_mc16" + camp,
    "ttW_mc16" + camp,
    "WpqqWmlv_mc16" + camp,
    "ttbarHT1k5_mc16" + camp,
    "ttbarHT6c_mc16" + camp,
    "tttautau_mc16" + camp,
    "tchan_mc16" + camp,
    "Wt_mc16" + camp,
    "tW_mc16" + camp,
    "ttbar_mc16" + camp,
    "ttH125_mc16" + camp,
    "SM4topsNLO_mc16" + camp,
    "Ztautau_mc16" + camp,
    "lllv_mc16" + camp,
    "lvvv_mc16" + camp,
    "WqqZvv_mc16" + camp,
    "llll_mc16" + camp,
    "llvv_mc16" + camp,
    "Wenu_mc16" + camp,
    "ZH125_mc16" + camp,
    "Zee_mc16" + camp,
    "ZqqZll_mc16" + camp,
    "ttmumu_mc16" + camp,
    "WplvWmqq_mc16" + camp,
    "ttee_mc16" + camp
    ]
    return names

#out = List("a")
#out = List("d")
out = List("e")

print(out)


samples = TopExamples.grid.Samples(out)
TopExamples.grid.submit(config, samples)
config.noSubmit = False
