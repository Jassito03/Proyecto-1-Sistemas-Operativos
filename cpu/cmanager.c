#include "./cpu_t.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string,h>

#define CMANAGER_MAX_BUFFER_SIZE 100

// Dividirlo en más funciones
// Devolver argumentos
cpu_t *cmanager_cpu_t_create() {
  char *name;
  int args[10];
  const char *comando = "cat /proc/stat | grep  cpu | head -n 1 | awk '{for (i=1; i<=NF; i++) print $i}'";
  char line[CMANAGER_MAX_BUFFER_SIZE];

  FILE *file = popen(comando, "r");
  if (file == NULL) {
    perror("Error al ejecutar el comando");
    exit(EXIT_FAILURE);
  }
int i = 0;
  while (fgets(line, CMANAGER_MAX_BUFFER_SIZE, file)) {
    if (i == 0) {
      name = strdup(line);
    } else {
      args[i - 1] = atoi(line);
    }
    i++;
  }
  pclose(file);
  cpu_t *cpu = malloc(sizeof(cpu_t));
  if (!cpu) {
    perror("Error de memoria");
    exit(EXIT_FAILURE);
  }
  cpu_t_init(cpu, name, args);
  free(name);

  return cpu;
}

int main() {
  cpu_t *cpu = cmanager_cpu_t_create();
  printf("Nombre cpu: %s ", cpu->name);
  printf("%d ", cpu->cant_user_process);
  printf("%d ", cpu->cant_niced_process);
  printf("%d ", cpu->cant_system_process);
  printf("%d ", cpu->cant_idle);
  printf("%d ", cpu->cant_iowait);
  printf("%d ", cpu->cant_irq);
  printf("%d ", cpu->cant_softirq);
  printf("%d ", cpu->cant_steal);
  printf("%d ", cpu->cant_guest);
  printf("%d ", cpu->cant_guest_nice);
  return 0;
}
