# Banco de pruebas final

publicas.json contiene los seis casos públicos del enunciado PG207.
evaluar.py es el ejecutor publicado en ese mismo enunciado.

propias.json reúne las seis entradas propias que ya estaban en el proyecto y cuatro casos adicionales:

- limites_maximos: 20 registros, 8 objetos, id y q iguales a 9999, nombre de 15 caracteres y TOTAL 160.
- busqueda_extremo: encuentra el id 40, el mayor del conjunto, con score 2.
- ausente_menor: busca el id 1, menor que todos los existentes, y devuelve -1.
- ausente_intermedio: busca el id 15, situado entre dos identificadores existentes, y devuelve -1.

Cada archivo .out contiene la salida esperada de la versión completa.
Las notas de validación anteriores describen las etapas de desarrollo; por eso algunas todavía hablan de funciones que estaban pendientes en esa etapa.

Desde PowerShell, con Python 3 instalado:

```powershell
py evaluar.py publicas.json reto.exe
py evaluar.py propias.json reto.exe
```

La comparación ignora diferencias de espacios y saltos de línea, como indica el enunciado.
Los resultados obtenidos deben conservarse después de ejecutar las pruebas en la computadora de entrega.

