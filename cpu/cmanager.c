#include <stdlib.h>
#include <errno.h>

#define MAX_BUFFER_SIZE 1024

char* num_cores(const char* comando) {
  char* cores = malloc(MAX_BUFFER_SIZE);
    if(cores == NULL) {
      perror("Error de asignación de memoria");
      exit(EXIT_FAILURE);
    }

    FILE* file = popen(comando, "r");
    if (file == NULL) {
      perror("Error al ejecutar el comando");
      free(cores);
      exit(EXIT_FAILURE);
    }
  
  fgets(cores,MAX_BUFFER_SIZE, file);

  return cores;
}

int main() {
    const char* comando = "cat /proc/cpuinfo | grep siblings | grep : | grep -m 1 2 | awk '{print $NF}'";
    char* salida = num_cores(comando);
    printf("Salida: %s", salida);
    free(salida);
    return 0;
}
