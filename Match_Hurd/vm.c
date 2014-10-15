#include <mach.h>
#include <mach_error.h>
#include <mach/mig_errors.h>
#include <mach/thread_status.h>
#include <mach/processor_info.h>
#include <mach/mach_host.h>
#include <stdio.h>
#include <stdlib.h>
#include <hurd.h>

#define PAG_SIZE 4096
#define SLEEP_TIME 15

char data[PAG_SIZE] __atribute__((aligned(PAG_SIZE)));

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

   checkError(task_create(self, 0, &child), "Error creating task (0x%x), %s\n");
   checkError(vm_alocate(child, &address, PAG_SIZE, 1),
              "Error alocating vm (0x%x), %s\n");
   checkError(vm_write(child, &address, (vm_offset_t)data, PAG_SIZE),
              "Error copying vm data (0x%x), %s\n");

   sleep(SLEEP_TIME);

   checkError(task_terminate(child), "Error terminating task (0x%x), %s\n");

}
