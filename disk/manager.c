#include "./manager.h"

void manager_execute(char *arg) {
  pid_t pid;
  int data[2];

  if (pipe(data) == -1) {
    perror("Error to execute command");
    exit(EXIT_FAILURE);
  }

  pid = fork();
  if (pid < 0) {
    perror("Error to execute command");
    exit(EXIT_FAILURE);
  }

  if (pid == 0) {
    close(data[0]);
    disk_t disk = disk_get_data("/");
    write(data[1], &disk, sizeof(disk));
    close(data[1]);
  } else {
    waitpid(pid, NULL, 0);
    close(data[1]);
    disk_t read_pipe;
    read(data[0], &read_pipe, sizeof(read_pipe));
    if ((strcmp(arg, "-tm") == 0)) {
      disk_show_in_mib(&read_pipe);
    } else if ((strcmp(arg, "-tg") == 0)) {
      disk_show_in_gib(&read_pipe);
    } else {
      disk_show_percentage(&read_pipe);
    }
    close(data[0]);
  }
}

int main(int argc, char *argv[]) {

  if (argc == 2) {
    if (strcmp(argv[1], "-tm") == 0) {
      manager_execute(argv[1]);
    } else if (strcmp(argv[1], "-tg") == 0) {
      manager_execute(argv[1]);
    }
  } else if (argc == 1) {
    manager_execute("");
  } else {
    fprintf(stderr, "Uso: %s disco [-tm | -tg]\n", argv[0]);
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}