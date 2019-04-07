#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "scheduler.h"
#include "process_control.h"

int scheduler_RR(Process *proc, int N_procs){

	pid_t chpids[N_procs];

	for(int i=0; i<N_procs; i++){
		chpids[i] = proc_create(proc[cur]);
		proc_kickout(chpids[i]);
	}

	int N_fin = 0; //number of finished processes

	while(1){

		for(int i=1; i<N_procs; i++){

			if( proc[i].exec_time <= 0 ) continue;

			// run an RR round
			proc_resume(chpid[i]);

			int kt = 500; //time quantum for RR
			while( proc[i].exec_time > 0 && kt > 0){
				write(proc[cur].pipe_fd[1], "run", strlen("run")); // tell process to run 1 time unit
				TIME_UNIT(); // run 1 time unit itself
				kt --;
				proc[cur].exec_time --;
			}

			// if process finished
			if(proc[i].exec_time <= 0){

				int re_status;
				waitpid(chpids[i], &re_status, 0);
				if( !(WIFEXITED(re_status)) ){
					perror("error: child process terminated inappropriately");
					return 1;
				}

				N_fin ++;

			}else{
				proc_kickout(chpids[i]);
			}

		}

		if( N_fin >= N_procs ) break;
	}

	return 0;
}
