#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "scheduler.h"
#include "process_control.h"
#include "quicksort.c"

int CMP(const void *a, const void *b){
	Process *c = (Process *)a;
	Process *d = (Process *)b;
	
	if( c->ready_time < d->ready_time )
		return -1;
	else if( c->ready_time > d->ready_time )
		return 1;
	else if( c->exec_time < d->exec_time )
		return -1;
	else
		return 1;
}

int main(){
	char SP[8];
	int n;
	scanf("%s", SP);
	scanf("%d", &n);
	Process* proc = malloc(n * sizeof(Process));

	for(int i = 0 ; i < n ; i++){
		Process *tmp = (proc + i);
		scanf("%s%d%d", tmp -> name, &(tmp -> ready_time), &(tmp -> exec_time));
		tmp -> pid = -1; // initialize pid
		if(pipe((tmp -> pipe_fd)) < 0){
			perror("error: pipe");
			exit(1);
		}
	}

	qsort(proc, n, sizeof(Process), CMP);
	assign_core(getpid(), 0);

	if(strcmp(SP, "FIFO") == 0){
		scheduler_FIFO(proc, n);
	}
	else if(strcmp(SP, "RR") == 0){
		scheduler_RR(proc, n);
	}
	else if(strcmp(SP, "SJF") == 0){
		scheduler_SJF(proc, n);
	}
	else if(strcmp(SP, "PSJF") == 0){
		scheduler_PSJF(proc, n);
	}
	else{
		printf("No Such scheduler policy.\n");
	}

	return 0;
}
