#ifndef RETO_H
#define RETO_H

#define MAX_REGISTROS 20
#define MAX_OBJETOS 8
#define MAX_NOMBRE 15

typedef struct {
    int tipo;
    int p;
} Configuracion;

typedef struct {
    int id;
    char nombre[MAX_NOMBRE + 1];
    Configuracion config;
    int score;
    int estado;
} Registro;

int calcular(const int pesos[], int m, int tipo, int p,
              char nombre[], int *estado);

#endif