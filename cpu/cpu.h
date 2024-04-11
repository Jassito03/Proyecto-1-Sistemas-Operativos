#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

double cpu_total_usage();
unsigned long cpu_total_time();
float cpu_usage_pid_in_5_min(const char *);
void cpu_show_usage_pid_in_5_min(const char *, float);
void cpu_show_usage(double);