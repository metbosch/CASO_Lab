#include <sys/time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#define FILE_PATH "/tmp/caso_write200.txt"
#define SIZE_WRITE 200*1024*1024
#define NUM_PARAMS 3

struct timeval begin, end;

void handleError(const char *text) {
    perror(text);
    exit(1);
}

void usage() {
    printf("USAGE: chunkSize[def. 1024 bytes], sync[0, 1], FilePath\n");
    exit(1);
}

void printResults(double time, unsigned int SIZE) {
   printf("------- RESULTS -------\n");
   printf("Time:\t%f s\n", time);
   printf("Bytes:\t%d\n", SIZE);
   printf("MB/s:\t%f\n", SIZE/time/1000000.0);
   printf("-----------------------\n");
}

void main(int argc, char *argv[]) {
   int chunkSize = 1024;
   unsigned char sync = 0;

   if (argc != 1 && argc != 1 + NUM_PARAMS) usage();
   if (argc != 1) {
      chunkSize = atoi(argv[1]);
      sync = atoi(argv[2]);
   }

   FILE *f = fopen(argv[3], "w+");
   if (f == NULL) handleError("Error opening file");
   if (gettimeofday(&begin, 0) != 0) handleError("Error getting time");

   int i;
   char data[chunkSize];
   for (i = 0; i < SIZE_WRITE - chunkSize; i += chunkSize) {
      fwrite(data, 1, chunkSize, f);
   }
   fwrite(data, 1, SIZE_WRITE - i, f);

   if (sync != 0) {
       int id = fileno(f);
       if (id < 0) handleError("Error getting file_id");
       if (fsync(id) != 0) handleError("Error syncronizating disk");
   }
   if (gettimeofday(&end, 0) != 0) handleError("Error getting time");

   fclose(f);
   printResults((double)((end.tv_sec - begin.tv_sec) +
                 (end.tv_usec - begin.tv_usec)/1000000.0), SIZE_WRITE);
}
