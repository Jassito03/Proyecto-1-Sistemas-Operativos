#include <stdio.h>

typedef struct {
  // Identifier
  char name[5];
  // Processes executing in user mode
  int cant_user_process;
  // Niced processes executing in user mode
  int cant_niced_process;
  // Processes executing in kernel mode
  int cant_system_process;
  // Twiddling thumbs
  int cant_idle;
  // Waiting for I/O to complete
  int cant_iowait;
  // Servicing interrupts
  int cant_irq;
  // Servicing softirqs
  int cant_softirq;
  // Counts the ticks spent executing other virtual hosts
  int cant_steal;
  // Counts the time spent running a virtual CPU for guest operating systems under the control of the Linux kernel
  int cant_guest;
  // Time spent running a niced guest
  int cant_guest_nice;
} cpu_t;
void cpu_t_init(cpu_t *, char[5], int[10]);