# Plan del reto PG207


## Descripción del problema
El programa debe calcular cuántas cajas se utilizan para guardar los objetos de cada registro, respetando el orden indicado y la capacidad de peso de cada caja, que es p + 100. Si el siguiente objeto no cabe en la caja actual, se abre otra y se continúa hasta terminar todos los objetos de ese registro. Al final, score indica la cantidad de cajas utilizadas y estado vale 1 si alguna caja quedó exactamente llena, o 0 si ninguna quedó llena.

## Datos de entrada
n m q
- n: Representa la cantidad de regristros que se procesarán.
- m: Representa la cantidad de objetos que contiene cada registro.
- q: Es el identificador del registro que se buscará al final.

id nombre tipo p x1 x2 ... xm
- id: Es el identificador único de cada registro.
- nombre: es el nombre o etiqueta de cada registro.
- tipo: es el sentido del recorrido: 0 original y 1 inverso.
- p: parámetro que determina la capacidad de cada caja mediante p + 100.
- x1 ... xm: son los pesos de los m objetos del registro.

## Datos de salida

Para una entrada válida, el programa va a mostrar una linea por cada registro, respetando el orden en que fueron ingresados. Cada línea incluirá el id, el nombre en mayúsculas, la cantidad de cajas utilizadas, que es el "score", y el indicador de si alguna caja quedó exactamente llena, que sería el "estado". Después de los resultados individuales, se imprimirán tres líneas adicionales:

- TOTAL: Es la suma de los scores de todos los registros de esa entrada.
- ORDER: Son los identificadores (id) ordenados por score de mayor a menor. Si dos resgistros tienen el mismo score, aparecerá primero el identificador de menor valor.
- FIND: Es el identificador consultado "q" y el score del registro encontrado. Si ese identificador no existe, mostrará "q" seguido de "-1"; porque una busqueda sin coincidencia no convierte la entrada en inválida.

En caso de detectar una entrada realmente inválida, el programa impimirá únicamente "ERROR", sin mostrar resultados parciales. Por eso, el programa debe comprobar que los datos de entrada sean válidos antes de imprimir los resultados.

## Restricciones y validaciones

- n: De 1 a 20 registros.
- m: De 1 a 8 objetos por registro.
- id y q: Enteros de 1 a 9999.
- tipo: Únicamente 0 o 1.
- p: De 0 o 100.
- x: De 0 o 100.

Los id deben ser únicos, no pueden repetirse, y deben recibirse todos los datos indicados por n y m.

## Pseudocódigo

INICIO
       Intentar leer n, m y q

       SI no se pudieron leer los tres datos ENTONCES
           Mostrar "ERROR"
           TERMINAR
FIN SI

SI n < 1 O n > 20 O m < 1 O m > 8 O q < 1 O q > 9999 ENTONCES
    Mostrar "ERROR"
    TERMINAR
FIN SI

Crear un arreglo registros con capacidad para 20 registros
Crear una matriz muestras con 20 filas y 8 columnas

PARA i DESDE 0 HASTA n - 1 HACER
    Intentar leer id, nombre, tipo y p del registro actual

    SI no se pudieron leer los cuatro datos ENTONCES
        Mostrar "ERROR"
        TERMINAR
    FIN SI

    SI id < 1 O id > 9999 O tipo no pertenece a {0, 1}
    O p < 0 O p > 100 ENTONCES
        Mostrar "ERROR"
        TERMINAR
    FIN SI

    SI el id coincide con el de algún registro anterior ENTONCES
        Mostrar "ERROR"
        TERMINAR
    FIN SI

    Guardar id, nombre, tipo y p en registros[i]

    PARA j DESDE 0 HASTA m - 1 HACER
        Intentar leer muestras[i][j]

        Si no se pudo leer el peso ENTONCES
            Mostrar "ERROR"
            TERMINAR
        FIN SI

        SI muestras[i][j] < 0 O muestras[i][j] > 100 ENTONCES
            Mostrar "ERROR"
            TERMINAR
        FIN SI
    FIN PARA
FIN PARA

PARA cada registro en el orden de entrada HACER
    Llamar a calcular con sus pesos, m, tipo, p, nombre y referencia a estado
    Guardar el valor devuelto en score
    Mostrar id, nombre, score y estado
FIN PARA

total = total_rec(registros, n)
media = total / (double)n
Mostrar "TOTAL", total

Copiar registros a ordenados
ordenar(ordenados, n)
Mostrar "ORDER" seguido de los identificadores de ordenados

Copiar registros a por_id
ordenar_por_id(por_id, n)
posicion = buscar(por_id, n, q)

SI posicion == -1 ENTONCES
    Mostrar "FIND", q, -1
SINO
    Mostrar "FIND", q, por_id[posicion].score
FIN SI
FIN

## Función calcular

FUNCION calcular(pesos, m, tipo, p, nombre, REFERENCIA estado)
    capacidad = p + 100
    carga = 0
    cajas = 1
    estado = 0
    Convertir nombre a mayúsculas

    PARA paso DESDE 0 HASTA m - 1 HACER
        SI tipo == 0 ENTONCES
            posicion = paso
        SINO
            posicion = m - 1 - paso
        FIN SI

        SI carga + pesos[posicion] > capacidad ENTONCES
            cajas = cajas + 1
            carga = 0
        FIN SI

        carga = carga + pesos[posicion]

        SI carga == capacidad ENTONCES
            estado = 1
        FIN SI
    FIN PARA

    DEVOLVER cajas
FIN FUNCION

## Función total_rec

FUNCION total_rec(registros, n)
    SI n == 0 ENTONCES
        DEVOLVER 0
    FIN SI

    DEVOLVER registros[n - 1].score + total_rec(registros, n - 1)
FIN FUNCION