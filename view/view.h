#ifndef VIEW_H
#define VIEW_H

#include <string>
#include "../model/model.h"

using namespace std;

// Función principal que inicia la interfaz (Llamada por main)
void view_iniciarSistema();

// Funciones de visualización (Llamadas por Controller)
void view_mostrarArbol(Persona* raiz);
void view_anunciarRey(Persona* rey);
void view_mostrarMensaje(string msg);
void view_mostrarLineaSucesion(Persona* raiz);
void view_mostrarCambioRey(Persona* reyAntiguo, Persona* reyNuevo);
void view_pedirDatosEdicion(Persona* p, string& n, string& l, char& g, int& a, bool& d);
int view_menuEdicionPersona();
string view_pedirNuevoNombre(Persona* p);
string view_pedirNuevoApellido(Persona* p);
char view_pedirNuevoGenero(Persona* p);
int view_pedirNuevaEdad(Persona* p);
bool view_pedirNuevoEstadoVida(Persona* p);

#endif