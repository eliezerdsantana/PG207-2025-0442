Probé la versión completa del programa. Compiló sin errores ni advertencias.

- Pruebas públicas: 6 de 6 correctas.
- Pruebas propias: 10 de 10 correctas.

Probé ambos recorridos, ceros, cajas llenas, límites máximos, identificadores presentes y ausentes, y entradas inválidas. Todas las salidas coincidieron con lo esperado. Guardé las salidas obtenidas en pruebas/obtenidos y el resumen en pruebas/resultado_final.txt.

Con los pesos 60, 40 y 30, y capacidad 100, el recorrido original llena una caja con 60 y 40. El inverso agrupa 30 y 40, y después coloca 60 en otra caja. Ambos usan dos cajas, pero sus estados son diferentes.

En el desarrollo corregí la comparación del estado: debe comprobar carga == capacidad para detectar una caja exactamente llena.