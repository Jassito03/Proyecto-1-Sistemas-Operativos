#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define BIN_CPU "cpu"
#define BIN_DISK "disco"
#define BIN_MEMORY "memoria"

void main_not_arguments(char *command, char *arg[]) {
  pid_t pid = fork();
  if (pid < 0) {
    perror("Error al ejecutar el comando");
    exit(EXIT_FAILURE);
  }

  if (pid == 0) {
    execl(command, command, NULL);
  } else {
    waitpid(pid, NULL, 0);
  }
}

void main_arguments(char *command, char *arg[]) {
  pid_t pid = fork();
  if (pid < 0) {
    perror("Error al ejecutar el comando");
    exit(EXIT_FAILURE);
  }

  if (pid == 0) {
    execl(command, command, arg[2], NULL);
  } else {
    waitpid(pid, NULL, 0);
    exit(EXIT_SUCCESS);
  }
}

int main(int argc, char *argv[]) {
  if (argc > 1) {
    if (strcmp(argv[1], "cpu") == 0) {
      if (argc == 3) {
        // Se ejecta el programa CPU con el argumento PID
        main_arguments(BIN_CPU, argv);
      } else if (argc == 2) {
        // Se ejecuta el programa CPU
        main_not_arguments(BIN_CPU, argv);
      }
    } else if (strcmp(argv[1], "disco") == 0) {
      if (argc == 3) {
        if (strcmp(argv[2], "-tm") == 0) {
          // Se ejecuta el programa DISCO con el argumento -tm
          main_arguments(BIN_DISK, argv);
        }
        if (strcmp(argv[2], "-tg") == 0) {
          // Se ejecuta el programa DISCO con el argumento -tg
          main_arguments(BIN_DISK, argv);
        }
      } else if (argc == 2) {
        // Se ejecuta el programa DISCO
        main_not_arguments(BIN_DISK, argv);
      }
    } else {
      fprintf(stderr, "Uso: %s [cpu] [PID opcional]\n", argv[0]);
      fprintf(stderr, "Uso: %s [disco [-tm | -tg]\n", argv[0]);
      fprintf(stderr, "Uso: %s [memoria] [-r | -v] [PID opcional]\n", argv[0]);
      return EXIT_FAILURE;
    }
  } else {
    fprintf(stderr, "Uso: %s [cpu] [PID opcional]\n", argv[0]);
    fprintf(stderr, "Uso: %s [disco [-tm | -tg]\n", argv[0]);
    fprintf(stderr, "Uso: %s [memoria] [-r | -v] [PID opcional]\n", argv[0]);
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}