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
    
    listaGlobal = model_cargarDesdeCSV("bin/realeza.csv");
    
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

    // 1. Guardamos referencia al rey actual (antes de matarlo) para mostrarlo en el mensaje
    Persona* reyAntiguo = model_obtenerReyActual(raizArbol);

    // 2. Ejecutamos la lógica de sucesión (Modelo)
    // Esto mata al antiguo y corona al nuevo internamente
    model_ejecutarMuerteRey(raizArbol);

    // 3. Buscamos quién quedó como rey ahora
    Persona* reyNuevo = model_obtenerReyActual(raizArbol);

    // 4. Mostramos el mensaje dramático
    view_mostrarCambioRey(reyAntiguo, reyNuevo);

    // 5. Mostramos el árbol actualizado para verificar visualmente
    view_mostrarArbol(raizArbol);
}