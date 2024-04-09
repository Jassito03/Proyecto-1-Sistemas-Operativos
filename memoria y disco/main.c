#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "disco.h"
#include "memoria.h"
//Asi no se debe de trabajar el main esto es solo para ver si funcionaban los 
//subprogramas
int main(int argc, char *argv[]) {
    if (argc > 1) {
        if (strcmp(argv[1], "disco") == 0) {
            if (argc == 3) {
                // Pasamos la opción -tm o -tg a mostrarEstadisticasDisco
                mostrarEstadisticasDisco(argv[2]);
            } else {
                // Sin argumentos adicionales, pasamos una cadena vacía
                mostrarEstadisticasDisco("");
            }
            return EXIT_SUCCESS; // Finaliza después de manejar 'disco'
        } else if (strcmp(argv[1], "memoria") == 0) {
            if (argc == 3) {
                // Muestra la información de memoria para todos los procesos
                if (strcmp(argv[2], "-v") == 0) {
                    mostrarUsoMemoriaVirtual();
                } else if (strcmp(argv[2], "-r") == 0) {
                    mostrarUsoMemoriaReal();
                } else {
                    fprintf(stderr, "Opción no reconocida. Uso: %s memoria [-v | -r]\n", argv[0]);
                    return EXIT_FAILURE;
                }
            } else if (argc == 4) {
                // Muestra la información de memoria para un PID específico
                if (strcmp(argv[2], "-v") == 0) {
                    mostrarUsoMemoriaVirtualPid(argv[3]);
                } else if (strcmp(argv[2], "-r") == 0) {
                    mostrarUsoMemoriaRealPid(argv[3]);
                } else {
                    fprintf(stderr, "Opción no reconocida. Uso: %s memoria [-v | -r] [PID]\n", argv[0]);
                    return EXIT_FAILURE;
                }
            } else {
                fprintf(stderr, "Uso incorrecto. Uso: %s memoria [-v | -r] [PID opcional]\n", argv[0]);
                return EXIT_FAILURE;
            }
            return EXIT_SUCCESS;
        } else {
            fprintf(stderr, "Comando no reconocido. Uso: %s [disco | memoria] [opciones] [PID opcional]\n", argv[0]);
            return EXIT_FAILURE;
        }
    } else {
        fprintf(stderr, "Uso: %s [disco | memoria] [opciones] [PID opcional]\n", argv[0]);
        return EXIT_FAILURE;
    }
}
