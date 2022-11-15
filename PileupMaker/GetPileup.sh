#!bin/bash

export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh
lsetup rucio 
echo "$pass" | voms-proxy-init -voms atlas --valid 144:00

mkdir -p PileUp
cd PileUp

while IFS= read -r line
do
  echo $line
  rucio get $line
done  < "../pileupList.txt"


