#Variables para CPU
#include_cpu = -Icpu
#cpu_objs_path = objs/cpu/
#cpu_objs = $(cpu_objs_path)cmanager.o $(cpu_objs_path)cpu_t.o

#Compila CPU
#bin/cpu: $(cpu_objs)
#	gcc $(cpu_objs) -o bin/cpu
#objs/cpu/cmanager.o:
#	gcc -c $(include_cpu) cpu/cmanager.c -o $(cpu_objs_path)cmanager.o
#objs/cpu/cpu_t.o:
#	gcc -c $(include_cpu) cpu/cpu_t.c -o $(cpu_objs_path)cpu_t.o

#Variables para MEMORY
include_memory = -Imemory
memory_objs_path = objs/memory/
memory_objs = $(memory_objs_path)memory.o

#Variables para DISK
include_disk = -Idisk
disk_objs_path = objs/disk/
disk_objs = $(disk_objs_path)disk.o

#Compila MAIN
bin/main: $(memory_objs) $(disk_objs) objs/main.o
	gcc $(memory_objs) $(disk_objs) objs/main.o -o bin/main
objs/main.o:
	gcc -c main.c -o objs/main.o

#Compila MEMORY
objs/memory/memory.o:
	gcc -c $(include_memory) memory/memory.c -o $(memory_objs_path)memory.o

#Compila DISK
objs/disk/disk.o:
	gcc -c $(include_disk) disk/disk.c -o $(disk_objs_path)disk.o

clean: clean/objs clean/bin
clean/objs:
	find ./objs -type f -name "*.o" -exec rm {} \;
clean/bin:
	rm ./bin/main