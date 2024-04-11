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

    if (strcmp(argv[1], "cpu") == 0) {
      if (argc == 2) {
        pid = fork();
        if (pid < 0) {
          perror("Error al ejecutar el comando");
          exit(EXIT_FAILURE);
        }

        if (pid == 0) {
          close(data[0]);
          float cpu_usage = cpu_total_usage(argv[2]);
          write(data[1], &cpu_usage, sizeof(cpu_usage));
          close(data[1]);
        } else {
          waitpid(pid, NULL, 0);
          close(data[1]);
          float read_pipe;
          read(data[0], &read_pipe, sizeof(read_pipe));
          cpu_show_usage(read_pipe);
          close(data[0]);
        }
      } else if (argc == 3) {
        pid = fork();
        if (pid < 0) {
          perror("Error al ejecutar el comando");
          exit(EXIT_FAILURE);
        }

        if (pid == 0) {
          close(data[0]);
          float cpu_usage = cpu_usage_pid_in_5_min(argv[2]);
          write(data[1], &cpu_usage, sizeof(cpu_usage));
          close(data[1]);
        } else {
          waitpid(pid, NULL, 0);
          close(data[1]);
          float read_pipe;
          read(data[0], &read_pipe, sizeof(read_pipe));
          cpu_show_usage_pid_in_5_min(argv[2], read_pipe);
          close(data[0]);
        }
      } else {
        fprintf(stderr, "Opción no reconocida. Uso: %s cpu [PID opcional]\n", argv[0]);
        return EXIT_FAILURE;
      }
    }
  } else {
    fprintf(stderr, "Uso: %s cpu [PID opcional]\n", argv[0]);
    return EXIT_FAILURE;
  }
  return 0;
}
