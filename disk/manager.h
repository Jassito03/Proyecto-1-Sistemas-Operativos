#ifndef MANAGER_H
#define MANAGER_H

#include "./disk.h"
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void manager_execute(char *);
int main(int, char *[]);

#endif // MANAGER_H