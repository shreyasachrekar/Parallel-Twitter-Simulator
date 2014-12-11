#!/bin/sh 
#SBATCH --partition=debug
#SBATCH --time=00:20:00 
#SBATCH --nodes=1 
#SBATCH --ntasks-per-node=1
##SBATCH--constraint=CPU-E5-2660
# Memory per node specification is in MB. It is optional. 
# The default limit is 3GB per core. 
#SBATCH --job-name="Twitter_Simulator" 
#SBATCH --output=Twitter__1K.out
#SBATCH --mail-user=pdeshpan@buffalo.edu 
##SBATCH --mail-type=ALL 
##SBATCH --requeue 
#Specifies that the job will be requeued after a node failure. 
#The default is that the job will not be requeued. 
module list 
ulimit -s unlimited # 

#export I_MPI_PMI_LIBRARY=/usr/lib64/libpmi.so
#export I_MPI_DEBUG=4
./Execute 1000
