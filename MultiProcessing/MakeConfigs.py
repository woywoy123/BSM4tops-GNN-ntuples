import shutil 
import os
import glob

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
    script = [
               "ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase",
               "source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh",
               "setupATLAS",
               "cd " + SRCDir+ "/source/", 
               "asetup --restore", 
               "cd " + SRCDir + "/build", 
               "source ./*/setup.sh",
               "cd " + OutDir, 
               "top-xaod " + config + " " + run + " >> log.txt", 
               'echo "DONE" > done.txt'
    ]

    if runner == True:
        script.append("rm $(cat " + run + ") && " + run)
    Write(script, f)


def DumpRucio(f, SMPL):
    rucio = [
               "ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase",
               "source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh",
               "setupATLAS",
               "lsetup rucio", 
               "rucio get --no-subdir mc16_13TeV:" + SMPL,
            ]
    Write(rucio, f)
               


ANA="/CERN/SamplesFromGrid/Downloading"
PROC="/CERN/SamplesFromGrid/Processed"
INPT = "/home/tnom6927/bsm4tops-gnn-ntuples/"
OUPT = INPT + "MultiProcessing/Output/"

mc = {}
mc["r9364"] = INPT + "/EventSelection/SingleLeptonJet_MC_a.txt"
mc["r10201"] = INPT + "/EventSelection/SingleLeptonJet_MC_d.txt"
mc["r10724"] = INPT + "/EventSelection/SingleLeptonJet_MC_e.txt"

smpls = {}
run = {}
mc_run = {}
for i in ReadDir(ANA):
    for j in ReadDir(i):
        smpls[j] = "/".join(j.split("/")[:-1])
        run[j] = True
        mc_run[j] = mc[[k for k in j.split("_") if k in mc][0]]

for i in ReadDir(PROC):
    for j in ReadDir(i):
        if "root.tmp" in [k for k in ReadDir(j) if ".root" in k][0]:
            print("REMOVING: ", j)
            shutil.rmtree(j)
            continue
        if j + ".pool.root.1" not in run:
            run[j + ".pool.root.1"] = False
            smpls[j + ".pool.root.1"] = ""
            mc_run[j + ".pool.root.1"] = mc[[k for k in j.split("_") if k in mc][0]]

for i in run:
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




