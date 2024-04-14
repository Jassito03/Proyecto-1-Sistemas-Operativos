#ifndef MEMORY_H
#define MEMORY_H

#include "memory_t.h"
#include <dirent.h>
#include <stdio.h>  
#include <string.h> 
#include <unistd.h> 

unsigned long memory_get_total();
void memory_read_process_info(const char *, const char *, unsigned long, char *, float *);
void memory_free_data(memory_t **, int);
memory_t memory_usage_pid(char *, char *);
void memory_show_pid(memory_t);
memory_t **memory_all_process(const char *, int *);
void memory_show_all_process(int, const char *);

#endif // MEMORY_H