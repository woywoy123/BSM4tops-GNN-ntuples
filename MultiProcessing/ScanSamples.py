import glob
import os 

def Write(x, f):
    p = open(f, "w")
    p.write("\n".join(x))
    p.close()

def ReadDir(f):
    out = []
    for x in glob.glob(f +"/*/*"):
        if x.endswith(".part"):
            continue
        out.append(x)
    return out

def DumpConfig(f, SRCDir, OutDir, config):
    script = [ "#!/bin/bash",
               "export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase",
               "source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh",
               "cd " + SRCDir+ "/source/", 
               "asetup --restore", 
               "cd " + SRCDir + "/build/", 
               "source ./*/setup.sh",
               "cd " + OutDir, 
               "top-xaod " + config + " smpl.txt >> log.txt", 
               'x=$(cat smpl.txt | cut -f1 -d",")', 
               "echo $x"
    ]
    Write(script, f)

out = "Dilepton"
src = "/suphys/tnom6927/bsm4tops-gnn-ntuples/" 
Samples = "/import/wu1/tnom6927/Samples/"
Output = "/import/wu1/tnom6927/" + out  + "/"
				
mc = {}
mc["r9364"] = "/suphys/tnom6927/bsm4tops-gnn-ntuples/EventSelection/" + out + "_MC_a.txt"
mc["r10201"] = "/suphys/tnom6927/bsm4tops-gnn-ntuples/EventSelection/" + out + "_MC_d.txt"
mc["r10724"] = "/suphys/tnom6927/bsm4tops-gnn-ntuples/EventSelection/" + out + "_MC_e.txt"

FinDL = {}
FinProc = {}

for i in ReadDir(Output + "/*"):
    if not i.endswith("output.root"):
        continue
    Write([""], "/".join(i.split("/")[:-1]) + "/FIN.txt")

for i in ReadDir(Samples):
    if not i.endswith(".root.1"):
        continue
    if i.split("/")[-1] in FinProc:
        continue
    FinDL[i.split("/")[-1]] = i.lstrip(".")
    

for i in FinDL:
    print(i)
    SMPL = FinDL[i].split("/")[-2]
    Name = ".".join(i.split(".")[:-3])
    OutDir = Output + SMPL + "/" + Name
    try:
        os.makedirs(OutDir)
    except:
        continue

    x = [k for k in SMPL.split("_") if k in mc]
    if len(x) == 0:
        continue
    Conf = mc[x[0]]
    DumpConfig(OutDir + "/Out.sh", src, OutDir, Conf) 
    Write([FinDL[i] + ","], OutDir + "/smpl.txt")



