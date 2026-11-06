#include <stdio.h>
#include "reto.h"

int main(void) {
    int n, m, q;
    Registro registros[MAX_REGISTROS];
    int muestras[MAX_REGISTROS][MAX_OBJETOS];
    int i, j, k;

    if (scanf("%d %d %d", &n, &m, &q) != 3) {
        printf("ERROR\n");
        return 0;
    }
    
    if (n < 1 || n > MAX_REGISTROS || 
        m < 1 || m > MAX_OBJETOS || q < 1 || q > 9999) {
        printf("ERROR\n");
        return 0;
    }

    for (i = 0; i < n; i++) {
        if (scanf("%d %15s %d %d", 
                  &registros[i].id, registros[i].nombre, 
                  &registros[i].config.tipo,
                  &registros[i].config.p) != 4) {
            printf("ERROR\n");
            return 0;
        }
        
        if (registros[i].id < 1 || registros[i].id > 9999 || 
            (registros[i].config.tipo != 0 &&
             registros[i].config.tipo != 1) ||
            registros[i].config.p < 0 || registros[i].config.p > 100) {
            printf("ERROR\n");
            return 0;
        }

        for (k = 0; k < i; k++) {
            if (registros[i].id == registros[k].id) {
                printf("ERROR\n");
                return 0;
            }
        }

        for (j = 0; j < m; j++) {
            if (scanf("%d", &muestras[i][j]) != 1 ||
                muestras[i][j] < 0 || muestras[i][j] > 100) {
                printf("ERROR\n");
                return 0;
            }
        }
    }

    /* pendinte: calcular y mostrar los resultados*/
    return 0;
}