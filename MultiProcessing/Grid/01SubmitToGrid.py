#!/usr/bin/env python

# Copyright (C) 2002-2017 CERN for the benefit of the ATLAS collaboration
import TopExamples.grid
import MC16_precent

config = TopExamples.grid.Config()

config.gridUsername = "tnommens"
# skip shower check because people updated TDP in 21.2.168 but did not think of updating the HARD-CODED :( showering names in the grid submission script.

camp = "a"
config.code          = 'top-xaod'
config.settingsFile  = "SingleLeptonJet_MC_" + camp + ".txt"
config.suffix        = 'bsm4t-gnn-mc' + camp
config.mergeType     = 'None' #'None', 'Default' or 'xAOD'
config.otherOptions  = "--nGBPerJob=20" 

config.otherOptions  = "" 

def List(campi):
    names = [
    "ttH_mc16" + campi
    ]
    return names

out = List("a")
#out = List("d")
#out = List("e")

samples = TopExamples.grid.Samples(out)
TopExamples.grid.submit(config, samples)
config.noSubmit = True
