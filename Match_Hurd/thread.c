#include <mach.h>
#include <mach_error.h>
#include <mach/mig_errors.h>
#include <mach/thread_status.h>
#include <mach/processor_info.h>
#include <mach/mach_host.h>
#include <stdio.h>
#include <stdlib.h>
#include <hurd.h>


        processor_array_t processor_list = NULL;
        mach_msg_type_number_t processor_listCnt = 0;

void checkError(int res, char * str) {
   if (res != KERN_SUCCESS) {
      printf (str, res, mach_error_string(res));
      exit(1);
   }
}

int main ()
{
   int res, i;
   mach_port_t child;
   mach_port_t self = mach_task_self();

   checkError(thread_create(self, &child), "Error creating thread (0x%x), %s\n");
}
