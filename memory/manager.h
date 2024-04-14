#include "./memory.h"
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int, char *[]);

void show_virtual_memory_usage_all(int *);
void show_real_memory_usage_all(int *);
void show_memory_usage_pid(char *, char *, int *);