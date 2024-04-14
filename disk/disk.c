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

void disk_show_in_gib(const disk_t *disk) {
  double total, used, free;
  convert(disk, &total, &used, &free, 2);
  printf("+------------------------------------------+\n");
  printf("| %4s | %4s | %-s  |\n", "Usado (GiB)", "Libre (GiB)", "Total (GiB)");
  printf("+-------------+-------------+--------------+\n");
  printf("| %-11.2f | %-11.2f | %-12.2f |\n", used, free, total);
  printf("+------------------------------------------+\n");
}

void disk_show_in_mib(const disk_t *disk) {
    double total, used, free;
    convert(disk, &total, &used, &free, 1);
    printf("+------------------------------------------+\n");
    printf("| %4s | %4s | %-s  |\n", "Usado (MiB)", "Libre (MiB)", "Total (MiB)");
    printf("+-------------+-------------+--------------+\n");
    printf("| %-11.2f | %-11.2f | %-12.2f |\n", used, free, total);
    printf("+------------------------------------------+\n");
}

void disk_show_percentage(const disk_t *disk) {
    float used_percentage = (float)(disk->total - disk->free ) / disk->total * 100;
    float free_percentage = (float)disk->free / disk->total * 100;
    double totalGiB =  disk->total / 1073741824.0;
    char auxGib[20];
    sprintf(auxGib, "%.2f GiB", totalGiB);
    printf("+--------------------------------+\n");
    printf("| %-7s | %-7s | %-9s  |\n", "Usado", "Libre", "Total");
    printf("+---------+---------+------------+\n");
    printf("| %-6.2f%% | %-6.2f%% | %-10s |\n", used_percentage, free_percentage, auxGib);
    printf("+--------------------------------+\n");
   
}

void convert(const disk_t *disk, double *total, double *used, double *free, int unit) {
    const double toMiB = 1048576.0;  // 1024*1024
    const double toGiB = 1073741824.0;  // 1024*1024*1024

    switch (unit) {
        case 1:  // MiB
            *total = disk->total / toMiB;
            *used = (disk->total - disk->free ) / toMiB;
            *free = disk->free / toMiB;
            break;
        case 2:  // GiB
            *total = disk->total / toGiB;
            *used = (disk->total - disk->free ) / toGiB;
            *free = disk->free / toGiB;
            break;
    }
}