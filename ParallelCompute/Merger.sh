#!/bin/bash 

mkdir Merger
cd Merger 
Merge=$PWD
cd ..

for item in *
do
  if [[ $item == "QU_"* ]]
  then 
    mv -v $item/output.root $Merge/$item.root
  fi 
done 

cd $Merge
string=""
for item in *
do
  string="$item $string"
done 

ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh

$ROOTSYS/bin/hadd Merger.root $string 

mv Merger.root ../
cd ../
