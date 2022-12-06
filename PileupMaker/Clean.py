
f = open("pileup.txt", "r").readlines()
T = []
for i in f:
  i = i.replace("\n", "")
  if "-"*10 in i:
    continue
  if "SCOPE:NAME" in i:
    continue
  i = i.split("|")[1]
  i = i.split(":")[1]
  T.append(i)

T = list(set(T))


f = open("pileupList.txt", "w")
f.write("\n".join(T))
f.close()
