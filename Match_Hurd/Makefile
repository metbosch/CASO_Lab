all: proc mps mtask thread vm vm-read msg

proc: proc.c 
	gcc -D_GNU_SOURCE -O -o proc proc.c

mps: mps.c print-task-info.c
	gcc -D_GNU_SOURCE -O -o mps mps.c print-task-info.c

mtask: mtask.c print-task-info.c
	gcc -D_GNU_SOURCE -O -o mtask mtask.c print-task-info.c

thread: thread.c
	gcc -D_GNU_SOURCE -O -o thread thread.c

msg: msg.c
	cc -D_GNU_SOURCE -O -o msg msg.c

vm: vm.c
	cc -D_GNU_SOURCE -O -o vm vm.c

vm-read: vm-read.c
	cc -D_GNU_SOURCE -O -o vm-read vm-read.c

clean:
	rm -f thread thread.o mps mps.o print-task-info.o \
              msg msg.o vm vm.o vm-read vm-read.o proc proc.o \
              mtask mtask.o
