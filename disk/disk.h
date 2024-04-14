#ifndef DISK_H
#define DISK_H

#include "./disk_t.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/statvfs.h>

disk_t disk_get_data(const char *);
void disk_show_in_gib(const disk_t *);
void disk_show_in_mib(const disk_t *);
void disk_show_percentage(const disk_t *);
void convert(const disk_t *, double *, double *, double *, int);

#endif // DISK_H