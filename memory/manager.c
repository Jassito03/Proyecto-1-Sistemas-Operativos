#include "./manager.h"

// Refactor
// Dividir cada una de las estadisticas en funciones para reducir el main

int main(int argc, char *argv[]) {
  if (argc > 1) {
    pid_t pid;
    int data[2];

    if (pipe(data) == -1) {
      perror("Error al ejecutar el comando");
      exit(EXIT_FAILURE);
    }

    if (strcmp(argv[1], "memoria") == 0) {
      if (argc == 3) {
        // Muestra la información de memoria para todos los procesos
        if (strcmp(argv[2], "-v") == 0) {
          pid = fork();
          if (pid < 0) {
            perror("Error al ejecutar el comando");
            exit(EXIT_FAILURE);
          }

          if (pid == 0) {
            close(data[0]);
            // Traer datos
            // write(data[1], &variable, sizeof(variable));
            close(data[1]);
          } else {
            waitpid(pid, NULL, 0);
            close(data[1]);
            // Leer datos
            // read(data[0], &variable, sizeof(variable));
            // mostrar datos
            close(data[0]);
          }
        } else if (strcmp(argv[2], "-r") == 0) {
          pid = fork();
          if (pid < 0) {
            perror("Error al ejecutar el comando");
            exit(EXIT_FAILURE);
          }

          if (pid == 0) {
            close(data[0]);
            // Traer datos
            // write(data[1], &variable, sizeof(variable));
            close(data[1]);
          } else {
            waitpid(pid, NULL, 0);
            close(data[1]);
            // Leer datos
            // read(data[0], &variable, sizeof(variable));
            // mostrar datos
            close(data[0]);
          }
        } else {
          fprintf(stderr, "Opción no reconocida. Uso: %s memoria [-v | -r]\n", argv[0]);
          return EXIT_FAILURE;
        }
      } else if (argc == 4) {
        // Muestra la información de memoria para un PID específico
        if (strcmp(argv[2], "-v") == 0) {
          pid = fork();
          if (pid < 0) {
            perror("Error al ejecutar el comando");
            exit(EXIT_FAILURE);
          }

          if (pid == 0) {
            close(data[0]);
            // Traer datos
            // write(data[1], &variable, sizeof(variable));
            close(data[1]);
          } else {
            waitpid(pid, NULL, 0);
            close(data[1]);
            // Leer datos
            // read(data[0], &variable, sizeof(variable));
            // mostrar datos
            close(data[0]);
          }
        } else if (strcmp(argv[2], "-r") == 0) {
          pid = fork();
          if (pid < 0) {
            perror("Error al ejecutar el comando");
            exit(EXIT_FAILURE);
          }

          if (pid == 0) {
            close(data[0]);
            // Traer datos
            // write(data[1], &variable, sizeof(variable));
            close(data[1]);
          } else {
            waitpid(pid, NULL, 0);
            close(data[1]);
            // Leer datos
            // read(data[0], &variable, sizeof(variable));
            // mostrar datos
            close(data[0]);
          }
        } else {
          fprintf(stderr, "Opción no reconocida. Uso: %s memoria [-v | -r] [PID]\n", argv[0]);
          return EXIT_FAILURE;
        }
      } else {
        fprintf(stderr, "Uso incorrecto. Uso: %s memoria [-v | -r] [PID opcional]\n", argv[0]);
        return EXIT_FAILURE;
      }
      return EXIT_SUCCESS;
    }
  } else {
    fprintf(stderr, "Uso: %s memoria [-v | -r] [PID opcional]\n", argv[0]);
    return EXIT_FAILURE;
  }
  return 0;
}