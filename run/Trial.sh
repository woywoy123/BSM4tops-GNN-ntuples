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
  top-xaod ../../ljets_calib_cuts_mc16a_nominal.txt ../TestFile_$l.txt &
  cd ..
  l=$(($l+1))
done
