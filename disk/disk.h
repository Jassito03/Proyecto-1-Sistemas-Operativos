#ifndef DISK_H
#define DISK_H

#include "./disk_t.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/statvfs.h>

disk_t disk_get_data(const char *);
void disk_show_tg(float, float, float);
void disk_show_tm(float, float, float);
void disk_show_percentage(float, float, float);

#endif // DISK_H