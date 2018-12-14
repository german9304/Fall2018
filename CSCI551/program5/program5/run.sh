#!/bin/sh
### script to run one job

### Set the job name
###scp -r program5 german9304@login-29-239.pod.penguincomputing.com:/home/german9304
### ssh  german9304@login-29-239.pod.penguincomputing.com
#PBS -N project3

### Join the standard output and standard error streams
#PBS -j oe

### Specify wallclock time required for this job, hhh:mm:ss

#PBS -l walltime=00:40:00
### Specify nodes and features
#PBS -l nodes=1:ppn=256

### Specify the queue
#PBS -q IntelKNL

### set directory for job execution
cd ~german9304/program5

### load module
module load intel/2018

### record the date and execute
date
./main 8000