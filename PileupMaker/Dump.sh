#!/bin/bash 

export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh
lsetup rucio 

echo "$pass" | voms-proxy-init -voms atlas --valid 144:00

while IFS= read -r line
do
  VAR=$(echo $line | cut -d"." -f2)
  rucio ls "mc16_13TeV:*.$VAR*deriv.NTUP_PILEUP*" >> pileup.txt
done  < "./Samples.txt"


