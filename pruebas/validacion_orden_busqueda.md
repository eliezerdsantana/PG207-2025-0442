Probé el ordenamiento y la búsqueda por identificador. Después de corregir los errores de escritura, compilé sin errores ni advertencias.

- calculo_sentidos_ceros.in: esperaba ORDER 10 40 20 30 y FIND 99 -1. Salieron ambos resultados.
- busqueda_presente.in: esperaba FIND 20 1 y salió FIND 20 1.

Las filas individuales conservaron el orden de entrada.

Para ORDER usé selección: en cada posición busco el mayor score y, si hay empate, el menor id. Después intercambio los registros completos. Trabajo sobre una copia para conservar el arreglo original.

Para FIND preparo otra copia ordenada por id. La búsqueda binaria compara el identificador del medio y continúa en la mitad que corresponde. Devuelve la posición si encuentra el registro o -1 si no existe.

En estos casos, la media es 6 / 4 = 1.50. La calculé con total / (double)n y se documentará en el README.