#include "memoria.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINEA_TAM 256
#define BUFFER_TAM 256

unsigned long obtenerMemoriaTotal() {
  FILE *file = fopen("/proc/meminfo", "r");
  if (!file) {
    perror("Error al ejeccutar el comando");
    return 0;
  }

  char linea[LINEA_TAM];
  unsigned long memoriaTotal = 0;
  while (fgets(linea, sizeof(linea), file)) {
    if (sscanf(linea, "MemTotal: %lu kB", &memoriaTotal) == 1) {
      break;
    }
  }
  fclose(file);
  return memoriaTotal;
}

void leerInformacionProceso(const char *pid, const char *tipoMemoria, unsigned long memoriaTotal) {
  char path[BUFFER_TAM], linea[LINEA_TAM], nombre[BUFFER_TAM] = "";
  snprintf(path, sizeof(path), "/proc/%s/status", pid);
  FILE *file = fopen(path, "r");
  if (!file) {
    fprintf(stderr, "Error al abrir %s\n", path);
    return;
  }

  unsigned long memoria = 0;
  while (fgets(linea, sizeof(linea), file)) {
    if (strncmp(linea, "Name:", 5) == 0) {
      sscanf(linea, "Name:\t%255s", nombre);
    } else if (strncmp(linea, tipoMemoria, strlen(tipoMemoria)) == 0) {
      sscanf(linea, "%*s %lu", &memoria);
      double porcentajeMemoria = (memoria / 1024.0) * 100.0 / (memoriaTotal / 1024.0);
      printf("| %-9s | %-25.25s | %11.2f |\n", pid, nombre, porcentajeMemoria);
      break;
    }
  }
  fclose(file);
}

void mostrarUsoMemoria(const char *tipoMemoria) {
  unsigned long memoriaTotal = obtenerMemoriaTotal();
  printf("| %-9s | %-25s | %-11s  |\n", "PID", "Nombre", "Memoria (%)");
  printf("|------------------------------------------------------|\n");
  DIR *dir = opendir("/proc");
  if (!dir) {
    perror("Error al abrir /proc");
    return;
  }

  struct dirent *entrada;
  while ((entrada = readdir(dir)) != NULL) {
    if (entrada->d_type == DT_DIR && strtol(entrada->d_name, NULL, 10) > 0) {
      leerInformacionProceso(entrada->d_name, tipoMemoria, memoriaTotal);
    }
  }
  closedir(dir);
}

void mostrarUsoMemoriaVirtual() {
  printf("|------------------------------------------------------|\n");
  mostrarUsoMemoria("VmSize:");
  printf("|------------------------------------------------------|\n");
}

void mostrarUsoMemoriaReal() {
  printf("|------------------------------------------------------|\n");
  mostrarUsoMemoria("VmRSS:");
  printf("|------------------------------------------------------|\n");
}

void mostrarUsoMemoriaVirtualPid(const char *pid) {
  unsigned long memoriaTotal = obtenerMemoriaTotal();
  printf("|------------------------------------------------------|\n");
  printf("| %-9s | %-25s | %-8s  |\n", "PID", "Nombre", "Memoria (%)");
  printf("|-----------|---------------------------|--------------|\n");
  leerInformacionProceso(pid, "VmSize:", memoriaTotal);
  printf("|------------------------------------------------------|\n");
}

void mostrarUsoMemoriaRealPid(const char *pid) {
  unsigned long memoriaTotal = obtenerMemoriaTotal();
  printf("|------------------------------------------------------|\n");
  printf("| %-9s | %-25s | %-8s  |\n", "PID", "Nombre", "Memoria (%)");
  printf("|------------------------------------------------------|\n");
  leerInformacionProceso(pid, "VmRSS:", memoriaTotal);
  printf("|------------------------------------------------------|\n");
}
