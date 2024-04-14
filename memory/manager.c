#include "./manager.h"

int main(int argc, char *argv[]) {
    if (argc > 1) {
        int data[2];
        if (pipe(data) == -1) {
            perror("Error to create PIPE");
            exit(EXIT_FAILURE);
        }

            if (strcmp(argv[1], "-v") == 0) {
                if (argc == 2) {
                    show_virtual_memory_usage_all(data);
                } else if (argc == 3) {
                    show_memory_usage_pid(argv[2], "VmSize:", data);
                }
            } else if (strcmp(argv[1], "-r") == 0) {
                if (argc == 2) {
                    show_real_memory_usage_all(data);
                } else if (argc == 3) {
                    show_memory_usage_pid(argv[2], "VmRSS:", data);
                }
            } else {
                fprintf(stderr, "Opción no reconocida. Uso: %s memoria [-v | -r] [PID opcional]\n", argv[0]);
                return EXIT_FAILURE;
            }
            return EXIT_SUCCESS;
        }

    return EXIT_SUCCESS;
}

void show_memory_usage_pid(char *pid,char *memory_type, int *pipe_fd) {
    pid_t child_pid = fork();
    if (child_pid == 0) {
        close(pipe_fd[0]);
        memory_t memory = memory_usage_pid(pid, memory_type);
        write(pipe_fd[1], &memory, sizeof(memory));
        close(pipe_fd[1]);
        exit(EXIT_SUCCESS);
    } else if (child_pid > 0) {
        close(pipe_fd[1]);
        waitpid(child_pid, NULL, 0);
        memory_t read_pipe;
        read(pipe_fd[0], &read_pipe, sizeof(read_pipe));
        memory_show_pid(read_pipe);
        close(pipe_fd[0]);
    } else {
        perror("Error to execute fork");
        exit(EXIT_FAILURE);
    }
}

void show_real_memory_usage_all(int *pipe_fd) {
    pid_t pid = fork();
    if (pid == 0) {
        close(pipe_fd[0]);
        memory_show_all_process(pipe_fd[1], "VmRSS:");
        close(pipe_fd[1]);
        exit(EXIT_SUCCESS);
    } else if (pid > 0) {
        close(pipe_fd[1]);
        char buffer[1024];
        int nbytes;
        while ((nbytes = read(pipe_fd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[nbytes] = '\0'; 
            printf("%s", buffer);
        }

        close(pipe_fd[0]);
        waitpid(pid, NULL, 0);
    } else {
        perror("Error to execute fork");
        exit(EXIT_FAILURE);
    }
}

void show_virtual_memory_usage_all(int *pipe_fd) {
    memory_t *memory;
    pid_t pid = fork();
    if (pid == 0) {
        close(pipe_fd[0]);
        memory_show_all_process(pipe_fd[1], "VmSize:");
        close(pipe_fd[1]);
        exit(EXIT_SUCCESS);
    } else if (pid > 0) {
        close(pipe_fd[1]);
        char buffer[1024];
        int nbytes;
        while ((nbytes = read(pipe_fd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[nbytes] = '\0'; 
            printf("%s", buffer);
        }
        close(pipe_fd[0]);
        waitpid(pid, NULL, 0);
    } else {
        perror("Error to execute fork");
        exit(EXIT_FAILURE);
    }
}