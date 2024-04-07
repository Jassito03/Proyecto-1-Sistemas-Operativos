#include <stdio.h>
#include <stdlib.h>
#include <sys/statvfs.h>
#include <string.h>
//Esta es otra manera de averiguar lo del disco
//usa esta libreria <sys/statvfs.h> y es mas facil
//no se cual manera hay que utilizar
void mostrarEstadisticasDisco(const char *puntoMontaje, const char *opcion) {
    struct statvfs buf;

    if (statvfs(puntoMontaje, &buf) != 0) {
        perror("statvfs error");
        exit(EXIT_FAILURE);
    }

    unsigned long long total = buf.f_blocks * buf.f_frsize;
    unsigned long long free = buf.f_bfree * buf.f_frsize;
    unsigned long long used = total - free;
    double usedPercentage = 100.0 * used / total;
    double freePercentage = 100.0 * free / total;

    if (strcmp(opcion, "-tg") == 0) {
        printf("Total: %.2f GiB\n", total / 1024.0 / 1024.0 / 1024.0);
        printf("Used: %.2f GiB\n", used / 1024.0 / 1024.0 / 1024.0);
        printf("Free: %.2f GiB\n", free / 1024.0 / 1024.0 / 1024.0);
    } else if (strcmp(opcion, "-tm") == 0) {
        printf("Total: %.2f MiB\n", total / 1024.0 / 1024.0);
        printf("Used: %.2f MiB\n", used / 1024.0 / 1024.0);
        printf("Free: %.2f MiB\n", free / 1024.0 / 1024.0);
    } else {
        printf("Used Percentage: %.2f%%\n", usedPercentage);
        printf("Free Percentage: %.2f%%\n", freePercentage);
    }
}

int main(int argc, char *argv[]) {
    const char *puntoMontaje = "/"; // Asumiendo el punto de montaje del sistema de archivos raíz
    const char *opcion = "";

    if (argc > 1) {
        opcion = argv[1];
    }

    mostrarEstadisticasDisco(puntoMontaje, opcion);

    return EXIT_SUCCESS;
}