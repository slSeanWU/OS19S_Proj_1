#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "scheduler.h"
#include "process_control.h"

int schuduler_FIFO(Process *proc, int N_procs){

	int cur = -1;

	while(1){

		cur += 1;
		if( cur >= N_procs ) break;

		pid_t chpid = proc_create(proc[cur]);

		while( proc[cur].exec_time > 0 ){
			// tell process to run 1 time unit
			write(proc[cur].pipe_fd[1], "run", strlen("run"));
			// run 1 time unit itself
			TIME_UNIT();
			proc[cur].exec_time -= 1;
		}

		// wait child process
		int re_status;
		waitpid(chpid, &re_status, 0);
		if( !(WIFEXITED(re_status)) ){
			perror("error: child process terminated inappropriately");
			return 1;
		}

	}

	return 0;
}