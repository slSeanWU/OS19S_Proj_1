#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "scheduler.h"
#include "process_control.h"
#include "quicksort.c"

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

	quickSort(proc, 0, n - 1);
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
