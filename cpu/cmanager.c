#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define MAX_BUFFER_SIZE 1024

int cmanager_calc_cores(){ 
    const char* comando = "cat /proc/cpuinfo | grep siblings | grep : | grep -m 1 2 | awk '{print $NF}'";
    int cores;

    FILE* file = popen(comando, "r");
    if (file == NULL) {
      perror("Error al ejecutar el comando");
      exit(EXIT_FAILURE);
    }
  
  if(fscanf(file,"%d",&cores) != 1){
    perror("Error al leer la salida del comando");
    pclose(file);
    exit(EXIT_FAILURE);
  }
  pclose(file);

  return cores;
}

int main() {
    int salida = cmanager_calc_cores();
    salida = salida + 1;
    printf("Salida: %d", salida);
    return 0;
}
