# PG207 - Embalaje secuencial de una mudanza

- Estudiante: Eliezer Daniels Santana
- Matrícula: 2025-0442
- Correo: 20250442@itla.edu.do

## Qué hace el programa

El programa calcula cuántas cajas necesita cada registro para guardar sus objetos. Cada caja tiene capacidad p + 100. El tipo 0 recorre los pesos en el orden de entrada y el tipo 1 los recorre al revés.

Si el siguiente objeto no cabe, abro otra caja y lo coloco en ella. El score es la cantidad de cajas utilizadas. El estado vale 1 si alguna caja quedó exactamente llena y 0 si ninguna quedó llena. Cada registro empieza con una caja, incluso si todos sus pesos son cero.

Primero valido toda la entrada. Compruebo los rangos de n, m, q, id, tipo, p y los pesos, que los id sean únicos y que estén todos los datos. Ante un error, el programa muestra únicamente ERROR. Una consulta q sin coincidencia es válida y devuelve -1.

El enunciado garantiza enteros representables, nombres de 1 a 15 caracteres ASCII alfanuméricos o guion bajo, y ausencia de datos extra.

## Cómo lo organicé

- Guardé los pesos en una matriz de 20 filas y 8 columnas.
- Usé un arreglo de registros con una configuración anidada para tipo y p.
- calcular recorre los pesos, convierte el nombre a mayúsculas y devuelve el estado mediante un apuntador. La carga y el estado se reinician para cada registro.
- total_rec suma los scores recursivamente. Su caso base es n == 0.
- ordenar usa selección para colocar primero el mayor score y, en empate, el menor id.
- Para FIND preparo otra copia ordenada por id y aplico búsqueda binaria. buscar devuelve la posición encontrada o -1.
- Trabajo sobre copias al ordenar para conservar las filas individuales en el orden de entrada.

## Documentacion del codigo

main.c y reto.h incluyen el encabezado de autoria con nombre, matricula, seccion, practica, fecha y enlace. Antes de cada funcion de main.c describi su trabajo, los parametros que recibe y el valor que devuelve. Tambien comente las partes principales del algoritmo: validacion, recorridos, cajas, recursividad, ordenamientos y busqueda binaria.

## Compilación y ejecución en Windows

Usé VS Code, PowerShell y GCC de MSYS2. Desde la carpeta del proyecto, compilo con:

```powershell
gcc -std=c11 -Wall -Wextra -Wpedantic main.c -o reto.exe
```

Para ejecutar una entrada desde PowerShell:

```powershell
cmd /c ".\reto.exe < pruebas\calculo_sentidos_ceros.in"
```

La salida esperada de ese caso es:

```text
40 DIRECTO 2 1
10 INVERSO 2 0
30 CEROS 1 0
20 LLENA_0 1 1
TOTAL 6
ORDER 10 40 20 30
FIND 99 -1
```

## Pruebas y resultados

Compilé sin errores ni advertencias y ejecuté el banco completo mediante PowerShell:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\evaluar.ps1
```

- publicas.json: 6 de 6 correctas.
- propias.json: 10 de 10 correctas.

El ajuste Bypass se aplica solo al proceso que ejecuta el auxiliar.

Las entradas y las salidas esperadas están en [pruebas](pruebas). Los archivos .out de esa carpeta y de pruebas/publicas contienen los resultados esperados. Las salidas obtenidas se guardaron con el mismo nombre en [pruebas/obtenidos](pruebas/obtenidos). El resumen está en [resultado_final.txt](pruebas/resultado_final.txt).

Los casos propios comprueban ambos recorridos, ceros, cajas llenas, id repetidos, pesos inválidos, entrada incompleta y búsquedas presentes o ausentes. limites_maximos comprueba 20 registros con 8 objetos, un nombre de 15 caracteres, id y q iguales a 9999 y TOTAL 160.

En [validacion_final.md](pruebas/validacion_final.md) dejé una traza y la corrección de la comparación del estado. Las otras notas de validación corresponden a etapas anteriores; describen lo que funcionaba y lo que faltaba en ese momento.

También incluí evaluar.py, el ejecutor del enunciado. Con Python 3 instalado se puede usar así:

```powershell
py evaluar.py publicas.json reto.exe
py evaluar.py propias.json reto.exe
```

En Linux o macOS, con GCC y Python 3 disponibles:

```sh
gcc -std=c11 -Wall -Wextra -Wpedantic main.c -o reto
python3 evaluar.py publicas.json ./reto
python3 evaluar.py propias.json ./reto
```

## Media de los scores

La calculo en double con esta expresión C:

```c
double media = total / (double)n;
```

En calculo_sentidos_ceros.in, el total es 6 y hay 4 registros: la media es 1.50. En limites_maximos.in, el total es 160 entre 20 registros: la media es 8.00.

La media se documenta aquí y se calcula en el programa. Uso (void)media para evitar la advertencia de variable sin usar y mantengo la salida exigida: filas individuales, TOTAL, ORDER y FIND.

## Historial de trabajo

Esta tabla incluye los commits anteriores al commit final. El hash completo de la entrega final se entrega aparte con el enlace del repositorio.

| Hash completo | Avance |
| --- | --- |
| `74a2b6bfb88a0584aed4efa2cda3d375fe8ca09a` | Creé los archivos iniciales y documenté el problema. |
| `b71501dace5309751d063d406d64152cd811d004` | Agregué la lectura, las validaciones y las primeras pruebas. |
| `0e1c896f634971de526d35e28c80c0d08e52ccc8` | Implementé el cálculo de cajas y probé ambos recorridos. |
| `77cc96e96b18e3d9dab59c167bec662666fc19d8` | Agregué la suma recursiva de los scores. |
| `58a87a01211c7b9618edebb4ed5e5499f72c7bd4` | Agregué el ordenamiento y la búsqueda binaria. |
| `5e9c25046a8fc6b3331cd3cd52708390480bc16a` | Agregué el banco completo y guardé las salidas obtenidas. |
| `c66cf56ba131f6480bc08a70b4cef390ec16fc6a` | Completé el README y corregí los detalles de la revisión final. |

## Fuentes consultadas

- Enunciado PG207_2025-0442.pdf: reglas del problema, restricciones, casos públicos y evaluar.py.
- [Documentación de GCC](https://gcc.gnu.org/onlinedocs/gcc/C-Dialect-Options.html): selección de C11 con -std=c11.
- [Borrador de C11, WG14 N1570](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf): scanf en la sección 7.21.6.4 y strlen en la sección 7.24.6.3.


