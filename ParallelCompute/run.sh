#!/bin/bash 

NumberOfCores=7
FilesPerCore=1
SampleTexts="/CERN/SamplesFromGrid/Background/"
Configs="/CERN/SamplesFromGrid/Background/configs"
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
  Run=false
  cmp=""
  for k in ${config[@]}
  do
    if [[ $k != *"_Test" ]]
    then 
      continue
    fi

    tmp=$(cat test.txt)
    echo "$tmp"

    if [[ "$tmp" == *"_r9364_"* ]]
    then 
      cmp="a"
    fi

    if [[ "$tmp" == *"_r10201_"* ]]
    then 
      cmp="d"
    fi

    if [[ "$tmp" == *"_r10724_"* ]]
    then 
      cmp="e"
    fi
  
    echo "$cmp"

    if [[ "$k" != *"mc16$cmp"* ]]
    then 
      continue
    fi
  
    echo "Testing: -> "$k
    top-xaod $k test.txt >> log.txt
    
    testf=""
    for j in ./*
    do
      if [[ $j == *".root" ]]
      then
        testf="$k"_nominal.txt
        rm output*
        rm log.txt
        rm test.txt
        Run=true
        break
      fi
    done 
    
    if [[ $Run == true ]]
    then 
      break
    fi
  
  done

  if [[ $Run == false ]]
  then 
    exit
  fi

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
      
      for pid in ${cpu[*]}
      do
        wait $pid
        echo "Finished $pid"
      done
      cpu=()

    fi
    cd ../
    t=$(($t+1))
  done 

  cp $DIR/Merger.sh .
  cd ../
  l=$(($l+1))
done 

for pid in ${cpu[*]}
do
  wait $pid
  echo "Finished $pid"
done

for i in *
do

  if [[ "$i" != "SampleIndex_"* ]]
  then 
    continue
  fi
  echo $i
  cd $i
  bash Merger.sh
  
  cd ../

done

cd $DIR
