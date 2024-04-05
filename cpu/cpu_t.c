#include "./cpu_t.h"

void cpu_t_init(cpu_t *cpu_t, char *new_name, int news_args[10]) {
  cpu_t->name = new_name;
  cpu_t->cant_user_process = news_args[0];
  cpu_t->cant_niced_process = news_args[1];
  cpu_t->cant_system_process = news_args[2];
  cpu_t->cant_idle = news_args[3];
  cpu_t->cant_iowait = news_args[4];
  cpu_t->cant_irq = news_args[5];
  cpu_t->cant_softirq = news_args[6];
  cpu_t->cant_steal = news_args[7];
  cpu_t->cant_guest = news_args[8];
  cpu_t->cant_guest_nice = news_args[9];
}

// getarguments()

// Create(cpu_t*) -> Se llaman a los argumentos y se inicializa
