#include "parta.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * creates array of PCB in a heap
 * @returns an array on heap
 */
struct pcb* init_procs(int* bursts, int blen) {
    if (blen <= 0) {
        return NULL;
    }

    struct pcb* procs = malloc(sizeof(struct pcb) *blen);
    
    if (!procs) {
        return NULL;
    } 

    for (int i = 0; i < blen; i++) {
        procs[i].pid = i;
        procs[i].burst_left = bursts[i];
        procs[i].wait = 0;

    }

    return procs; 
}

/**
 * Prints currect values of PCB
 */
void printall(struct pcb* procs, int plen) {
    for (int i = 0; i < plen; i++) {
        printf("P%d: burst_left=%d wait=%d\n", procs[i].pid, procs[i].burst_left, procs[i].wait);
    }
}

/**
 * "runs" a test case runtime for amount of time
 */
void run_proc(struct pcb* procs, int plen, int current, int amount) {
    if (!procs || plen <= 0 || current < 0 || current >= plen) { 
        return;
    }

    int run_amount = amount;
    
    if (procs[current].burst_left < run_amount) { 
        run_amount = procs[current].burst_left;
    }

    procs[current].burst_left -= run_amount;
    
    if( procs[current].burst_left < 0) {
        procs[current].burst_left = 0; 
    }

    for( int i = 0; i < plen; i++) {
        if(i != current && procs[i].burst_left > 0 ) {
        procs[i].wait += run_amount;
    }
    
    }
}

/**
 * runs through each process startign from 0 until completed 
 * @returns total time 
 */
int fcfs_run(struct pcb* procs, int plen) {
   if (!procs || plen <= 0) { 
    return -1;
   }

   int time = 0;

   for( int i = 0; i < plen; i++) {
    while (procs[i].burst_left > 0) {
        int amt = procs[i].burst_left;
        run_proc (procs, plen, i, amt);
        time += amt;
    }

   }
   return time;
}

/**
 * gets the next process after the current 
 * @returns the next process to run
 */
int rr_next(int current, struct pcb* procs, int plen) {
   if (!procs || plen <= 0) { 
    return -1;
   }

   int working_procs = 0;

   for (int i = 0; i <plen; i++) {
    if(procs[i].burst_left > 0 ) {
        working_procs = 1; 
        break;
    }
   }

   if (!working_procs) {
    return -1;
   }

   for (int offset =1 ; offset <= plen; offset++) {
    int idx = (current + offset) % plen;
    if (procs[idx].burst_left > 0 ) {
        return idx;
    }
   }

   if (procs[current].burst_left > 0) {
    return current;
   }
   return -1; 

}
/**
 * TODO: Describe what the function does
 */
int rr_run(struct pcb* procs, int plen, int quantum) {
    
}

