# Sistema de Sucesión Monárquica (MVC C++)

Aplicación de consola en C++ que modela un linaje real, calcula la sucesión legítima y muestra el árbol genealógico. El proyecto sigue un patrón MVC sencillo: la **Vista** gestiona la interacción por menú, el **Controlador** coordina las acciones y el **Modelo** encapsula la lógica sobre personas.

## Características principales
- Lectura de un archivo CSV (`bin/realeza.csv`) con la información de cada miembro.
- Construcción de un árbol genealógico enlazado a partir de los registros cargados.
- Limpieza y cálculo dinámico del heredero aplicando reglas de sucesión (el primer vivo siguiendo la jerarquía).
- Impresión jerárquica del árbol y anuncio del nuevo rey.
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
1. Desde la raíz del proyecto (`C:\Users\ejemp\OneDrive\Desktop\EDD\Luis`) ejecuta:
   ```
   ./bin/programa.exe
   ```
2. Usa las opciones del menú:
   - `1` Cargar datos desde CSV.
   - `2` Calcular y anunciar al rey vigente.
   - `3` Salir.