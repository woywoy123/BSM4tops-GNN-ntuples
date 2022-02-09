#!/bin/bash 

NumberOfCores=12
FilesPerCore=5
SampleTexts="/CERN/FourTopsAnalysis"
Configs="/CERN/FourTopsAnalysis/configs"
DIR=$PWD

ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh

cd ../
source setup.sh


config=()
cd $Configs
for i in *
do
  config+=("$Configs/$i")
done

cd $SampleTexts
l=0
cpu=()
for i in *
do

  if [[ "$i" != "TestFile_"* ]]
  then 
    continue
  fi
  echo $i
  
  rm -rf SampleIndex_$l
  mkdir SampleIndex_$l
  cd SampleIndex_$l

  k=0
  str="" 
  t=0
  testf=""
  while read -r line;
  do 
    if [[ $k -ge $FilesPerCore ]]
    then 
      k=0
      t=$(($t+1))
      echo "$str" > Qu_$t.txt
      str=""
    fi
    k=$(($k+1)) 
    str="$line,$str"
    if [[ $line != "" ]]
    then
      testf=$line
    fi
  done < ../$i
  
  if [[ "$str" != "" ]]
  then 
    echo "$str" > Qu_$t.txt
  fi
  
  echo $testf >> test.txt
  for k in ${config[@]}
  do
    if [[ $k == *"_Test" ]]
    then 
      echo "Testing: -> "$k
      top-xaod $k test.txt >> log.txt
      
      testf=""
      for j in ./*
      do
        if [[ $j == *".root" ]]
        then
          testf="$k"_nominal.txt
          rm output*
          rm test.txt
          rm log.txt
          break
        fi
      done 
      if [[ $testf != "" ]]
      then 
        break
      fi
    fi
  done

  Complete=()
  t=0
  for k in *
  do
    if [[ $k != *".txt" ]]
    then 
      continue
    fi

    mkdir QU_$t
    cd QU_$t
    top-xaod $testf ../$k >> log.txt &
    cpu+=("$!")
    
    if [[ ${#cpu[@]} -ge $NumberOfCores ]]
    then 

      while true 
      do 
        alive=()
        for j in ${cpu[@]}
        do
          if ps  -p $j > /dev/null
          then 
            echo "Running: $j"
            alive+=("$j")
            cpu=$alive
          fi
        done
        
        if (( ${#alive[@]} == 0 ))
        then 
          cpu=()
          break
        fi 
        sleep 40
        echo "__________" 
      done
    fi
    cd ../
    t=$(($t+1))
  done 
  cd ../
  l=$(($l+1))
done 

cd $DIR
