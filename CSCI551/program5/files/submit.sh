#! /bin/sh
rm -f *.o* combined-output.txt combined-error.txt

qsub -v OMP_NUM_THREADS=1  ./run.sh
qsub -v OMP_NUM_THREADS=2  ./run.sh
qsub -v OMP_NUM_THREADS=5  ./run.sh
qsub -v OMP_NUM_THREADS=10  ./run.sh
qsub -v OMP_NUM_THREADS=20  ./run.sh
qsub -v OMP_NUM_THREADS=30  ./run.sh
qsub -v OMP_NUM_THREADS=40  ./run.sh
qsub -v OMP_NUM_THREADS=50  ./run.sh
qsub -v OMP_NUM_THREADS=60  ./run.sh