#include "memory.h"

#define LINE_SIZE 256
#define BUFFER_SIZE 512

unsigned long memory_get_total() {
  FILE *file = fopen("/proc/meminfo", "r");
  if (!file) {
    perror("Error to execute command");
    return EXIT_FAILURE;
  }

  char line[LINE_SIZE];
  unsigned long total_memory = 0;
  while (fgets(line, sizeof(line), file)) {
    if (sscanf(line, "MemTotal: %lu kB", &total_memory) == 1) {
      break;
    }
  }
  fclose(file);
  return total_memory;
}

void memory_read_process_info(const char *pid, const char *memory_type, unsigned long total_memory, char *name, float *memory_usage_percent) {
    char path[BUFFER_SIZE];
    snprintf(path, sizeof(path), "/proc/%s/status", pid);
    FILE *file = fopen(path, "r");
    if (!file) {
        fprintf(stderr, "Failed to open %s\n", path);
        exit(EXIT_FAILURE);
    }

    char line[LINE_SIZE];
    unsigned long memory = 0;
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "Name:", 5) == 0) {
            sscanf(line, "Name:\t%255s", name);
        } else if (strncmp(line, memory_type, strlen(memory_type)) == 0) {
            sscanf(line, "%*s %lu", &memory);
            if (strcmp(memory_type, "VmSize:") == 0) {
               *memory_usage_percent = (float)(memory * 100.0 / total_memory);
            } else if (strcmp(memory_type, "VmRSS:") == 0) {
              *memory_usage_percent = (float)(memory / 1024.0 * 100.0 / (total_memory / 1024.0));
            }
            break;
        }
    }
    fclose(file);
}

void memory_free_data(memory_t **data, int count) {
    for (int i = 0; i < count; i++) {
        memory_t_destroy(data[i]);
    }
    free(data);
}

memory_t memory_usage_pid(char *pid, char *memory_type) {
    unsigned long total_memory = memory_get_total();
    char name[BUFFER_SIZE] = {0};
    float memory_usage_percent;
    memory_t memory;
    if (strcmp(memory_type, "VmRSS:") == 0){
       memory_read_process_info(pid, "VmRSS:", total_memory, name, &memory_usage_percent);
    }else{
       memory_read_process_info(pid, "VmSize:", total_memory, name, &memory_usage_percent);
    }
    strcpy(memory.pid, pid); 
    strcpy(memory.name, name);
    
    memory.usage_percentage = memory_usage_percent;
    return memory;
}

void memory_show_pid(memory_t memory){
    printf("+------------------------------------------------------+\n");
    printf("| %-9s | %-25s | %-8s  |\n", "PID", "Nombre", "Memoria (%)");
    printf("+-----------+---------------------------+--------------+\n");
    printf("| %-9s | %-25.25s | %11.2f%% |\n", memory.pid, memory.name, memory.usage_percentage);
    printf("+------------------------------------------------------+\n");
}

memory_t **memory_all_process(const char *memory_type, int *count) {
    DIR *dir = opendir("/proc");
    if (!dir) {
        perror("Error to open /proc");
        exit(EXIT_FAILURE);
    }

    struct dirent *entry;
    memory_t **memory_list = NULL;
    int n = 0;
    unsigned long total_memory = memory_get_total();

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR && strtol(entry->d_name, NULL, 10) > 0) {
            char process_name[BUFFER_SIZE];
            memset(process_name, 0, BUFFER_SIZE);
            float memory_usage_percent;
            memory_read_process_info(entry->d_name, memory_type, total_memory, process_name, &memory_usage_percent);
            memory_t *new_proc = memory_t_create(strdup(entry->d_name), strdup(process_name), memory_usage_percent);
            memory_list = realloc(memory_list, sizeof(memory_t *) * (n + 1));
            memory_list[n++] = new_proc;
        }
    }
    closedir(dir);
    *count = n;
    return memory_list;
}

void memory_show_all_process(int fd, const char *memory_type) {
    int count;
    memory_t **data = memory_all_process(memory_type, &count);
    if (data == NULL) return;

    printf("+------------------------------------------------------+\n");
    printf("| %-9s | %-25s | %-8s  |\n", "PID", "Nombre", "Memoria (%)");
    printf("+-----------+---------------------------+--------------+\n");
    for (int i = 0; i < count; i++) {
        dprintf(fd, "| %-9s | %-25.25s | %11.2f%% |\n" ,data[i]->pid, data[i]->name, data[i]->usage_percentage);
    }
    printf("+------------------------------------------------------+\n");
    memory_free_data(data, count);
}