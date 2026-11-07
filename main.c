/*
 * Programacion para mecatronicos
 * Nombre: Eliezer Daniels Santana
 * Matricula: 2025-0442
 * Seccion: Miercoles
 * Practica: PG207 - Embalaje secuencial de una mudanza
 * Fecha: 07/11/2026
 * Link practica: https://github.com/eliezerdsantana/PG207-2025-0442
 * Archivo: main.c
 */

#include <stdio.h>
#include <string.h>
#include "reto.h"

/**
 * @brief Lee y valida la entrada, calcula cada registro y muestra el informe.
 * No recibe parametros de funcion; los datos se leen de la entrada estandar.
 * Con datos invalidos imprime solo ERROR, sin resultados parciales.
 * @return 0 tanto al completar el informe como al detectar datos invalidos,
 * segun la terminacion normal que pide el enunciado.
 */
int main(void) {
    int n, m, q;
    Registro registros[MAX_REGISTROS];
    Registro ordenados[MAX_REGISTROS];
    Registro por_id[MAX_REGISTROS];
    int muestras[MAX_REGISTROS][MAX_OBJETOS];
    int i, j, k;

    /* Valido toda la entrada antes de imprimir las filas del informe. */
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

        /* Solo comparo con registros anteriores, que ya fueron leidos. */
        for (k = 0; k < i; k++) {
            if (registros[i].id == registros[k].id) {
                printf("ERROR\n");
                return 0;
            }
        }

        /* La fila i contiene los pesos de este registro. */
        for (j = 0; j < m; j++) {
            if (scanf("%d", &muestras[i][j]) != 1 ||
                muestras[i][j] < 0 || muestras[i][j] > 100) {
                printf("ERROR\n");
                return 0;
            }
        }
    }

    /* Proceso e imprimo los registros en su orden original. */
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
    /* La conversion a double permite conservar la parte decimal. */
    double media = total / (double)n;
    /* La media se documenta en el README y no se agrega a la salida. */
    (void)media;
    printf("TOTAL %d\n", total);

    /* ORDER trabaja con una copia para conservar el arreglo original. */
    for (i = 0; i < n; i++) {
        ordenados[i] = registros[i];
    }

    ordenar(ordenados, n);

    printf("ORDER");
    for (i = 0; i < n; i++) {
        printf(" %d", ordenados[i].id);
    }
    printf("\n");

    /* FIND necesita otra copia, esta vez ordenada por identificador. */
    for (i = 0; i < n; i++) {
        por_id[i] = registros[i];
    }

    ordenar_por_id(por_id, n);

    /* La posicion devuelta pertenece a por_id; leo el score de esa copia. */
    int posicion = buscar(por_id, n, q);

    if (posicion == -1) {
        printf("FIND %d -1\n", q);
    } else {
        printf("FIND %d %d\n", q, por_id[posicion].score);
    }

    return 0;
}

/**
 * @brief Calcula las cajas de un registro y convierte su nombre a mayusculas.
 * @param[in] pesos Vector con los m pesos del registro.
 * @param[in] m Cantidad de objetos, entre 1 y MAX_OBJETOS.
 * @param[in] tipo 0 para recorrido original y 1 para recorrido inverso.
 * @param[in] p Parametro de capacidad: cada caja admite p + 100.
 * @param[in,out] nombre Cadena del registro; queda en mayusculas ASCII.
 * @param[out] estado Recibe 1 si alguna caja queda exactamente llena, o 0.
 * @return Cantidad de cajas utilizadas, incluida la caja inicial.
 * @pre Los pesos y la configuracion ya fueron validados en main.
 */
