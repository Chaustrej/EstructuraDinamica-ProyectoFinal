#include "controller.h"
#include "../model/model.h" 
#include "../view/view.h"    
#include <iostream>

// Al usar 'static', estas variables son privadas de este archivo
// pero persisten durante toda la ejecución.
static Persona* listaGlobal = nullptr;
static Persona* raizArbol = nullptr;

void controller_eventoCargarDatos() {
    view_mostrarMensaje("Cargando datos desde CSV...");
    
    listaGlobal = model_cargarDesdeCSV("../bin/realeza.csv");
    
    if (listaGlobal == nullptr) {
        view_mostrarMensaje("ERROR: No se pudo abrir 'realeza.csv'.");
    } else {
        raizArbol = model_construirArbol(listaGlobal);
        view_mostrarMensaje("Datos cargados exitosamente.");
        
        // El controller decide qué se muestra ahora:
        view_mostrarArbol(raizArbol);
    }
}

void controller_eventoAsignarRey() {
    if (raizArbol == nullptr) {
        view_mostrarMensaje("ERROR: Base de datos vacia. Cargue datos primero.");
        return;
    }

    view_mostrarMensaje("Calculando sucesion...");
    
    // 1. Limpiar
    model_limpiarReyes(raizArbol);
    
    // 2. Calcular
    Persona* nuevoRey = model_encontrarHeredero(raizArbol);
    
    // 3. Actualizar dato
    if (nuevoRey != nullptr) {
        nuevoRey->isKing = true;
    }
    
    // 4. Actualizar Vistas
    view_anunciarRey(nuevoRey);
    view_mostrarArbol(raizArbol);
}

void controller_eventoMostrarSucesion() {
    if (raizArbol == nullptr) {
        view_mostrarMensaje("Base de datos vacia. Cargue datos primero.");
        return;
    }
    // Llama a la vista pasándole la raíz
    view_mostrarLineaSucesion(raizArbol);
}

void controller_eventoMatarRey() {
    if (raizArbol == nullptr) {
        view_mostrarMensaje("Cargue datos primero.");
        return;
    }

    Persona* reyAntiguo = model_obtenerReyActual(raizArbol);

    model_ejecutarMuerteRey(raizArbol);

    bool guardado = model_guardarEnCSV(listaGlobal, "../bin/realeza.csv");
    if (!guardado) {
        view_mostrarMensaje("AVISO: No se pudo persistir la muerte del rey en el CSV.");
    }

    Persona* reyNuevo = model_obtenerReyActual(raizArbol);

    // 4. Mostramos el mensaje dramático
    view_mostrarCambioRey(reyAntiguo, reyNuevo);

    // 5. Mostramos el árbol actualizado para verificar visualmente
    view_mostrarArbol(raizArbol);
}

void controller_eventoEditarPersona() {
    if (listaGlobal == nullptr) {
        view_mostrarMensaje("Cargue datos primero.");
        return;
    }

    int idBuscado;
    cout << "\nIngrese el ID de la persona a editar: ";
    cin >> idBuscado;

    Persona* persona = model_buscarPorId(listaGlobal, idBuscado);

    if (persona == nullptr) {
        view_mostrarMensaje("ID no encontrado.");
        return;
    }

    bool continuar = true;
    bool huboCambios = false;

    while (continuar) {
        int opcionEdicion = view_menuEdicionPersona();

        switch (opcionEdicion) {
            case 0:
                continuar = false;
                break;
            case 1:
                persona->name = view_pedirNuevoNombre(persona);
                huboCambios = true;
                break;
            case 2:
                persona->lastName = view_pedirNuevoApellido(persona);
                huboCambios = true;
                break;
            case 3:
                persona->gender = view_pedirNuevoGenero(persona);
                huboCambios = true;
                break;
            case 4:
                persona->age = view_pedirNuevaEdad(persona);
                huboCambios = true;
                break;
            case 5:
                persona->isDead = view_pedirNuevoEstadoVida(persona);
                huboCambios = true;
                break;
            case 6: {
                string n, l;
                char g;
                int a;
                bool d;
                view_pedirDatosEdicion(persona, n, l, g, a, d);
                model_actualizarDatos(persona, n, l, g, a, d);
                huboCambios = true;
                break;
            }
            default:
                view_mostrarMensaje("Opcion de edicion invalida.");
                break;
        }
    }

    if (!huboCambios) {
        view_mostrarMensaje("No se realizaron cambios.");
        return;
    }

    // RECONSTRUCCION DEL ARBOL (orden puede cambiar tras editar edad)
    Persona* actual = listaGlobal;
    while(actual != nullptr) {
        actual->hijoMayor = nullptr;
        actual->hijoMenor = nullptr;
        actual = actual->siguienteEnLista;
    }
    raizArbol = model_construirArbol(listaGlobal);

    bool guardado = model_guardarEnCSV(listaGlobal, "../bin/realeza.csv");
    if (guardado) {
        view_mostrarMensaje("Datos actualizados, arbol reestructurado y CSV sincronizado.");
    } else {
        view_mostrarMensaje("Datos actualizados pero no se pudo escribir el CSV.");
    }

    view_mostrarArbol(raizArbol);
}