REALIZADO POR----- Juan Chaustre 30.886.168, Luis Barrios 31.552.124
# Sistema de Sucesión Monárquica (MVC C++)

Aplicación de consola en C++ que modela un linaje real, calcula la sucesión legítima y muestra el árbol genealógico. El proyecto sigue un patrón MVC sencillo: la **Vista** gestiona la interacción por menú, el **Controlador** coordina las acciones y el **Modelo** encapsula la lógica sobre personas.

## Características principales
- Lectura de un archivo CSV (`bin/realeza.csv`) con la información de cada miembro.
- Construcción de un árbol genealógico enlazado a partir de los registros cargados.
- Cálculo dinámico del heredero con dos fases claras: primero se buscan varones vivos menores de 70 siguiendo la rama de primogénitos; si nadie cumple, se elige a la mujer viva más joven (mayor de 15 y menor de 70).
- Simulación del fallecimiento/retiro del monarca: al ejecutar la sucesión se marca al rey saliente como `wasKing` e `isDead`, y se corona al siguiente candidato válido de manera automática.
- Impresión jerárquica del árbol y anuncio del nuevo rey.

## Reglas de sucesión implementadas
1. **Búsqueda de varones:** se recorre primero la rama del primogénito (`hijoMayor`), luego la del segundo hijo (`hijoMenor`) y, por último, el propio nodo. Solo califican los varones vivos menores de 70 años.  
2. **Búsqueda de mujeres:** si no existe ningún varón que cumpla las condiciones en todo el árbol, se realiza una pasada completa para mujeres vivas entre 16 y 69 años. El trono se asigna a la candidata más joven de ese rango.  
3. **Transición automática:** la función `model_ejecutarMuerteRey` marca al monarca vigente como fallecido, recalcula al heredero con las reglas anteriores y establece `isKing` en el nuevo soberano, manteniendo un historial con `wasKing`.

## Estructura del proyecto
```
main.cpp                 # Punto de entrada que delega todo en la vista
controller/              # Lógica de coordinación entre Vista y Modelo
  controller.h
  controller.cpp
model/                   # Definiciones y funciones sobre "Persona"
  model.h
  model.cpp
view/                    # Interacción por consola en modo texto
  view.h
  view.cpp
bin/
  realeza.csv            # Datos de prueba y ejecutable compilado
```

## Compilación
Compila todo el proyecto (Windows PowerShell):
```
g++ main.cpp model/model.cpp view/view.cpp controller/controller.cpp -o bin/programa.exe
```

## Ejecución
1. Desde la raíz del proyecto (`C:\Users\PC\Desktop\EstructuraDinamica-ProyectoFinal-main`) ejecuta:
   ```
   ./bin/programa.exe
   ```
2. Usa las opciones del menú:
   - `1` Cargar datos desde CSV.
  - `2` Calcular y anunciar al rey vigente mostrando únicamente la línea viva de sucesión.
   - `3` Salir.

> **Nota:** El controlador prueba automáticamente varias rutas comunes para `realeza.csv` (`bin/`). Asegúrate de que el archivo exista en esta ruta o ajusta la ruta en `controller/controller.cpp` si cambiaste la estructura.

## Formato del CSV
La primera fila es un encabezado. Cada línea siguiente usa la forma:
```
id,nombre,apellido,género,edad,fatherId,isDead,wasKing,isKing
```
- `fatherId = 0` identifica a la raíz del árbol.
- Los campos booleanos se expresan como `0` o `1`.


## Próximas mejoras sugeridas

- Validar duplicados y datos inconsistentes al cargar el CSV.
- Admitir múltiples hijos por nodo (actualmente solo se guardan hijo mayor y menor).
- Persistir el estado de `isKing` en disco tras calcular la sucesión.