int calcular(const int pesos[], int m, int tipo, int p,
              char nombre[], int *estado) {
    int capacidad = p + 100;
    int carga = 0;
    /* La caja inicial cuenta incluso si todos los pesos son cero. */
    int cajas = 1;
    int paso, posicion, letra;
    int longitud = (int)strlen(nombre);

    /* Cada llamada empieza un registro independiente. */
    *estado = 0;

    /* Convierto las minusculas ASCII y conservo el resto del nombre. */
    for (letra = 0; letra < longitud; letra++) {
        if (nombre[letra] >= 'a' && nombre[letra] <= 'z') {
            nombre[letra] = (char)(nombre[letra] - 'a' + 'A');
        }
    }

    /* Cambio el indice segun el tipo, sin modificar el vector de pesos. */
    for (paso = 0; paso < m; paso++) {
        if (tipo == 0) {
            posicion = paso;
        } else {
            posicion = m - 1 - paso;
        }

        /* La igualdad cabe. Un cero tambien cabe en una caja llena. */
        if (carga + pesos[posicion] > capacidad) {
            cajas++;
            carga = 0;
        }

        carga += pesos[posicion];

        /* Una vez activado, el estado conserva 1 hasta acabar el registro. */
        if (carga == capacidad) {
            *estado = 1;
        }
    }

    return cajas;
}

/**
 * @brief Suma recursivamente los scores de los primeros n registros.
 * @param[in] registros Arreglo con los scores ya calculados.
 * @param[in] n Cantidad de registros que se suman, entre 0 y MAX_REGISTROS.
 * @return Suma de los scores; devuelve 0 cuando n es 0.
 */
int total_rec(const Registro registros[], int n) {
    /* El caso base detiene la recursion antes de acceder al arreglo. */
    if (n == 0) {
        return 0;
    }

    /* Sumo el ultimo score y dejo los n - 1 restantes a la otra llamada. */
    return registros[n - 1].score + total_rec(registros, n - 1);
}

/**
 * @brief Ordena por score descendente y, en empate, por id ascendente.
 * @param[in,out] datos Arreglo cuyos primeros n registros se ordenan.
 * @param[in] n Cantidad de registros que se ordenan.
 * @return No devuelve un valor; modifica el arreglo recibido.
 */
void ordenar(Registro datos[], int n) {
    int i, j, mejor;
    Registro auxiliar;

    for (i = 0; i < n - 1; i++) {
        mejor = i;

        /* Selecciono el mayor score; si empatan, el menor identificador. */
        for (j = i + 1; j < n; j++) {
            if (datos[j].score > datos[mejor].score ||
                (datos[j].score == datos[mejor].score &&
                 datos[j].id < datos[mejor].id)) {
                mejor = j;
            }
        }

        /* Intercambio el registro completo para mantener juntos sus datos. */
        if (mejor != i) {
            auxiliar = datos[i];
            datos[i] = datos[mejor];
            datos[mejor] = auxiliar;
        }
    }
}

/**
 * @brief Ordena por id ascendente mediante seleccion.
 * @param[in,out] datos Arreglo que se prepara para la busqueda binaria.
 * @param[in] n Cantidad de registros que se ordenan.
 * @return No devuelve un valor; modifica el arreglo recibido.
 */
void ordenar_por_id(Registro datos[], int n) {
    int i, j, menor;
    Registro auxiliar;

    for (i = 0; i < n - 1; i++) {
        menor = i;

        /* Selecciono el menor id entre las posiciones que faltan. */
        for (j = i + 1; j < n; j++) {
            if (datos[j].id < datos[menor].id) {
                menor = j;
            }
        }

        /* El id conserva el score y los demas datos de su registro. */
        if (menor != i) {
            auxiliar = datos[i];
            datos[i] = datos[menor];
            datos[menor] = auxiliar;
        }
    }
}

/**
 * @brief Busca un identificador mediante busqueda binaria.
 * @param[in] datos Arreglo ordenado por id ascendente.
 * @param[in] n Cantidad de registros del arreglo.
 * @param[in] q Identificador que se consulta.
 * @return Posicion del registro encontrado, o -1 si no existe.
 * @pre Los primeros n registros deben estar ordenados por id ascendente.
 */
int buscar(const Registro datos[], int n, int q) {
    int inicio = 0;
    int fin = n - 1;

    /* Mantengo un intervalo cerrado y lo reduzco en cada iteracion. */
    while (inicio <= fin) {
        int medio = (inicio + fin) / 2;

        if (datos[medio].id == q) {
            return medio;
        }


        /* Por el orden ascendente, descarto la mitad que no puede contener q. */
        if (q < datos[medio].id) {
            fin = medio - 1;
        } else {
            inicio = medio + 1;
        }
    }

    return -1;
}
