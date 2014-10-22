all: times

proc: times.c
	gcc -D_GNU_SOURCE -O -o times times.c
write-to-disk1: write-to-disk1.c
	gcc -o write-to-disk1 write-to-disk1.c
write-to-disk2: write-to-disk2.c
	gcc -o write-to-disk2 write-to-disk2.c

clean:
	rm -f times times.o
