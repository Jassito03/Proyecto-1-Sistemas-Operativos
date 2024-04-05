#include "./cpu_t.h"

typedef struct cpu_t {
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

void cpu_t_init(cpu_t *cpu_t, char new_name[5], int news_args[10]) {
  cpu_t->name[5] = new_name[5];
  cpu_t->cant_user_process = news_args[1];
  cpu_t->cant_niced_process = news_args[2];
  cpu_t->cant_system_process = news_args[3];
  cpu_t->cant_idle = news_args[4];
  cpu_t->cant_iowait = news_args[5];
  cpu_t->cant_irq = news_args[6];
  cpu_t->cant_softirq = news_args[7];
  cpu_t->cant_steal = news_args[8];
  cpu_t->cant_guest = news_args[9];
  cpu_t->cant_guest_nice = news_args[10];
}
