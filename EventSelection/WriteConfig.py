from Object import *

def CurrentAnalysisSelection(config):
	Basic = SubBlock("BASIC")
	Basic.Initial = None
	Basic.GRL = None
	Basic.GoodCalo = None
	Basic.PriVTX = None
	Basic.Reco_Level = None
	
	# More than two jets with WP 77 	
	Nbtag_DL1 = SubBlock("Nbtag_DL1")
	Nbtag_DL1.Jet_N_btag = "DL1:FixedCutBEff_77 >= 2"	

	Nbtag_DL1r = SubBlock("Nbtag_DL1r")
	Nbtag_DL1r.Jet_N_btag = "DL1r:FixedCutBEff_77 >= 2"	
		
	# Two or more fat jets
	RCJ = SubBlock("RCJ")
	RCJ.RCJet_N = "200000 >= 2"
	RCJ.RCJetMass_N = "50000 >= 2"

	# ============= Electron Channel 	
	EL = SubBlock("EL")
	EL.ImportSub(Basic)
	EL.GTrigDec = None
	EL.EL_N = "28000 >= 1"

	# At Least one electron and no muon
	el_jet = SubBlock("ejets_basic")
	el_jet.EL_N = "10000 >= 1"
	el_jet.EL_N = "10000 == 1"
	el_jet.MU_N = "10000 == 0"
	el_jet.EL_N = "28000 == 1"
	el_jet.EL_N_TIGHT = "28000 == 1"
	el_jet.GTrigMatch = None
	el_jet.JETCLEAN = "LooseBad"
	el_jet.JET_N = "25000 >= 4"

	BSM_ejets_DL1 = SubBlock("BSM_ejets_DL1")
	BSM_ejets_DL1.ImportSub([EL, el_jet, Nbtag_DL1])

	BSM_ejets_DL1r = SubBlock("BSM_ejets_DL1r")
	BSM_ejets_DL1r.ImportSub([EL, el_jet, Nbtag_DL1r])
	
	# ============= MUON Channel 
	MU = SubBlock("MU")
	MU.ImportSub(Basic)
	MU.GTrigDec = None
	MU.MU_N = "28000 >= 1"

	# At Least one muon and no electron
	mu_jet = SubBlock("mujets_basic")
	mu_jet.MU_N = "10000 >= 0"
	mu_jet.MU_N = "10000 == 0"
	mu_jet.EL_N = "10000 == 0"
	mu_jet.MU_N = "28000 == 1"
	mu_jet.MU_N_TIGHT = "28000 == 1"
	mu_jet.GTrigMatch = None
	mu_jet.JETCLEAN = "LooseBad"
	mu_jet.JET_N = "25000 >= 4"

	BSM_mujets_DL1 = SubBlock("BSM_mujets_DL1")
	BSM_mujets_DL1.ImportSub([MU, mu_jet, Nbtag_DL1])

	BSM_mujets_DL1r = SubBlock("BSM_mujets_DL1r")
	BSM_mujets_DL1r.ImportSub([MU, mu_jet, Nbtag_DL1r])


	# Make it into a selection for the electron channel 
	el_j_dl1 = SubBlock("BSM_eljets_DL1_RCJ")
	el_j_dl1.ImportSub([BSM_ejets_DL1, RCJ])
	el_j_dl1.Save = None

	el_j_dl1r = SubBlock("BSM_ejets_DL1r")
	el_j_dl1r.ImportSub([BSM_ejets_DL1r, RCJ])
	el_j_dl1r.Save = None

	
	# Make it into a selection for the MUON channel 
	mu_j_dl1 = SubBlock("BSM_mujets_DL1_RCJ")
	mu_j_dl1.ImportSub([BSM_mujets_DL1, RCJ])
	mu_j_dl1.Save = None

	mu_j_dl1r = SubBlock("BSM_mujets_DL1r_RCJ")
	mu_j_dl1r.ImportSub([BSM_mujets_DL1r, RCJ])
	mu_j_dl1r.Save = None

	config.Selection = [el_j_dl1, el_j_dl1r,
			    mu_j_dl1, mu_j_dl1r]

def CurrentAnalysis(config):	
	config.Default_Event.PackageName = "libFourTopsGNNSampleProduction"
	config.Default_Event.Format = "top::EventSaver"
	config.UseRCJetSubstructure = -1
	config.RCJetPt = -1
	config.UseRCJets = -1
	config.Default_Truth.TopPartonHistory = False
	config.Default_Truth.BlockInfo = False
	config.Default_Truth.PDFInfo = False
	config.Default_Truth.TopParticleLevel = False
	config.Default_Truth.MCGeneratorWeights = "Nominal"
	CurrentAnalysisSelection(config)	

if __name__ == "__main__":
	for j in ["a", "d", "e"]:	
		for i in [-1, 100]:
			config = ConfigContainer()
			if i == 100:
				config.Filename = "SingleLeptonJet_MC_"+ j + "_Test"
			else:
				config.Filename = "SingleLeptonJet_MC_"+j

			if j == "a":
				config.Default_Campaign = [MCa()]

			if j == "d":
				config.Default_Campaign = [MCd()]

			if j == "e":
				config.Default_Campaign = [MCe()]

			CurrentAnalysis(config)
			config.Compile()	
























