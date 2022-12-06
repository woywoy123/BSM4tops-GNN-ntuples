import ROOT
import glob 
import shutil
import os

mc = {}
mc["a"] = "r9364"
mc["d"] = "r10201"
mc["e"] = "r10724"

for cp in mc:
    keys = {}
    File = ROOT.TFile.Open("user.iconnell.Top.PRW.MC16" + cp + ".AF.v2/prw.merged.root")
    fold = File.Get("PileupReweighting")
    for i in fold.GetListOfKeys():
        keys[str(i).split(" ")[1]] = False
   
    #os.makedirs("Output/user.iconnell.Top.PRW.MC16" + cp + "_BSMH.AF.v2")
    #shutil.copy("user.iconnell.Top.PRW.MC16" + cp + ".AF.v2/prw.merged.root", "Output/user.iconnell.Top.PRW.MC16" + cp + "_BSMH.AF.v2/prw.merged.root")
    
    for i in glob.glob("PileUp/*"):
        if mc[cp] not in i:
            continue 
        for k in glob.glob(i + "/*"):
            F1 = ROOT.TFile.Open(k)
            FL = F1.Get("PileupReweighting")
            print("---> " + k)
            for t in FL.GetListOfKeys():
                t = str(t).split(" ")[1]
                if t.startswith("MCP"):
                    continue
                
                print(keys[t], t)
                if t in keys:
                    continue
                keys[t] = k

                print("-> ", t, keys[t])
                #name = "Output/user.iconnell.Top.PRW.MC16" + cp + "_BSMH.AF.v2/prw.merged"
                #os.system("hadd -f tmp.root" + " " + name + ".root"  + " " + k)
                #shutil.move("tmp.root", name + ".root")
