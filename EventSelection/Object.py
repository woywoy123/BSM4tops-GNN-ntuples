class Electron(object):
	def __init__(self):
		self.CollectionName = "Electrons"
		self.ID = "TightLH"
		self.IDLoose = "MediumLH"
		self.Isolation = "FCTight"
		self.IsolationLoose = None
		#self.UseChargeIDSelection = False
		self.Pt = 28000
		self.Triggers = ["2015@e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose", 
				 "2016@e26_lhtight_nod0_ivarloose_OR_e60_lhmedium_nod0_OR_e140_lhloose_nod0", 
				 "2017@e26_lhtight_nod0_ivarloose_OR_e60_lhmedium_nod0_OR_e140_lhloose_nod0", 
				 "2018@e26_lhtight_nod0_ivarloose_OR_e60_lhmedium_nod0_OR_e140_lhloose_nod0"]
		self.TriggersLoose = ["2015@e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose", 
				      "2016@e26_lhtight_nod0_ivarloose_OR_e60_lhmedium_nod0_OR_e140_lhloose_nod0", 
				      "2017@e26_lhtight_nod0_ivarloose_OR_e60_lhmedium_nod0_OR_e140_lhloose_nod0", 
				      "2018@e26_lhtight_nod0_ivarloose_OR_e60_lhmedium_nod0_OR_e140_lhloose_nod0"]

class Muon(object):
	def __init__(self):
		self.CollectionName = "Muons"
		self.Quality = "Medium"
		self.QualityLoose = "Medium"
		self.Isolation = "FCTightTrackOnly"
		self.IsolationLoose = None
		self.Pt = 28000
		self.Triggers = ["2015@mu20_iloose_L1MU15_OR_mu50", 
				 "2016@mu26_ivarmedium_OR_mu50", 
				 "2017@mu26_ivarmedium_OR_mu50", 
				 "2018@mu26_ivarmedium_OR_mu50"]

		self.TriggersLoose = ["2015@mu20_iloose_L1MU15_OR_mu50", 
				      "2016@mu26_ivarmedium_OR_mu50", 
				      "2017@mu26_ivarmedium_OR_mu50", 
				      "2018@mu26_ivarmedium_OR_mu50"]

class Tau(object):
	def __init__(self):
		self.CollectionName = None

class Photon(object):
	def __init__(self):
		self.CollectionName = None

class MET(object):
	def __init__(self):
		self.CollectionName = "MET_Reference_AntiKt4EMPFlow"

class LooseMET(object):
	def __init__(self):
		self.CollectionName = "MET_Reference_AntiKt4EMPFlow"

class LargeJet(object):
	def __init__(self):
		self.CollectionName = None
		self.Substructure = None

class Jet(object):
	def __init__(self):
		self.CollectionName = "AntiKt4EMPFlowJets_BTagging201903"
		self.Pt = 28000
		self.DL1Algo = "FixedCutBEff"
		self.DL1rAlgo = "FixedCutBEff"
		self.DL1_wp = [77, 70, 60, 85]
		self.DL1r_wp = [77, 70, 60, 85]
		self.BTagCDIPath = "xAODBTaggingEfficiency/13TeV/2020-21-13TeV-MC16-CDI-2021-04-16_v1.root"
		self.BTaggingWP = None
	
	def __Compile__(self):
		self.BTaggingWP = []
		for i,j in zip(self.DL1_wp, self.DL1r_wp):
			self.BTaggingWP.append("DL1:" + self.DL1Algo + "_" + str(int(i)))
			self.BTaggingWP.append("DL1r:" + self.DL1rAlgo + "_" + str(int(j)))			
class Truth(object):
	def __init__(self):
		self.CollectionName = "TruthParticles"
		self.JetCollectionName = "AntiKt4TruthWZJets"
		self.TopPartonHistory = -1
		self.BlockInfo = -1
		self.PDFInfo = -1
		self.TopParticleLevel = -1
		self.MCGeneratorWeights = -1


