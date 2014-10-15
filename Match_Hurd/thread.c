#include <mach.h>
#include <mach_error.h>
#include <mach/mig_errors.h>
#include <mach/thread_status.h>
#include <mach/processor_info.h>
#include <mach/mach_host.h>
#include <stdio.h>
#include <stdlib.h>
#include <hurd.h>

#define STACK_SIZE 8192
#define SLEEP_TIME 15


        processor_array_t processor_list = NULL;
        mach_msg_type_number_t processor_listCnt = 0;

unsigned char threadStack[STACK_SIZE];

void threadLoop() {
   while(1) {

   }
}

void checkError(int res, char * str) {
   if (res != KERN_SUCCESS) {
      printf (str, res, mach_error_string(res));
      exit(1);
   }
}

int main ()
{
   struct i386_thread_state thread_state;
   mach_msg_type_number_t state_count;
   mach_port_t child;
   mach_port_t self = mach_task_self();

   checkError(thread_create(self, &child), "Error creating thread (0x%x), %s\n");
   checkError(thread_get_state(child, i386_THREAD_STATE, &thread_state, &state_count),
              "Error getting thread state (0x%x), %s\n");
   thread_state.uesp = threadStack[STACK_SIZE] - 100;
   thread_state.eip = threadLoop;
   checkError(thread_set_state(child, i386_THREAD_STATE,(thread_state_t *)(&thread_state), state_count),
              "Error setting thread state (0x%x), %s\n");
   checkError(thread_resume(child), "Error resuming thread (0x%x), %s\n");

   sleep(SLEEP_TIME);

   checkError(thread_terminate(child), "Error terminating thread (0x%x), %s\n");

}
