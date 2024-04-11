#include "./manager.h"

void manager_execute(char *arg) {
  pid_t pid;
  int data[2];

  if (pipe(data) == -1) {
    perror("Error al ejecutar el comando");
    exit(EXIT_FAILURE);
  }

  pid = fork();
  if (pid < 0) {
    perror("Error al ejecutar el comando");
    exit(EXIT_FAILURE);
  }

  if (pid == 0) {
    close(data[0]);
    float cpu_usage = cpu_total_usage();
    write(data[1], &cpu_usage, sizeof(cpu_usage));
    close(data[1]);
  } else {
    waitpid(pid, NULL, 0);
    close(data[1]);
    float read_pipe;
    read(data[0], &read_pipe, sizeof(read_pipe));
    if ((strcmp(arg, "/") == 0)) {
      cpu_show_usage(read_pipe);
    } else {
      cpu_show_usage_pid_in_5_min(arg, read_pipe);
    }
    close(data[0]);
  }
}

int main(int argc, char *argv[]) {
  if (argc == 2) {
    manager_execute(argv[1]);
  } else if (argc == 1) {
    manager_execute("/");
  } else {
    fprintf(stderr, "Uso: %s cpu [PID opcional]\n", argv[0]);
    return EXIT_FAILURE;
  }
  return 0;
}
