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

int main ()
{
   int res, i;
   mach_port_t host_privileged_port, pset, pset_priv;
   device_t device_privileged_port;
   task_array_t task_list;
   mach_msg_type_number_t task_count;

   res = get_privileged_ports(&host_privileged_port, &device_privileged_port);
   if (res != KERN_SUCCESS) {
      printf ("Error getting privileged ports (0x%x), %s\n", res,
                mach_error_string(res));
      exit(1);
   }

   res = processor_set_default(host_privileged_port, &pset);
   if (res != KERN_SUCCESS) {
      printf ("Error setting default processor (0x%x), %s\n", res,
                mach_error_string(res));
      exit(1);
   }

   res = host_processor_set_priv(host_privileged_port, pset, &pset_priv);
   if (res != KERN_SUCCESS) {
      printf ("Error setting privileged processor (0x%x), %s\n", res,
                mach_error_string(res));
      exit(1);
   }

   res = processor_set_tasks(pset_priv, &task_list, &task_count);
   if (res != KERN_SUCCESS) {
      printf ("Error getting set of tasks (0x%x), %s\n", res,
                mach_error_string(res));
      exit(1);
   }

   for (i=0; i < (int)(task_count); i++) {
      Print_Task_info((task_t)task_list[i]);
   }
}
