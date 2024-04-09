#include "disk/disk.h"
#include "memory/memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc > 1) {
    if (strcmp(argv[1], "disco") == 0) {
      if (argc == 3) {
        // Pasamos la opción -tm o -tg a mostrarEstadisticasDisco
        disk_show_stats("/", argv[2]);
      } else {
        // Sin argumentos adicionales, pasamos una cadena vacía
        disk_show_stats("/", "");
      }
      return EXIT_SUCCESS; // Finaliza después de manejar 'disco'
    } else if (strcmp(argv[1], "memoria") == 0) {
      if (argc == 3) {
        // Muestra la información de memoria para todos los procesos
        if (strcmp(argv[2], "-v") == 0) {
          memory_show_virtual_usage();
        } else if (strcmp(argv[2], "-r") == 0) {
          memory_show_real_usage();
        } else {
          fprintf(stderr, "Opción no reconocida. Uso: %s memoria [-v | -r]\n", argv[0]);
          return EXIT_FAILURE;
        }
      } else if (argc == 4) {
        // Muestra la información de memoria para un PID específico
        if (strcmp(argv[2], "-v") == 0) {
          memory_usage_virtual_pid(argv[3]);
        } else if (strcmp(argv[2], "-r") == 0) {
          memory_usage_real_pid(argv[3]);
        } else {
          fprintf(stderr, "Opción no reconocida. Uso: %s memoria [-v | -r] [PID]\n", argv[0]);
          return EXIT_FAILURE;
        }
      } else {
        fprintf(stderr, "Uso incorrecto. Uso: %s memoria [-v | -r] [PID opcional]\n", argv[0]);
        return EXIT_FAILURE;
      }
      return EXIT_SUCCESS;
    } else {
      fprintf(stderr, "Comando no reconocido. Uso: %s [disco | memoria] [opciones] [PID opcional]\n", argv[0]);
      return EXIT_FAILURE;
    }
  } else {
    fprintf(stderr, "Uso: %s [disco | memoria] [opciones] [PID opcional]\n", argv[0]);
    return EXIT_FAILURE;
  }
}