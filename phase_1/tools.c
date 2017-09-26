// tools.c, 159

#include "spede.h"
#include "types.h"
#include "data.h"

// clear DRAM data blocks by filling zeroes
void MyBzero(char *p, int size) {
   while (size--)    *p++ = 0;                                          //loop 'size' times, set where p points to 0, increment p
}

// dequeue, return 1st element in array, and move all forward
int DeQ(q_t *p) {                                                       // return -1 if q[] contains no valid elements
   int i = -1,  element = -1;
   
   if(p -> size == 0)     return element;                               // if queue is empty, return element
  
   element = p -> q[0];                                                 // copy the 1st in the array that p points to to element
   p -> size--;                                                         // decrement the size of the queue that p points to
   while (++i != p -> size)    p -> q[i] = p->[i+1];                    // move all elements in the array to the front by one position

   return element;
}

// enqueue element to next available position in array, 'size' is array index
void EnQ(int element, q_t *p) {

   if(p -> size == Q_SIZE) {                                            // if queue is full
      cons_printf(""Kernel Panic: queue is full, cannot EnQ!\n"");      // print error on target pc
      return;                                                           // return (or breakpoint() into GDB if you want)
   }
   p -> q[p -> size] = element;                                         //copy element to the location in the array indexed by 'size'
   p -> size++;                                                         //increment 'size' of the queue 
}
