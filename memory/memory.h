#ifndef MEMORY_H
#define MEMORY_H

void memory_show_virtual_usage();
void memory_show_real_usage();
void memory_usage_virtual_pid(const char *);
void memory_usage_real_pid(const char *);

#endif // MEMORY_H