#include "disco.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_TAM 1024
#define NOMBRE_DISCO_TAM 256
#define COMANDO_TAM 128

const double MB_A_MIB = 1.048576;
const double GB_A_GIB = 1.073741824;

void ejecutarYMostrarResultados(const char *comando, const char *flag);
void mostrarEstadisticas(const char *nombreDisco, double espacioTotal, double espacioUsado, const char *unidad, double convertido);
void mostrarEstadisticasPorDefecto(const char *nombreDisco, char *porcentajeUtilizadoStr);

void mostrarEstadisticasDisco(const char *opcion) {
    const char *unidad = strcmp(opcion, "-tm") == 0 ? "MiB" : "GiB";
    double conversion = strcmp(opcion, "-tm") == 0 ? MB_A_MIB : GB_A_GIB;
    char comando[COMANDO_TAM];

    if (strcmp(opcion, "-tm") == 0) {
        snprintf(comando, sizeof(comando), "df -h --block-size=1M --output=source,size,used | grep '^/'");
    } else if (strcmp(opcion, "-tg") == 0) {
        snprintf(comando, sizeof(comando), "df -h --block-size=1G --output=source,size,used | grep '^/'");
    } else {
        snprintf(comando, sizeof(comando), "df -h --block-size=1G --output=source,pcent | grep '^/'");
    }

    ejecutarYMostrarResultados(comando, opcion);
}

void ejecutarYMostrarResultados(const char *comando, const char *opcion) {
    FILE *file = popen(comando, "r");
    if (file == NULL) {
        printf("No fue posible ejecutar el comando\n");
        exit(EXIT_FAILURE);
    }

    char resultado[BUFFER_TAM];
    fgets(resultado, sizeof(resultado), file);

    while (fgets(resultado, sizeof(resultado), file) != NULL) {
        char nombreDisco[NOMBRE_DISCO_TAM];
        if (strcmp(opcion, "-tm") == 0 || strcmp(opcion, "-tg") == 0) {
            int espacioTotal, espacioUsado;
            if(sscanf(resultado, "%s %d %d", nombreDisco, &espacioTotal, &espacioUsado) == 3) {
                double conversion = strcmp(opcion, "-tm") == 0 ? MB_A_MIB : GB_A_GIB;
                mostrarEstadisticas(nombreDisco, espacioTotal, espacioUsado, strcmp(opcion, "-tm") == 0 ? "MiB" : "GiB", conversion);
            } else {
                printf("Error al parsear la línea: %s\n", resultado);
            }
        } else {
            char porcentajeUtilizadoStr[NOMBRE_DISCO_TAM];
            if(sscanf(resultado, "%s %s", nombreDisco, porcentajeUtilizadoStr) == 2) {
                mostrarEstadisticasPorDefecto(nombreDisco, porcentajeUtilizadoStr);
            } else {
                printf("Error al parsear la línea: %s\n", resultado);
            }
        }
    }

    pclose(file);
}

void mostrarEstadisticas(const char *nombreDisco, double espacioTotal, double espacioUsado, const char *unidad, double conversion) {
    double espacioTotalConv = espacioTotal / conversion;
    double espacioUsadoConv = espacioUsado / conversion;
    double espacioLibre = espacioTotalConv - espacioUsadoConv;
    printf("|------------------------------------------------------------------|\n");
    printf("| %-12s | %-14s | %-14s | %-15s |\n", "Nombre", "Utilizado", "Libre", "Total");
    printf("| %-11s  | %-10.2f %s | %-10.2f %s | %-11.2f %s |\n", nombreDisco, espacioUsado, unidad, espacioLibre, unidad, espacioTotal, unidad);
    printf("|------------------------------------------------------------------|\n");
}

void mostrarEstadisticasPorDefecto(const char *nombreDisco, char *porcentajeUtilizadoStr) {
    porcentajeUtilizadoStr[strcspn(porcentajeUtilizadoStr, "%")] = '\0'; // quita el % de la variable

    float porcentajeUtilizado = atof(porcentajeUtilizadoStr);
    float porcentajeLibre = 100.0 - porcentajeUtilizado;

    printf("|------------------------------------------------|\n");
    printf("| %-12s | %-9s | %-9s | %-7s |\n", "Nombre", "Utilizado", "Libre", "Total");
    printf("| %-11s  | %8.2f% | %8.2f% | %6s  |\n", nombreDisco, porcentajeUtilizado, porcentajeLibre, "100%");
    printf("|------------------------------------------------|\n");
}
