import shutil 
import os
import glob
import json 

def ReadText(f):
    x = open(f, "r")
    c = x.readline()
    x.close()
    return c

def Write(x, f):
    p = open(f, "w")
    p.write("\n".join(x))
    p.close()

def ReadDir(f):
    out = []
    for x in glob.glob(f +"/*"):
        if "mc16_" not in x:
            continue
        out.append(x)
    return out

def DumpConfig(f, SRCDir, OutDir, config, runner = False):
    run="run.txt"
    if runner == True:
        run="runRucio.txt"
    script = [ "#!/bin/bash",
               "export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase",
               "source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh",
               "cd " + SRCDir+ "/source/", 
               "asetup --restore", 
               "cd " + SRCDir + "/build", 
               "source ./*/setup.sh",
               "cd " + OutDir, 
               "top-xaod " + config + " " + run + " >> log.txt", 
               'echo "DONE" > done.txt'
    ]

    if runner == True:
        script.append("rm ./*.pool.root.1")
    Write(script, f)


def DumpRucio(f, SMPL):
    rucio = [
               "#!/bin/bash",
               "cd " + "/".join(f.split("/")[:-1]), 
               "export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase",
               "source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh",
               "export RUCIO_ACCOUNT=tnommens", 
               "lsetup rucio", 
               "rucio get --no-subdir mc16_13TeV:" + SMPL,
            ]
    Write(rucio, f)

r = "/nfs/dust/atlas/user/woywoy12/AnalysisTop/bsm4tops-gnn-ntuples/"
ANA= r + "MultiProcessing/Sorted"
PROC= r + "MultiProcessing/Sorted"
INPT = r
OUPT = INPT + "MultiProcessing/Output/"

mc = {}
mc["r9364"] = INPT + "/EventSelection/SingleLeptonJet_MC_a.txt"
mc["r10201"] = INPT + "/EventSelection/SingleLeptonJet_MC_d.txt"
mc["r10724"] = INPT + "/EventSelection/SingleLeptonJet_MC_e.txt"

op = open("FileNames.json", "r")
F = json.load(op)

smpls = {}
run = {}
mc_run = {}
for i in F:
    for j in F[i]:
        smpls[j] = "/".join(j.split("/")[:-1])
        run[j] = True
        mc_run[j] = mc[[k for k in i.split("_") if k in mc][0]]

for i in run:
    print(i)
    if run[i] == False:
        continue
    o = OUPT + "/" + i.split("/")[-1].replace(".pool.root.1", "")
    try:
        os.mkdir(o)
    except OSError:
        pass
    Write([i + ","], o + "/run.txt")
    DumpConfig(o + "/Out.sh", INPT, o, mc_run[i])
    DumpRucio(o + "/Rucio.sh", i.split("/")[-1]) 
    DumpConfig(o + "/OutRucio.sh", INPT, o, mc_run[i], True)
    Write(["./" + i.split("/")[-1] + ","], o + "/runRucio.txt")
    exit()
