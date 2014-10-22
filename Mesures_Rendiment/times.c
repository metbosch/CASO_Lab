#include <stdio.h>
#include <stdlib.h>

#define NUM_PARAMS 2
#define SBRK_INC   1024

struct timeval begin, end;

void checkError(int res, char * str)
{
   if (res != 0) {
      printf(str);
      exit(1);
   }
}

void usage()
{
   printf("Usage: SysCall [sbrk, sbrk(inc), sched_yeld, getpid, fork-waitpid], NumCalls\n");
   exit(1);
}


int main (int argc, char *argc[])
{
   int i, call, reps;

   if (argc != NUM_PARAMS + 1) usage();
   call = atoi(argc[1]);
   reps = atoi(argc[2]);
   checkError(call < 0 || call >= 5, "Bad SysCall ID, must be between 0 and 4\n");
   checkError(reps < 0, "Number of repetitions can't be negative\n");

   unsigned long time = 0;
   for (i = 0; i < reps; ++i) {
      printf("Starting call %d", i);
      if (call == 0) {           // sbrk
         checkError(gettimeofday(&begin, 0) == 0, "Error getting time");
      } else if (call == 1) {    // sbrk(inc)

      } else if (call == 2) {    // sched_yeld

      } else if (call == 3) {    // getpid

      } else if (call == 4) {    // fork-wait

      }
      printf(" ...Done");
   }

}
