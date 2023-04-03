#!/bin/bash 
export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh
cd ../source/
asetup --restore 
cd ../build/
source ./*/setup.sh
make 
cd ../SmallRun
top-xaod Dilepton_MC_d.txt test.txt
