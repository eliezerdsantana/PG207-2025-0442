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