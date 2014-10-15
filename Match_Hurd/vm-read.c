#include <mach.h>
#include <mach_error.h>
#include <mach/mig_errors.h>
#include <mach/thread_status.h>
#include <mach/processor_info.h>
#include <mach/mach_host.h>
#include <stdio.h>
#include <stdlib.h>
#include <hurd.h>
#include <unistd.h>

#define NUM_PARAMS 2
#define READ_SIZE 16

void checkError(int res, char * str) {
   if (res != KERN_SUCCESS) {
      printf (str, res, mach_error_string(res));
      exit(1);
   }
}

void usage() {
   printf("Usage: PID, mem dir\n");
   exit(1);
}

int main (int argc, char *argv[])
{
   unsigned int address, pid, i;
   mach_port_t task;
   mach_msg_type_number_t data_count;
   char data[READ_SIZE];

   if (argc != NUM_PARAMS + 1) usage();
   pid = atoi(argv[1]);
   address = (vm_address_t)(atoi(argv[2]));

   task = (mach_port_t)(pid2task((pid_t)pid));
   checkError(task == MACH_PORT_NULL, "Error getting the task from PID (0x%x), %s\n");
   checkError(vm_read(task, (vm_address_t)address, (vm_size_t)READ_SIZE ,(vm_offset_t *)(&data), data_count),
              "Error reading (0x%x), %s\n");
   checkError((unsigned int)(data_count) != READ_SIZE, "Error num bytes readed (expected 16 bytes) (0x%x), %s\n	");

   write(1, &data, READ_SIZE);

}