class MCa(object):
	def __init__(self):
		self.ConfigFiles_FS = "dev/AnalysisTop/PileupReweighting/user.iconnell.Top.PRW.MC16a.FS.v2/prw.merged.root"
		self.ConfigFiles_AF = "dev/AnalysisTop/PileupReweighting/user.iconnell.Top.PRW.MC16a.AF.v2/prw.merged.root"
		self.LumiCalcFiles = ["GoodRunsLists/data15_13TeV/20170619/PHYS_StandardGRL_All_Good_25ns_276262-284484_OflLumi-13TeV-008.root", 
				      "GoodRunsLists/data16_13TeV/20180129/PHYS_StandardGRL_All_Good_25ns_297730-311481_OflLumi-13TeV-009.root"]
class MCd(object):
	def __init__(self):
		self.ConfigFiles_FS = "dev/AnalysisTop/PileupReweighting/user.iconnell.Top.PRW.MC16d.FS.v2/prw.merged.root"
		self.ConfigFiles_AF = "dev/AnalysisTop/PileupReweighting/user.iconnell.Top.PRW.MC16d.AF.v2/prw.merged.root"
		self.LumiCalcFiles  = "GoodRunsLists/data17_13TeV/20180619/physics_25ns_Triggerno17e33prim.actualMu.OflLumi-13TeV-010.root"
		self.ActualMu_FS    = "GoodRunsLists/data17_13TeV/20180619/physics_25ns_Triggerno17e33prim.actualMu.OflLumi-13TeV-010.root"
		self.ActualMu_AF    = ["GoodRunsLists/data17_13TeV/20180619/physics_25ns_Triggerno17e33prim.lumicalc.OflLumi-13TeV-010.root"]
class MCe(object):
	def __init__(self):
		self.ConfigFiles_FS = "dev/AnalysisTop/PileupReweighting/user.iconnell.Top.PRW.MC16e.FS.v2/prw.merged.root"
		self.ConfigFiles_AF = "dev/AnalysisTop/PileupReweighting/user.iconnell.Top.PRW.MC16e.AF.v2/prw.merged.root"
		self.LumiCalcFiles  = "GoodRunsLists/data18_13TeV/20190318/physics_25ns_Triggerno17e33prim.actualMu.OflLumi-13TeV-010.root"
		self.ActualMu_FS    = "GoodRunsLists/data18_13TeV/20190318/physics_25ns_Triggerno17e33prim.actualMu.OflLumi-13TeV-010.root"
		self.ActualMu_AF    = ["GoodRunsLists/data18_13TeV/20190318/ilumicalc_histograms_None_348885-364292_OflLumi-13TeV-010.root"]

class GoodRunList(object):
	def __init__(self):
		self.Dir = "GoodRunsLists"
		self.File = ["data15_13TeV/20170619/physics_25ns_21.0.19.xml", 
			     "data16_13TeV/20180129/physics_25ns_21.0.19.xml", 
			     "data17_13TeV/20180619/physics_25ns_Triggerno17e33prim.xml", 
			     "data18_13TeV/20190219/physics_25ns_Triggerno17e33prim.xml"]

class EventSaver(object):
	def __init__(self):
		self.PackageName = "libFourTopsGNNSampleProduction"
		self.Format = "top::CustomEventSaver"
		self.Filename = "output.root"
		self.Events = "SelectedEvents"
		self.FileSetAutoFlushZero = True
		self.TDPPath = -1
	
