#include <sys/time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sched.h>

#define NUM_PARAMS 2
#define SBRK_INC   1024

struct timeval begin, end;

void checkError(int res, char * str)
{
   if (res != 0) {
      printf("%s", str);
      exit(1);
   }
}

void usage()
{
   printf("Usage: SysCall [sbrk, sbrk(inc), sched_yield, getpid, fork-waitpid], NumCalls\n");
   exit(1);
}

void execChild() {
   exit(0);
}

int main (int argc, char *argv[])
{
   int i, call;
   long int reps;

   if (argc != NUM_PARAMS + 1) usage();
   call = atoi(argv[1]);
   reps = atoi(argv[2]);
   checkError(call < 0 || call >= 5, "Bad SysCall index, must be between 0 and 4\nUsage: SysCall [sbrk, sbrk(inc), sched_yield, getpid, fork-waitpid], NumCalls\n");
   checkError(reps < 0, "Number of repetitions can't be negative\nUsage: SysCall [sbrk, sbrk(inc), sched_yield, getpid, fork-waitpid], NumCalls\n");

   checkError(gettimeofday(&begin, 0) != 0, "Error getting time\n");
   if (call == 0) {           // sbrk
      for (i = 0; i < reps; ++i) {
         checkError(((void *) -1) == sbrk(0), "Error on sbrk(0)\n");
      }
   } else if (call == 1) {    // sbrk(inc)
      void * oldSbrk = sbrk(0);
      for (i = 0; i < reps; ++i) {
         checkError(oldSbrk != sbrk(SBRK_INC), "Error on sbrk(SBRK_INC)\n");
         oldSbrk += SBRK_INC;
      }
   } else if (call == 2) {    // sched_yield
      for (i = 0; i < reps; ++i) {
         checkError(0 != sched_yield(), "Error on sched_yield()\n");
      }
   } else if (call == 3) {    // getpid
      for (i = 0; i < reps; ++i) {
         getpid();
      }
   } else if (call == 4) {    // fork-wait
      int pid, status;
      for (i = 0; i < reps; ++i) {
         pid = fork();
         checkError(pid < 0, "Error on fork\n");
         if (pid == 0) execChild();
         checkError(0 > waitpid(-1, &status, 0), "Error on waitpid\n");
      }
   }
   checkError(gettimeofday(&end, 0) != 0, "Error getting time");
   double time = (double)((end.tv_sec - begin.tv_sec)*1000000.0 + (end.tv_usec - begin.tv_usec));

   printf("------- RESULTS -------\n");
   printf("Total:\t%f us\n", time);
   printf("Med:\t%f us\n", time/(double)reps);
   printf("-----------------------\n");
}
