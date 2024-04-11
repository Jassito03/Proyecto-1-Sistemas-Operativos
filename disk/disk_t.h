#include <stdio.h>
#include <stdlib.h>
#include <sys/statvfs.h>

typedef struct disk_t {
  float total;
  float free;
  float usage;
  float used_percentage;
  float free_percentage;
} disk_t;

disk_t disk_t_init(float, float, float);