class ConfigContainer(object):
	def __init__(self):
		self.LibraryNames = ["libTopEventSelectionTools", "libTopEventReconstructionTools"]
		self.ObjectSelectionName = "top::ObjectLoaderStandardCuts"
		self.UseRCJets = True
		self.RCJetPt = 200000.0
		self.UseRCJetSubstructure = False
		self.OverlapRemovalProcedure = "BoostedSlidingDRMu"
		self.OverlapRemovalLeptonDef = "Tight"
		self.DoLoose = False
		self.DoTight = "Both"
		self.ApplyTightSFsInLooseTree = True
		self.Systematics = "nominal"
		self.UseAodMetaData = True
		self.UseGlobalLeptonTriggerSF = True
		self.nEvents = -1
		self.Default_Objects = [Electron(), Muon(), Tau(), Photon(), LargeJet(), Jet()]
		self.Default_Truth = Truth()
		self.Default_Campaign = [MCa(), MCd(), MCe()]
		self.Default_Lists = GoodRunList()
		self.Default_Event = EventSaver()	
		self.Selection = None
		self.Filename = "debug.txt"
		self.__Collector = []
	
	def Compile(self):
		if self.Filename.endswith(".txt"):
			pass
		else:
			self.Filename += ".txt"


		self.MakeHeader("SELECTION CONFIGURATION")
		self.__All = []
		self.__All += self.Default_Objects
		self.__All += self.Default_Campaign 
		self.__All += [self.Default_Lists]
		self.__All += [self.Default_Event]

		self.__Dic = {}
		for i in self.__All:
			self.__Dic[type(i).__name__] = i

		self.MakeHeader("PACKAGE LIBRARIES")
	
		Event = self.__Dic["EventSaver"]	
		pkg = self.LibraryNames
		pkg += [Event.PackageName]
		self._d("LibraryNames " +" ".join(pkg))	
		
		if self.nEvents != -1:
			self.MakeHeader("NUMBER OF EVENTS")
			self.Add(self, "nEvents")
		 
		self.MakeHeader("OBJECT DEFINITION")
		self.Add(self, "ObjectSelectionName")
		self._d("# -- Collections")
		self.Add(self.Default_Objects, "CollectionName", True)	
		self._d("\n# -- Structure")
		self.Add(self.Default_Objects, "Substructure", True)
		self.Add(self, "UseRCJetSubstructure")
		self._d("\n# -- RC Jets")	
		for i in ["UseRCJets", "RCJetPt", "OverlapRemovalProcedure", "OverlapRemovalLeptonDef"]:
			self.Add(self, i)
		
		self.MakeHeader("TRUTH COLLECTIONS AND SETTINGS")
		t = ["CollectionName", "JetCollectionName", "TopPartonHistory", "BlockInfo", "PDFInfo", "TopParticleLevel", "MCGeneratorWeights"]
		tp = [True, True, False, True, False, False, False]
		for i, j in zip(t, tp):
			self.Add(self.Default_Truth, i, j)

		self.MakeHeader("OBJECT LOADER AND OBJECT SELECTIONS")
		ELMU = [self.__Dic["Electron"], self.__Dic["Muon"]]
		t = ["ID", "IDLoose", "Quality", "QualityLoose"]
		for i in t:
			self.Add(ELMU, i, True)
		self._d("")
		t = ["Isolation", "IsolationLoose", "UseChargeIDSelection"]
		for i in t:
			self.Add(ELMU, i, True)
		self._d("\n# -- PT")
		ELMU += [self.__Dic["Jet"]]
		self.Add(ELMU, "Pt", True)	
		
		self._d("\n# -- bTagging")
		self.__Dic["Jet"].__Compile__()		
		self.Add(ELMU, "BTaggingWP")		
		
		self._d("")
		t = ["DoLoose", "DoTight", "ApplyTightSFsInLooseTree"]
		for i in t:
			self.Add(self, i)

		self.MakeHeader("CDI File Settings")
		self.Add(self.__Dic["Jet"], "BTagCDIPath")

		self.MakeHeader("EXPERIMENTAL")
		self.Add(self, "Systematics")
		
		self.MakeHeader("EVENT SAVER")
		t = ["Format", "Filename", "Events", "FileSetAutoFlushZero"]
		for i in t:
			self.Add(self.Default_Event, i, False, "Output")
		
		self.MakeHeader("PILEUP CONFIG")
		t = ["Config", "ConfigFiles_FS", "ConfigFiles_AF", "LumiCalcFiles", "ActualMu_FS", "ActualMu_AF"]
		for i in self.Default_Campaign:
			self._d("# -- " + type(i).__name__)
			for p in t:
				self.Add(i, p, False, "PRW")
		
		self.MakeHeader("GOOD RUN LIST")
		for i in ["Dir", "File"]:
			self.Add(self.Default_Lists, i, False, "GRL")
		
		self.MakeHeader("Meta-data")
		self.Add(self, "UseAodMetaData")

		self.MakeHeader("SELECTIONS")		
		self.MakeHeader("global trigger definition", True)	
		self.Add(self, "UseGlobalLeptonTriggerSF")
		self._d("")
		for i in ["Triggers", "TriggersLoose"]:
			self.Add(ELMU, i, True)


		if self.Selection == None:
			print("NO SELECTION!")
			exit()
		
		UniqueBlocks = {}
		Chain = {}
		for i in self.Selection:
			i.TYPE = "SELECTION"
			UniqueBlocks.update(i.Compile())
			Chain.update(i.Chain())
	
		import time 
		
		def DependChain(inpt, din):
			tmp = {}
			for i in inpt:
				ob = [k for k in list(inpt[i]) if k in din]
				for t in ob:
					din.insert(0, din.pop(din.index(t)))
				tmp.update(inpt[i])
				din = DependChain(inpt[i], din)
			if len(tmp) == 0:
				return din
			return DependChain(tmp, din)
		
		Chain = DependChain(Chain, list(UniqueBlocks))
		for k in Chain:	
			self.MakeHeader(k.split(" ")[-1], True)
			self._d(k)
			for i in UniqueBlocks[k]:
				self._d(i)
		f = open(self.Filename, "w")
		f.write("".join(self.__Collector))
		f.close()
			
	
	def _d(self, inp):
		self.__Collector.append(inp + "\n")	
	
	def Add(self, obj, var, Own = False, Title = None):
		if isinstance(obj, list):
			for i in obj:
				self.Add(i, var, Own)
			return 
		if var not in obj.__dict__:
			return 
		if obj.__dict__[var] == -1:
			return
		string = ""
		if Own == True:
			string += str(type(obj).__name__)
		if Title != None:
			string += Title
		if var != None:
			string += var + " " 
		if isinstance(obj.__dict__[var], list):
			string += " ".join(obj.__dict__[var])
		else:
			string += str(obj.__dict__[var])
		self._d(string)	

	def MakeHeader(self, Text, small = False):
		self._d("")
		self._d("#"*100)
		if small != True:
			self._d("".join(["#", " "*int(98), "#"]))
		self._d("".join(["#", " ", str(Text), " "*int(97-len(Text)), "#"]))
		if small != True:	
			self._d("".join(["#", " "*int(98), "#"]))
		self._d("#"*100)
		self._d("")


	
