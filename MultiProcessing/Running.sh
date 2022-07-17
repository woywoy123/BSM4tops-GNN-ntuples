#!/bin/bash

function CondorBuild
{
  echo "executable = ./$1/Spawn.sh" >> example.submit
  #echo "output = ./results.output.$""(ClusterID)"  >> example.submit
  echo "error =  ./$1/results.error.$""(ClusterID)"  >> example.submit
  echo "log =  ./$1/results.log.$""(ClusterID)"  >> example.submit
  echo "Request_Cpus = 1"  >> example.submit
  echo "Request_Memory = 2048MB" >> example.submit
  echo "+RequestRunTime= 172800"  >> example.submit
  echo "queue 1"  >> example.submit
}


nCPU=7

ROOT=$PWD
cd ../EventSelection 
python WriteConfig.py
cd ../MultiProcessing
mkdir -p Output
mkdir -p Sorted

python MakeConfigs.py




cpu=()
for i in $ROOT/Output/*
do 
  fin=false
  for j in $i/*
  do
    if [[ "$j" == *"/*"* ]]
    then 
      continue
    fi
    if [[ "$j" == *"done.txt"* ]]
    then 
      fin=true
    fi
   
    if [[ "$j" == *"run.txt"* ]]
    then 
      x=($(cat $j | tr "/" "\n"))
      root=${x[-2]}
    fi

    if [[ "$j" == *"Out.sh"* ]]
    then
      run=$j
    fi
  done
  
  if [[ $fin == true ]]
  then 
    mkdir -p $ROOT/Sorted/$root
    mv $i $ROOT/Sorted/$root/
  fi

  if [[ ${#cpu[@]} -ge $nCPU ]]
  then 
    for pid in ${cpu[*]}
    do
      echo "Waiting for $pid"
      wait $pid
      echo "Finished $pid"
    done
    cpu=()
  fi
  bash $run &
  cpu+=("$!")
  echo $run
done
