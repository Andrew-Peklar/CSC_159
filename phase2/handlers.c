// handlers.c, 159

#include "spede.h"
#include "types.h"
#include "data.h"
#include "tools.h"
#include "proc.h"
#include "handlers.h"

// to create process, 1st alloc PID, PCB, and process stack space
// build process frame, initialize PCB, record PID to run_q (if not 0)
void NewProcHandler(func_p_t p) {  // arg: where process code starts
   int pid;

   if(0 == ready_q.size) { // may occur as too many processes been created
      cons_printf("Kernel Panic: cannot create more process!\n");
      return;                   // alternative: breakpoint() into GDB
   }

   pid = DeQ(&ready_q);
   MyBzero((char *)&pcb[pid], sizeof(pcb_t));
   pcb[pid].state = RUN;
   EnQ(pid, &run_q);

   pcb[pid].proc_frame_p = (proc_frame_t *)&proc_stack[pid][0];

   pcb[pid].proc_frame_p->EFL = EF_DEFAULT_VALUE|EF_INTR;
   pcb[pid].proc_frame_p->EIP = p;
   pcb[pid].proc_frame_p->CS = get_cs();
}

// count run_time of running process and preempt it if reaching time slice
void TimerHandler(void) {
   static unsigned int timer_tick = 0;
   timer_ticks++;
   

   outportb(0x20, 0x60); // 0x61 0x62

   //////////////////////////////////////////////////////
   while()
   {
	
   }
   //////////////////////////////////////////////////////
   if(run_pid == 0) return;

   pcb[run_pid].run_time++;
   if(pcb[run_pid].run_time == TIME_SLICE) {
      EnQ(run_pid, &run_q);
      run_pid = -1;
   }
}
////////////////////////////////////////////////
void GetPidHandler(void){
  outportb(0x20, 0x60);
  pcb[run_pid].proc_frame_p-> EBX = run_pid;
  GetPid();
}
////////////////////////////////////////
void WriteHandler(proc_frame_t p){
   char *str;
      p->EBX;
      if(p->EBX == STDOUT) {
         str = (char *)p->ECX;
         cons_printf(str);

}
void SleepHandler(void){
      outportb(0x20, 0x60);
      
      pcb[run_pid].wake_time = timer_ticks + 100 * seconds2sleep;
      seconds2sleep in p->EBX
      pcb[run_pid].state = RUN;
      run_pid = -1
  
}

