#!/bin/bash

function CondorBuild
{
  echo "executable = $1/OutRucio.sh" > example.submit
  #echo "output = results.output.$""(ClusterID)"  >> example.submit
  echo "error =  $1/results.error.$""(ClusterID)"  >> example.submit
  echo "log =  $1/results.log.$""(ClusterID)"  >> example.submit
  echo "Request_Cpus = 1"  >> example.submit
  echo "Request_Memory = 2048MB" >> example.submit
  echo "+RequestRunTime= 172800"  >> example.submit
  echo "queue 1"  >> example.submit
}

ROOT=$PWD
cd ../EventSelection 
python WriteConfig.py
cd ../MultiProcessing
mkdir -p Output
mkdir -p Sorted

while true
do
  python MakeConfigs.py
  for i in $ROOT/Output/*
  do 
    echo $i
    skip=false
    for j in $i/*
    do
      if [[ "$j" == *"/*"* ]]
      then 
        continue
      fi
  
      if [[ "$j" == *"done.txt"* ]]
      then 
        skip=true
      fi
      
      if [[ "$j" == *"Rucio.sh"* ]]
      then
        run=$j
      fi
  
      if [[ "$j" == *"OutRucio.sh"* ]]
      then
        run2=$j
      fi
    done
    
    if [[ $skip == true ]]
    then 
      echo "Skipped $i"
      continue
    fi
  
    echo "---> $i"
    echo $run
    echo $run2
    echo "________"
    chmod +x $run
    chmod +x $run2
    bash $run
    cd $i
    CondorBuild $i
    condor_submit example.submit 
    cd -
    echo $run
  done
done
