#include "./memory_t.h"

memory_t *memory_t_create( char *_pid,  char _name[], float _usage_percentage) {
    memory_t *memory = malloc(sizeof(memory_t));
    if (!memory) return NULL; 

    strcpy(memory->pid, _pid);
    strcpy(memory->name, _name);
    memory->usage_percentage = _usage_percentage;
    return memory;
}

void memory_t_destroy(memory_t *memory){
    if (memory) {
        free(memory);
    }
}