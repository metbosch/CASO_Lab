#include <mach.h>
#include <mach_error.h>
#include <mach/mig_errors.h>
#include <mach/thread_status.h>
#include <stdio.h>
#include <stdlib.h>
#include <hurd.h>


void Print_Task_info(task_t t)
{
        task_basic_info_data_t task_data;
        task_info_t ta_info = &task_data;
        mach_msg_type_number_t task_info_outCnt = TASK_BASIC_INFO_COUNT;

      int res;
      res = task_info(t, TASK_BASIC_INFO , ta_info, &task_info_outCnt);
      if (res != KERN_SUCCESS) {
         printf ("Error getting task_info (%d), %s\n", res,
                   mach_error_string(res));
         exit(1);
      }
      printf ("    suspend count %d\n", task_data.suspend_count);
      printf ("    base priority %d\n", task_data.base_priority);
      printf ("    virtual size %d\n", task_data.virtual_size);
      printf ("    resident size %d\n", task_data.resident_size);
      printf ("    user time %d %d\n", task_data.user_time.seconds,
                                        task_data.user_time.microseconds);
      printf ("    system time %d %d\n", task_data.system_time.seconds,
                                        task_data.system_time.microseconds);
      printf ("    creation time %d %d\n", task_data.creation_time.seconds,
                                        task_data.creation_time.microseconds);
      pid_t pid = task2pid(t);
      printf ("      pid %d\n", pid);
}
