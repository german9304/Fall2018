#!/bin/sh
### script to run one job

### Set the job name
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
cd ~german9304/grazo

### load module
module load intel/2018

### record the date and execute
date
./gauss 8000