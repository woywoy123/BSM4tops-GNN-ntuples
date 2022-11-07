import glob 
import os
import shutil

mc = {}
mc["r9364"]  = "a" #"EventSelection/SingleLeptonJet_MC_a.txt"
mc["r10201"] = "d" #"EventSelection/SingleLeptonJet_MC_d.txt"
mc["r10724"] = "e" #"EventSelection/SingleLeptonJet_MC_e.txt"

try:
    os.mkdir("ALL")
except:
    pass


for i in glob.glob("xAODInfo/*"):
    camp = ""
    for k in i.split("_"):
        if k in mc:
            camp = mc[k]
    if camp == "":
        continue
    try:
        shutil.copytree(i, "ALL" + "/" + i.split("/")[-1].split("\xa2")[-1])
    except:
        continue

DUMP = []
MC = {}
MC["a"] = []
MC["d"] = []
MC["e"] = []
import time
MC = {}

print("_____________________________")
for i in glob.glob("ALL/*"):
    proc = i.split(".")[2:][0].split("_")[1:]
    proc = [k for k in proc if "H7UE" not in k and "A14" not in k] 
    proc = [k for k in proc if "NNPDF" not in k and "221" not in k] 
    proc = [k for k in proc if "222" not in k and "MEN" not in k] 
    proc = [k for k in proc if "HThalf" not in k and "704" not in k] 
    proc = proc[0]

    if "r9364" in i:
        cmp = "a"
    if "r10201" in i:
        cmp = "d"
    if "r10724" in i:
        cmp = "e"
    
    if cmp not in MC:
        MC[cmp] = {}
    if proc not in MC[cmp]:
        MC[cmp][proc] = []

    
    MC[cmp][proc].append(i.split("/")[-1])

    f = open(i + "/FileNames.txt")
    x = [l.replace("\n", "").split(",")[0] for l in f.readlines()]
    f.close()
    DUMP += x
    shutil.rmtree(i)

C = []
C.append("import TopExamples.grid")
for i in MC:
    for j in MC[i]:
        name = j + "_mc16" + i
        C.append("TopExamples.grid.Add(" + '"' + name + '").datasets = [')
        C += ['"' + k + '",' for k in MC[i][j]]
        C.append("]")
    C.append("")

F = open("MC16_precent.py", "w")
F.write("\n".join(C))
F.close()
