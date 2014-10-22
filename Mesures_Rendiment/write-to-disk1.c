#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    struct timeval begin, end;
    int chunkSize = 128;
    char str[chunkSize];
    int sizeWrite = 200*1024*1024;
	FILE * fp;
    fp = fopen (argv[1], "w+");

	gettimeofday(&begin, NULL);
	while (sizeWrite > 0) {
   	    fwrite(str , 1 , chunkSize , fp );
        sizeWrite -= chunkSize;
	}
    gettimeofday(&end, NULL);
    fclose(fp);
    double elapsed = (end.tv_sec - begin.tv_sec) + ((end.tv_usec - begin.tv_usec)/1000000.0);
    printf("Temps escritura: %f \n", elapsed);
    double x = 200.0*1024*1024/elapsed;
    double y = 200.0/elapsed;
    printf("Bandwith: %fbytes x sec \n", x);
    printf("Bandwith: %fMbytes x sec \n", y);

    return(0);
}
