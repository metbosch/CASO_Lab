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

#define PAG_SIZE 4096
#define SLEEP_TIME 1500

void checkError(int res, char * str) {
   if (res != KERN_SUCCESS) {
      printf (str, res, mach_error_string(res));
      exit(1);
   }
}

int main ()
{
   vm_address_t address;
   mach_port_t child;
   mach_port_t self = mach_task_self();
   char data[PAG_SIZE] __attribute__((aligned(PAG_SIZE)));

   checkError(task_create(self, 0, &child), "Error creating task (0x%x), %s\n");
   checkError(vm_allocate(child, &address, PAG_SIZE, 1),
              "Error allocating vm (0x%x), %s\n");
   checkError(vm_write(child, address, (vm_offset_t)data, PAG_SIZE),
              "Error copying vm data (0x%x), %s\n");

#if PRINT_DATA_INFO
   data[0] = 10;
   printf("Data Structure info\n");
   printf("  Starts: %d\n", &data[0]);
   printf("  Ends:   %d\n", &data[PAG_SIZE - 1]);
   printf("  Size:   %d\n", PAG_SIZE);
#endif

   sleep(SLEEP_TIME);

   checkError(task_terminate(child), "Error terminating task (0x%x), %s\n");

}
