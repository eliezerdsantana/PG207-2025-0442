/*
 * Programacion para mecatronicos
 * Nombre: Eliezer Daniels Santana
 * Matricula: 2025-0442
 * Seccion: Miercoles
 * Practica: PG207 - Embalaje secuencial de una mudanza
 * Fecha: 07/11/2026
 * Link practica: https://github.com/eliezerdsantana/PG207-2025-0442
 * Archivo: reto.h
 */

#ifndef RETO_H
#define RETO_H

/* Capacidades maximas fijadas por el enunciado. */
#define MAX_REGISTROS 20
#define MAX_OBJETOS 8
#define MAX_NOMBRE 15

/* Configuracion independiente de cada registro. */
typedef struct {
    int tipo; /* 0: orden original; 1: orden inverso. */
    int p;    /* La capacidad de cada caja es p + 100. */
} Configuracion;

/* Identidad, configuracion y resultados de una unidad. */
typedef struct {
    int id;
    char nombre[MAX_NOMBRE + 1]; /* Un espacio adicional para '\0'. */
    Configuracion config;
    int score;  /* Cantidad de cajas utilizadas. */
    int estado; /* 1 si alguna caja quedo exactamente llena; 0 en otro caso. */
} Registro;

int calcular(const int pesos[], int m, int tipo, int p,
              char nombre[], int *estado);

int total_rec(const Registro registros[], int n);

void ordenar(Registro datos[], int n);
void ordenar_por_id(Registro datos[], int n);
int buscar(const Registro datos[], int n, int q);

#endif
