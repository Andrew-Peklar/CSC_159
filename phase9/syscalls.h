// syscalls.h

#ifndef _SYSCALLS_H_
#define _SYSCALLS_H_

int GetPid(void);         // no input, 1 return
void Write(int, char *);
void Sleep(int);
void Mutex(int);
char GetChar(int);
void PutChar(int, char);
void PutStr(int, char *);
void GetStr(int, char *, int);   //???
int Fork(void);       //phase 7
void Signal(int, func_p_t );
void Exit(int);       //phase 9
int WaitPid(int *);   //phase 9
#endif
