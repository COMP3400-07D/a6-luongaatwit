#include "parta.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stio.h>

int main(int argc, char* argv[]) {
   if (argc < 3) { 
    printf("ERROR: Missing arguments\n");
    return 1;
   }

   char* alg = argv[1];

   if (strcmp(alg, "fcfs") == 0) { //fcfs

    if ( argc < 3 + 0) {
        printf("ERROR: Missing arguments\n");
    return 1;
   }
   int plen = argc -2; 
   int* bursts = malloc(sizeof(int)* plen);

   for (int i = 0; i < plen ; i++) {
    bursts[i] = atoi(argv[i + 2]);
   }
   

   printf("using FCFS\n\n");

   struct pcb* procs = init_procs(bursts, plen);

   for (int i = 0; i < plen; i++) {
    printf("Accepted P%d: Burst %d\n", procs[i].pid, procs[i].burst_left);
   }

   double avg = fcfs_run(procs,plen);
   printf("Average wait time: .2%f\n", avg);

   free(procs);
   free(bursts);
   return 0;

   }

   else { 
    printf("ERROR: Missing arguments\n");
    return 1; 
   }
}

