// handlers.c, 159

#include "spede.h"
#include "types.h"
#include "data.h"
#include "tools.h"
#include "proc.h"
#include "handlers.h"

// to create process, 1st alloc PID, PCB, and process stack space
// build process frame, initialize PCB, record PID to run_q (if not 0)
void NewProcHandler(func_ptr_p p) {  // arg: where process code starts
   int pid;




  // if the size of ready_q is 0  // may occur as too many processes been created
  // show on Target PC: "Kernel Panic: cannot create more process!\n"
  //return;                   // alternative: breakpoint() into GDB
   


   //get a 'pid' from ready_q
   //use tool function MyBzero to clear PCB and runtime stack
   //set state of process in PCB
   //queue it (pid) to be run_q unless it's 0 (SystemProc)

   //point proc_frame_p to into stack (to where best to place a process frame)
   //fill out EFL with "EF_DEFAULT_VALUE|EF_INTR" // to enable intr!
   //fill out EIP to p
   //fill CS with the return from a get_cs() call 
}

// count run_time of running process and preempt it if reaching time slice
void TimerHandler(void) {
   //declare a staic local (unsigned int) counter timer_tick = 0
   unsigned int timer_tick = 0;

   if(timer_tick++ % 75 == 0)    cons_printf(".");       // if timer_tick++ is a multiple of 75, show a period symbol on target PC

   outportb(0x21, ~0x01);                                // dismiss timer event (IRQ0) <------------- ???

   if(run_pid == 0)     return;                          // if the running process is SystemProc, simply return

   pcb[run_pid].run_time++;                              // upcount the run_time of the running process
   if(pcb[run_pid].run_time == TIME_SLICE) {             // if it reaches the the OS time slice
      pcb[run_pid].state = READY;                        //update/downgrade its state
      EnQ(run_pid, &run_q);                            //queue it back to run queue
      run_pid = -1;                                      //reset the running pid (to -1)

   }
}

