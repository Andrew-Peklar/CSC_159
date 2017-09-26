// events.S, initial stage handling an event, build proc frame mainly

#include <spede/machine/asmacros.h>    // do not use/include "spede.h"
#include "events.h"                    // for K_DATA, K_STACK_SIZE below

.comm k_stack, 8192, 1                 // declare kernel stack space (8192 x 1 byte)
.text

// loads the trapframe of the selected process in order to run it
ENTRY(ProcLoader)
   movl 4(%esp),%eax                   //copy (movl) 4 bytes right above ESP into EAX
   movl %eax,%esp                      //copy EAX to ESP (point ESP to proc frame space)
   popa
   iret                                //interrupt return

// build proc frame, and go into kernel
ENTRY(TimerEvent)                      // will first push EFL, CS, EIP (hardware/circuit)
   pusha                               //push-all
   movl %esp,%ebx                      //copy ESP to EBX
   cld                                 //clear direction flag in EFL
   movw $0x10, %ax                     // set kernel data segment registers
   mov %ax, %ds                        // set kernel data segment registers
   mov %ax, %es                        // set kernel data segment registers
   leal k_stack + 8192, %esp           // point ESP to kernel stack
   pushl %ebx                          //push EBX there (into kernel stack)
   call CNAME(Kernel)                  //call the Kernel C code