#!/bin/bash

function CondorBuild
{
  echo "executable = $1/Out.sh" > $1/example.submit
  #echo "output = results.output.$""(ClusterID)"  >> example.submit
  echo "error =  $1/results.error.$""(ClusterID)"  >> $1/example.submit
  echo "log =  $1/results.log.$""(ClusterID)"  >> $1/example.submit
  echo "Request_Cpus = 1"  >> $1/example.submit
  echo "Request_Memory = 2048MB" >> $1/example.submit
  echo "+RequestRunTime= 172800"  >> $1/example.submit
  echo "queue 1"  >> $1/example.submit
}

ROOT=$PWD
mkdir -p $ROOT/Output
mkdir -p $ROOT/Samples

cpu=()
while true
do
  python ScanSamples.py
  for i in $ROOT/Output/*
  do
    for j in $i/*
    do
      ex=""
      for k in $j/*
      do
        if [[ $k == *"FIN.txt"* || "$k" == *"running.txt"* ]]
        then 
          echo "--> $k"
          ex=""
          break
        fi
        if [[ $k == *"Out.sh" ]]
        then
          ex=$k
        fi
      done
      if [[ $ex == "" ]]
      then 
        sleep 10
        continue
      fi

      if [[ ${#cpu[@]} -ge 7 ]]
      then 
        for pid in ${cpu[*]}
        do
          wait $pid
          echo "Finished $pid"
        done
        cpu=()
      fi  
      echo "" > "$j/running.txt"
      CondorBuild $j
      bash $ex &
      cpu+=("$!")
      sleep 1
    done
  done
done

