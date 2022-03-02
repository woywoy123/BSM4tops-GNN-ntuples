cd ..
ATLAS=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
source ${ATLAS}/user/atlasLocalSetup.sh
source setup.sh


cd run 
cd Files

l=0
for i in *
do
  mkdir Out_$l
  cd Out_$l
  top-xaod ../ljets_calib_cuts_mc16a_nominal.txt ../TestFile_$l.txt
 
  fail=false
  for k in ./*
  do
    if [[ $k == *".tmp" ]]
    then 
      fail=true
      mv Output.tmp Output_a.tmp
    fi

    if [[ $k == *".root" ]]
    then 
      mv Output.root Output_a.root
    fi
  done 
  
  if [[ $fail == true ]]
  then 
    top-xaod ../ljets_calib_cuts_mc16d_nominal.txt ../TestFile_$l.txt
 
    fail=false
    for k in ./*
    do
      if [[ $k == *".tmp" ]]
      then 
        fail=true
        mv Output.tmp Output_d.tmp
      fi

      if [[ $k == *".root" ]]
      then 
        mv Output.root Output_d.root
      fi
    done 
  fi

  if [[ $fail == true ]]
  then 
    top-xaod ../ljets_calib_cuts_mc16e_nominal.txt ../TestFile_$l.txt
 
    fail=false
    for k in ./*
    do
      if [[ $k == *".tmp" ]]
      then 
        fail=true
        mv Output.tmp Output_e.tmp
      fi

      if [[ $k == *".root" ]]
      then 
        mv Output.root Output_e.root
      fi
    done 
  fi

  cd ..
  l=$(($l+1))
done
