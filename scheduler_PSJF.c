#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/syscall.h>

#include "process_control.h"

int preemptive_find_shortest(Process *proc, int N_procs, int time){
	int shortest = -1, excute_time = INT_MAX;

	for (int i = 0; i < N_procs; i++){
		if (proc[i].ready_time < time && proc[i].exec_time && proc[i].exec_time < excute_time){
			excute_time = proc[i].exec_time;
			shortest = i;
		}
	}

	return shortest;
}

int scheduler_PSJF(Process *proc, int N_procs){
	int time = 0;

	int finish = 0, started[N_procs];
	memset(started, 0, sizeof(started));
	
	while (finish < N_procs){
		int target = preemptive_find_shortest(proc, N_procs, time);
		
		if (target != -1){
			if (started[target] == 0){
				pid_t chpid = proc_create(proc[target]);
				proc_resume( chpid );

				proc[target].pid = chpid;
				started[target] = 1;
			}
			else {
				proc_resume( proc[target].pid );
			}

			// tell child process to run 1 time unit
			char tmp[5] = "run";
			write(proc[target].pipe_fd[1], tmp, strlen(tmp));
			TIME_UNIT();
			time++;

			proc[target].exec_time--;		
			proc_kickout( proc[target].pid );
			
			if (proc[target].exec_time == 0){		
				// wait child process
				int _return;
				waitpid(proc[target].pid, &_return, 0);
				
				if (WIFEXITED(_return) != 1){
					fprintf(stderr, "error: child process terminated inappropriately");
					return 1;
				}

				finish++;
			}
		}		
		else{
			TIME_UNIT();
			time++;
		}
	}

	return 0;
}
