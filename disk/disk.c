#include "./disk.h"

disk_t disk_get_data(const char *puntoMontaje) {
  struct statvfs buf;

  if (statvfs(puntoMontaje, &buf) != 0) {
    perror("statvfs error");
    exit(EXIT_FAILURE);
  }

  unsigned long long total = buf.f_blocks * buf.f_frsize;
  unsigned long long free = buf.f_bfree * buf.f_frsize;
  unsigned long long used = total - free;

  return disk_t_init(total, free, used);
}

void disk_show_tg(float total, float used, float free) {
  printf("Total: %.2f GiB\n", total / 1024.0 / 1024.0 / 1024.0);
  printf("Used: %.2f GiB\n", used / 1024.0 / 1024.0 / 1024.0);
  printf("Free: %.2f GiB\n", free / 1024.0 / 1024.0 / 1024.0);
}

void disk_show_tm(float total, float used, float free) {
  printf("Total: %.2f MiB\n", total / 1024.0 / 1024.0);
  printf("Used: %.2f MiB\n", used / 1024.0 / 1024.0);
  printf("Free: %.2f MiB\n", free / 1024.0 / 1024.0);
}

void disk_show_percentage(float total, float used_percentage, float free_percentage) {
  printf("Total: %.2f GiB\n", total / 1024.0 / 1024.0 / 1024.0);
  printf("Used Percentage: %.2f%%\n", used_percentage);
  printf("Free Percentage: %.2f%%\n", free_percentage);
}
