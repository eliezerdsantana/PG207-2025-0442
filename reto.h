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

int total_rec(const Registro registros[], int n);

void ordenar(Registro datos[], int n);
void ordenar_por_id(Registro datos[], int n);
int buscar(const Registro datos[], int n, int q);

#endif