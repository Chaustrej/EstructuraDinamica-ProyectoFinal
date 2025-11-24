#ifndef VIEW_H
#define VIEW_H

#include <string>
#include "../model/model.h" // Necesita conocer la struct Persona para pintar

using namespace std;

// Función principal que inicia la interfaz (Llamada por main)
void view_iniciarSistema();

// Funciones de visualización (Llamadas por Controller)
void view_mostrarArbol(Persona* raiz);
void view_anunciarRey(Persona* rey);
void view_mostrarMensaje(string msg);

#endif