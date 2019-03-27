#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

#include "process_control.h"
// maximum time units in Round-Robin policy
#define RR_SLICE 500

/* 
Given to scheduler:
   1. details of each process
   2. number of processes
*/

int schuduler_FIFO(Process *proc, int N_procs);
int schuduler_RR(Process *proc, int N_procs);
int schuduler_SJF(Process *proc, int N_procs);
int schuduler_RSJF(Process *proc, int N_procs);

#endif
