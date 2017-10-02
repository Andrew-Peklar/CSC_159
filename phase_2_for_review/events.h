// events.h of events.S
// prototypes those coded in events.S

#ifndef _EVENTS_H_
#define _EVENTS_H_

#ifndef ASSEMBLER  // skip below if ASSEMBLER defined (from an assembly code)
                   // since below is not in assembler syntax


#define TIMER_EVENT 32       // IDT entry #32 has code addr for timer event (DOS IRQ0)
#define SYSCALL_EVENT 128
__BEGIN_DECLS

#include "types.h"                // proc_frame_t

void TimerEvent(void);            // coded in events.S, assembler won't like this syntax
void SyscallEvent(void);
void ProcLoader(proc_frame_t *);  // coded in events.S

__END_DECLS

#endif // ifndef ASSEMBLER

#endif // ifndef _EVENTS_H_

