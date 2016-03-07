#!/bin/tcsh

set OutFile=$1
set TmpOut=${OutFile}_tmp.txt 

# Regression test for FSI obstacle (steady state) case

if( -d HronTurekBeam ) then
  echo "removing HronTurekBeam directory"
  rm -r HronTurekBeam
endif

mkdir HronTurekBeam
cd HronTurekBeam

cp $2/share/Testing/test_data/HronTurekBeam/* .

$3/SolverModuleDriver -com-mpi 1.0

if( ! -e hronturektest.ep ) then
  echo "No hronturektest.ep results file from running Elmer"
  exit 1
endif
tail -n 546 hronturektest.ep | cut -d " " -f 3 > yvals.txt

$4/diffdatafiles yvals.txt yvals_gold.txt -t 1.0e-9 -n

@ result = 1

if($? != 0) then
  echo "Test data did not pass with tolerance of 1e-9."
  @ result = 0
endif
printf "HronTurekBeam:Works=${result}\n" >> ${TmpOut}
cat ${TmpOut} >> ../${OutFile}
cd ../
rm -r HronTurekBeam

exit 0