The project contains two folders:
1)Sequential
2)Parallel

1)Sequential:
*In this the program runs in the sequential mode.
*The slurm file is provided to run the program.
*The program runs as ./Execute [networkSize]

2)Parallel
*The parallel part has two slurm files namely slurm_twitter.sh and slurm_twitter_step.sh
*The program runs as ./Execute [networkSize] [step].
*The step indicates the frequency of communication done between master and workers.Low value 
indicates higher frequency in communication with the step values ranging from 1 to the networkSize.
* The slurm_twitter.sh has its step size set to 1 where as the slurm_twitter_step.sh has its 
step size set to 100 for test runs.
*The program makes 1 node as master and others as workers from the available nodes.
*The number of workers should be chosen in such a way that the division of networkSize is
equal for all nodes as we have not handled irregular division.
*Many of the printing statements are commented due to huge number of printing data.
*To verify probabilities,followers and following we can remove comments from line number 598 to line
604 in NetworkGenerator.cpp file.
*To verify tweet propagation we can remove comments from line number 619 and 534.