# Sistema de Sucesión Monárquica (MVC C++)

Aplicación de consola en C++ que modela un linaje real, calcula la sucesión legítima y muestra el árbol genealógico. El proyecto sigue un patrón MVC sencillo: la **Vista** gestiona la interacción por menú, el **Controlador** coordina las acciones y el **Modelo** encapsula la lógica sobre personas.

## Características principales
- Lectura de un archivo CSV (`bin/realeza.csv`) con la información de cada miembro.
- Construcción de un árbol genealógico enlazado a partir de los registros cargados.
- Limpieza y cálculo dinámico del heredero aplicando reglas de sucesión (el primer vivo siguiendo la jerarquía).
- Impresión jerárquica del árbol y anuncio del nuevo rey.