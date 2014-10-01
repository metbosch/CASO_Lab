#include <mach.h>
#include <mach_error.h>
#include <mach/mig_errors.h>
#include <mach/thread_status.h>
#include <stdio.h>
#include <stdlib.h>
#include <hurd.h>


        processor_array_t processor_list = NULL;
        mach_msg_type_number_t processor_listCnt = 0;

void printProcInfo ( processor_t proc, unsigned int index ) {
   mach_msg_type_number_t procInfoCont;
   kernel_return_t ret;
   processor_info_t info;
   processor_basic_info_t basicInfo;

   procInfoCont = sizeof(int)*PROCESSOR_INFO_MAX;
   ret = processor_info (proc, PROCESSOR_BASIC_INFO, host, info, &procInfoCont);
   if( res != KERN_SUCCESS) {
	   fprintf(stderr, "Error getting the processor %d info [0x%x]:\n\t%s\n", i, res, mach_error_string(res));
	   exit(1);
   }

   basicInfo = (processor_basic_info_t) &info[index];
   fprintf(stdout, "------------> CPU %d <------------\n", index);
   fprintf(stdout, "CPU Type:   \t\t%d\n", basicInfo->cpu_type);
   fprintf(stdout, "CPU Subtype:\t\t%d\n", basicInfo->cpu_subtype);
   fprintf(stdout, "CPU Running:\t\t%s\n", basicInfo->running ? "YES" : "NO");
   fprintf(stdout, "Slot number:\t\t%d\n", basicInfo->slot_num);
   fprintf(stdout, "CPU Master: \t\t%s\n", basicInfo->is_master ? "YES" : "NO");
   fprintf(stdout, "----------------------------------\n");
}

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
      printProcInfo(processor_list[i], i);
}