class SubBlock(object):
	def __init__(self, Title):
		self.Title = Title
		self.Initial = -1
		self.GRL = -1
		self.GoodCalo = -1
		self.PriVTX = -1
		self.RecoLevel = -1
		self.GTrigDec = -1
		self.GTrigMatch = -1

		self.EL_N = -1
		self.EL_N_Tight = -1
		self.MU_N = -1
		self.MU_N_Tight = -1
		
		self.Jet_N = -1
		self.Jet_N_bTag = -1
		self.JetClean = -1
		self.Save = -1	

		self.Imports = []
		self.TYPE = "SUB"
	
	def ImportSub(self, SUB):
		if isinstance(SUB, list):
			self.Imports += SUB
		else:
			self.Imports.append(SUB)		

	def Compile(self):
		def CheckLink(ipt):
			out = []
			v = ipt.__dict__
			for i in v:
				if v[i] == -1:
					continue
				name = i.upper()
				if name in ["TITLE", "IMPORTS", "TYPE"]:
					continue
				if isinstance(v[i], str):
					name += " " + v[i]	
				out.append(name)
			return out
			
		name = self.TYPE + " " + self.Title
		di = {name : []}
		for i in self.Imports:
			impt = ". " + i.Title	
			di[name].append(impt)
			di.update(i.Compile())
		di[name] += CheckLink(self)
		return di	
	
	def Chain(self):
		out = {self.TYPE + " " + self.Title : {}}
		for i in self.Imports:
			dep = i.Chain()
			out[self.TYPE + " " + self.Title].update(dep)
		return out







	




