#!/bin/sh
#SBATCH --partition=debug
#SBATCH --time=00:05:00
#SBATCH --nodes=3
#SBATCH --ntasks-per-node=3
##SBATCH --constraint=CPU-E5-2660
##SBATCH --mem=24000
#SBATCH --job-name="twitter"
#SBATCH --output=twitter.out
#SBATCH --mail-user=pdeshpan@buffalo.edu
#SBATCH --mail-type=ALL
##SBATCH --requeue
#Specifies that the job will be requeued after a node failure.
#The default is that the job will not be requeued.
#export | grep SLURM
echo "SLURM_JOBID="$SLURM_JOBID
echo "SLURM_JOB_NODELIST"=$SLURM_JOB_NODELIST
echo "SLURM_NNODES"=$SLURM_NNODES
echo "SLURMTMPDIR="$SLURMTMPDIR
echo "working directory = "$SLURM_SUBMIT_DIR
module load intel
module load intel-mpi
module list
ulimit -s unlimited
#
#sleep 120
#export I_MPI_DEBUG=9
echo "Launch twitter simulator parallely"
export I_MPI_PMI_LIBRARY=/usr/lib64/libpmi.so
srun ./Execute 100000 100
#
echo "All Done!"