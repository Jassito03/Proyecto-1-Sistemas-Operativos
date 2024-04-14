#ifndef MEMORY_T_H
#define MEMORY_T_H

#include <stdlib.h> 
#include <string.h> 

typedef struct memory_t {
  char pid[32];
  char name[255];
  float usage_percentage;
} memory_t;

memory_t *memory_t_create( char [],  char [], float);
void memory_t_destroy(memory_t *);

#endif // MEMORY_T_H