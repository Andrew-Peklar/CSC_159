// handlers.h, 159

#ifndef _HANDLERS_H_
#define _HANDLERS_H_

#include "types.h"   // need definition of 'func_p_t' below

void NewProcHandler(func_p_t);
void TimerHandler(void);
void GetPidHandler(void);
void WriteHandler(proc_frame_t*);
void SleepHandler(void);

#endif
