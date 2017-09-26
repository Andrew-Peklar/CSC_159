// syscalls.c
// API calls to kernel system services

// GetPid() call
int GetPid(void) {          // no input, has return
   int pid;

   asm("pushl %%EAX;        // save register EAX to stack
        movl $100, %%EAX;   // service #100
        int $128;           // interrupt CPU with IDT Event 128
        movl %%EAX, %0;     // after, copy EAX to variable 'pid' (%0 means 1st item below)
        popl %%EAX"         // restore original EAX
       : "=g" (pid)         // output syntax, for output argument
       :                    // no input items
    );

   return pid;
}

// Write() call
void Write(int fileno, char *p) {
   // asm("
   //   save registers that will be used here
   //   send in service #, fileno, and p via
   //   three suitable registers
   //   issue syscall
   //   recover those saved registers
       :          // no outputs, otherwise, use "=g" (...)
       : "g" (fileno), "g" ((int)p)  // inputs, %0 and %1
       );
}

// void Sleep(int) {
// send in # of seconds to sleep (in EBX)
// 101 -> EAX, call "int 128", 
