#! /bin/sh
###scp -r combined-output.txt grazo1@jaguar.csuchico.edu:/user/student/grazo1/Fall2018/CSCI551/program5

cat *.o* >> combined-output
rm -f *.o*
