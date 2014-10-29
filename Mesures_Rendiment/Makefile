all: times write-to-disk1 write-to-disk2 read-from-disk

proc: times.c
	gcc -D_GNU_SOURCE -O -o times times.c

write-to-disk1: write-to-disk1.c
	gcc -o write-to-disk1 write-to-disk1.c

write-to-disk2: write-to-disk2.c
	gcc -o write-to-disk2 write-to-disk2.c

read-from-disk: read-from-disk.c
	gcc -o read-from-disk read-from-disk.c

clean:
	rm -f times read-from-disk write-to-disk1 read-from-disk *.o
