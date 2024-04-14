#include "./cpu.h"

float cpu_total_usage() {
  FILE *file = fopen("/proc/stat", "r");
  unsigned long user, nice, system, idle, iowait, irq, softirq, steal;

  if (file == NULL) {
    perror("Error to execute command");
    exit(EXIT_FAILURE);
  }

  if (fscanf(file, "cpu %ld %ld %ld %ld %ld %ld %ld %ld", &user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal) != 8) {
    perror("Error to read /proc/stat");
    fclose(file);
    return -1;
  }
  fclose(file);
  return (100 - (100 * idle / (user + nice + system + idle + iowait + irq + softirq + steal)));
}

unsigned long cpu_total_time() {
  FILE *file = fopen("/proc/stat", "r");
  unsigned long user, nice, system, idle, iowait, irq, softirq, steal;

  if (file == NULL) {
    perror("Error to execute command");
    exit(EXIT_FAILURE);
  }

  if (fscanf(file, "cpu %ld %ld %ld %ld %ld %ld %ld %ld", &user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal) != 8) {
    perror("Error to read /proc/stat");
    fclose(file);
    return -1;
  }
  fclose(file);

  return user + nice + system + idle + iowait + irq + softirq + steal;
}

float cpu_usage_pid_in_5_min(const char *pid) {
  char procfile[300];
  FILE *file;
  unsigned long user_time, core_time, process_time_start, process_time_finish, cpu_time_start, cpu_time_finish, num_processors = sysconf(_SC_NPROCESSORS_ONLN);
  float total_process_cpu_time, total_cpu_time;

  char comando[300];
  snprintf(comando, sizeof(comando), "cat /proc/%s/stat | awk {'print $14, $15'}", pid);

  for (int i = 0; i < 5; i++) {
    file = popen(comando, "r");
    if (file == NULL) {
      perror("Error to execute command, Verify PID exists");
      exit(EXIT_FAILURE);
    }

    fscanf(file, "%lu %lu", &user_time, &core_time);
    fclose(file);

    if (i == 0) {
      cpu_time_start = cpu_total_time();
      process_time_start = user_time + core_time;
    }

    if (i == 4) {
      cpu_time_finish = cpu_total_time();
      process_time_finish = user_time + core_time;
    }

    sleep(1);
  }

  total_cpu_time = (cpu_time_finish - cpu_time_start) / (float)sysconf(_SC_CLK_TCK) / num_processors;
  total_process_cpu_time = (process_time_finish - process_time_start) / (float)sysconf(_SC_CLK_TCK);

  return (100 * total_process_cpu_time / total_cpu_time);
}

void cpu_show_usage_pid_in_5_min(const char *pid, float cpu_usage) {
  printf("La estimación de uso CPU para PID %s en los últimos 5 minutos es: %.2f%%\n", pid, cpu_usage);
}

void cpu_show_usage(float cpu_usage) {
  printf("El uso de CPU es: %.2f%%\n", cpu_usage);
}
