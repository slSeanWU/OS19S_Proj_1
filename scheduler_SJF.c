#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <sys/types.h>
#include <sys/syscall.h>

#include "process_control.h"

typedef struct sched_param Sched_pm;
typedef struct timespec Time_sp;

int time = 0;

int find_shortest(Process *proc, int N_procs){
	int shortest = -1, excute_time = INT_MAX;

	for (int i = 0; i < N_procs; i++){
		if (proc.ready_time < time && proc[i].exec_time && proc[i].exec_time < excute_time){
			excute_time = proc[i].exec_time;
			shortest = i;
		}
	}

	return shortest;
}

int scheduler_SJF(Process *proc, int N_procs){
	int finish = 0;
	
	while (finish < N_procs){
		int target = find_shortest(proc, N_procs);
		
		if (target != -1){
			pid_t chpid = process_create(proc[target]);
			proc[target].pid = chpid;

			while (proc[target].exec_time > 0){
				// tell child process to run 1 time unit
				char tmp = "run";
				write(proc[target].pipe_fd[1], tmp, strlen(tmp));
				
				TIME_UNIT();
				time++;
				proc[target].exec_time--;
			}

			finish++;			
			// wait child process
			int _return;
			waitpid(proc[target].pid, &_return, 0);
			
			if (WIFEXITED(_return) != 1){
				fprintf(stderr, "error: child process terminated inappropriately");
				return 0;
			}
		}

		else{
			TIME_UNIT();
			time++;
		}
	}

	return 1;
}