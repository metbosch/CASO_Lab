#include <mach.h>
#include <mach_error.h>
#include <mach/mig_errors.h>
#include <mach/thread_status.h>
#include <stdio.h>
#include <stdlib.h>
#include <hurd.h>


        processor_array_t processor_list = NULL;
        mach_msg_type_number_t processor_listCnt = 0;

int main ()
{
   int res, i;
   mach_port_t host_privileged_port;
   device_t device_privileged_port;

   res = get_privileged_ports(&host_privileged_port, &device_privileged_port);
   if (res != KERN_SUCCESS) {
      printf ("Error getting privileged ports (0x%x), %s\n", res,
                mach_error_string(res));
      exit(1);
   }

   printf ("privileged ports: host 0x%x  devices 0x%x\n",
                     host_privileged_port, device_privileged_port);

   printf ("Getting processors at array 0x%x\n", processor_list);

   res = host_processors(host_privileged_port,
                         &processor_list, &processor_listCnt);
   if (res != KERN_SUCCESS) {
      printf ("Error getting host_processors (0x%x), %s\n", res,
                mach_error_string(res));
      exit(1);
   }

   printf ("        processors at array 0x%x\n", processor_list);
   printf ("processor_listCnt %d\n", processor_listCnt);

   for (i=0; i < processor_listCnt; i++)
      printf ("processor_list[%d] 0x%x\n", i, processor_list[i]);
}
