#include <stdio.h>
#include <string.h>
#include "reto.h"

int main(void) {
    int n, m, q;
    Registro registros[MAX_REGISTROS];
    Registro ordenados[MAX_REGISTROS];
    Registro por_id[MAX_REGISTROS];
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

    int total = total_rec(registros, n);
    double media = total / (double)n;
    (void)media;
    printf("TOTAL %d\n", total);

    for (i = 0; i < n; i++) {
        ordenados[i] = registros[i];
    }

    ordenar(ordenados, n);

    printf("ORDER");
    for (i = 0; i < n; i++) {
        printf(" %d", ordenados[i].id);
    }
    printf("\n");

    for (i = 0; i < n; i++) {
        por_id[i] = registros[i];
    }

    ordenar_por_id(por_id, n);

    int posicion = buscar(por_id, n, q);

    if (posicion == -1) {
        printf("FIND %d -1\n", q);
    } else {
        printf("FIND %d %d\n", q, por_id[posicion].score);
    }

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

int total_rec(const Registro registros[], int n) {
    if (n == 0) {
        return 0;
    }

    return registros[n - 1].score + total_rec(registros, n - 1);
}

void ordenar(Registro datos[], int n) {
    int i, j, mejor;
    Registro auxiliar;

    for (i = 0; i < n - 1; i++) {
        mejor = i;

        for (j = i + 1; j < n; j++) {
            if (datos[j].score > datos[mejor].score ||
                (datos[j].score == datos[mejor].score &&
                 datos[j].id < datos[mejor].id)) {
                mejor = j;
            }
        }

        if (mejor != i) {
            auxiliar = datos[i];
            datos[i] = datos[mejor];
            datos[mejor] = auxiliar;
        }
    }
}

void ordenar_por_id(Registro datos[], int n) {
    int i, j, menor;
    Registro auxiliar;

    for (i = 0; i < n - 1; i++) {
        menor = i;

        for (j = i + 1; j < n; j++) {
            if (datos[j].id < datos[menor].id) {
                menor = j;
            }
        }

        if (menor != i) {
            auxiliar = datos[i];
            datos[i] = datos[menor];
            datos[menor] = auxiliar;
        }
    }
}

int buscar(const Registro datos[], int n, int q) {
    int inicio = 0;
    int fin = n - 1;

    while (inicio <= fin) {
        int medio = (inicio + fin) / 2;

        if (datos[medio].id == q) {
            return medio;
        }


        if (q < datos[medio].id) {
            fin = medio - 1;
        } else {
            inicio = medio + 1;
        }
    }

    return -1;
}