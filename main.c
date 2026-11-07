#include <stdio.h>
#include <string.h>
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

    for (i = 0; i < n; i++) {
        registros[i].score = calcular(
            muestras[i], m, 
            registros[i].config.tipo, registros[i].config.p, 
            registros[i].nombre, &registros[i].estado);

        printf("%d %s %d %d\n", 
            registros[i].id, registros[i].nombre, 
            registros[i].score, registros[i].estado);
    }

    /* Pendiente: TOTAL, ORDER y FIND. */
    return 0;
}

int calcular(const int pesos[], int m, int tipo, int p,
              char nombre[], int *estado) {
    int capacidad = p + 100;
    int carga = 0;
    int cajas = 1;
    int paso, posicion, letra;
    int longitud = (int)strlen(nombre);

    *estado = 0;

    for (letra = 0; letra < longitud; letra++) {
        if (nombre[letra] >= 'a' && nombre[letra] <= 'z') {
            nombre[letra] = (char)(nombre[letra] - 'a' + 'A');
        }
    }

    for (paso = 0; paso < m; paso++) {
        if (tipo == 0) {
            posicion = paso;
        } else {
            posicion = m - 1 - paso;
        }

        if (carga + pesos[posicion] > capacidad) {
            cajas++;
            carga = 0;
        }

        carga += pesos[posicion];

        if (carga == capacidad) {
            *estado = 1;
        }
    }

    return cajas;
}