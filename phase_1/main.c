// main.c, 159
// OS bootstrap and kernel code for OS phase 1
//
// Team Name: Null (Members: Khalid Muslih and Andrew Peklar)

#include "spede.h"      // given SPEDE stuff
#include "types.h"      // data types
#include "events.h"     // events for kernel to serve
#include "tools.h"      // small functions for handlers
#include "proc.h"       // process names such as SystemProc()
#include "handlers.h"   // handler code

// kernel data are all declared here:
int run_pid;            // currently running PID; if -1, none selected
q_t ready_q, run_q;     // processes ready to be created and runables
pcb_t pcb[PROC_NUM];    // Process Control Blocks
char proc_stack[PROC_NUM][PROC_STACK_SIZE]; // process runtime stacks

void ProcScheduler(void) {              // choose run_pid to load/run
   if(run_pid > 0)     return;          // if run_pid is greater than 0, return; no need if PID is a user proc

   //if the run_q is empty let run_pid be zero
   //else get the 1st in run_q to be run_pid

   //accumulate its life_time by adding its run_time
   //and then reset its run_time to zero
}

int main(void) {  // OS bootstraps
   int i;
   struct i386_gate *IDT_p;                                    // DRAM location where IDT is

   run_pid = -1;                                               //set run_pid to -1

   MyBzero((char *) &ready_q, sizeof(q_t));                    // MyBzero to clear ready_q
   MyBzero((char *) &run_q  , sizeof(q_t));                    // MyBzero to clear run_q

   for(int i = 0; i < Q_SIZE; i++)    EnQ(i, &ready_q);        // EnQ 0~19 to ready_q (all PID's are ready)

   IDT_p = get_idt_base();                                     // get the IDT_p 
   cons_printf("IDT at DRM addr %x (%d).\n" , IDT_p, IDT_p);   // show location on Target PC

   //fill out IDT entry #32 like in the timer lab exercise           <----------------------------------------- ???
   // set PIC mask to open up for timer event signal (IRQ0) only     <----------------------------------------- ???

   NewProcHandler(SystemProc);                                 //call NewProcHandler(SystemProc) to create the 1st process
   ProcScheduler();                                            //call ProcScheduler() to select the run_pid
   ProcLoader(pcb[run_pid].proc_frame_p)                       //call ProcLoader with the proc_frame_p of the selected run_pid


   return 0; // compiler needs for syntax altho this statement is never exec
}

void Kernel(proc_frame_t *proc_frame_p) {                      // kernel code runs (100 times/second)
   char key;
   pcb[run_pid].proc_frame_p = proc_frame_p;                   //save the proc_frame_p to the PCB of run_pid



   //call the timer even handler routine to handle the timer interrupt event

  // if a key has been pressed on Target PC {
   //   get the key
   //   if it's 'n,' create a new UserProc by calling NewProcHandler()
   //   if it's 'b,' go to the GDB prompt, by calling breakpoint()

   ProcScheduler();                                            //call ProcScheduler() to select the run_pid
   ProcLoader(pcb[run_pid].proc_frame_p)                       //call ProcLoader with the proc_frame_p of the selected run_pid
}
