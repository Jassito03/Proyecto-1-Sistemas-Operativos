EJ = bin/programa bin/cpu bin/disco bin/memoria install
INSTALL_PROGRAMS = install_cpu install_disco install_memoria

#Variables para CPU
INCLUDE_CPU = -Icpu
CPU_OBJS_PATH = objs/cpu/
CPU_OBJS = $(CPU_OBJS_PATH)cpu.o $(CPU_OBJS_PATH)manager.o

#Variables para MEMORY
INCLUDE_MEMORY = -Imemory
MEMORY_OBJS_PATH = objs/memory/
MEMORY_OBJS = $(MEMORY_OBJS_PATH)memory.o

#Variables para DISK
INCLUDE_DISK = -Idisk
DISK_OBJS_PATH = objs/disk/
DISK_OBJS = $(DISK_OBJS_PATH)disk_t.o $(DISK_OBJS_PATH)disk.o $(DISK_OBJS_PATH)manager.o

all: $(EJ)

#Quitar este make
bin: bin/programa bin/cpu bin/disco bin/memoria

#Compila MAIN
bin/programa: objs/main.o
	gcc objs/main.o -o bin/programa
objs/main.o:
	gcc -c main.c -o objs/main.o

#Compila CPU
bin/cpu: $(CPU_OBJS)
	gcc $(CPU_OBJS) -o bin/cpu

objs/cpu/cpu.o:
	gcc -c $(INCLUDE_CPU) cpu/cpu.c -o $(CPU_OBJS_PATH)cpu.o

objs/cpu/manager.o:
	gcc -c $(INCLUDE_CPU) cpu/manager.c -o $(CPU_OBJS_PATH)manager.o

#Compila DISK
bin/disco: $(DISK_OBJS)
	gcc $(DISK_OBJS) -o bin/disco

objs/disk/disk_t.o:
	gcc -c $(INCLUDE_DISK) disk/disk_t.c -o $(DISK_OBJS_PATH)disk_t.o

objs/disk/disk.o:
	gcc -c $(INCLUDE_DISK) disk/disk.c -o $(DISK_OBJS_PATH)disk.o

objs/disk/manager.o:
	gcc -c $(INCLUDE_DISK) disk/manager.c -o $(DISK_OBJS_PATH)manager.o

#Compila MEMORY
objs/memory/memory.o:
	gcc -c $(INCLUDE_MEMORY) memory/memory.c -o $(MEMORY_OBJS_PATH)memory.o

clean: clean/objs clean/bin
clean/objs:
	find ./objs -type f -name "*.o" -exec rm {} \;
clean/bin:
	rm ./bin/programa ./bin/cpu ./bin/disco ./bin/memoria

install: $(INSTALL_PROGRAMS)
	sudo install -m 0755 bin/programa $(DESTDIR)/usr/local/bin/programa

install_cpu:
	sudo install -m 0755 bin/cpu $(DESTDIR)/usr/local/bin/cpu

install_disco:
	sudo install -m 0755 bin/disco $(DESTDIR)/usr/local/bin/disco

install_memoria:
	sudo install -m 0755 bin/memoria $(DESTDIR)/usr/local/bin/memoria

uninstall: clean
	sudo find /usr/local/bin -type f -name programa -exec rm {} \;
	sudo find /usr/local/bin -type f -name cpu -exec rm {} \;
	sudo find /usr/local/bin -type f -name disco -exec rm {} \;
	sudo find /usr/local/bin -type f -name memoria -exec rm {} \;