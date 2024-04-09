#ifndef MEMORIA_H
#define MEMORIA_H

void memory_show_virtual_usage();
void memory_show_real_usage();
void memory_usage_virtual_pid(const char *pid);
void memory_usage_real_pid(const char *pid);

#endif // MEMORIA_H