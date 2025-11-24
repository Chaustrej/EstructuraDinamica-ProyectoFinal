#include "view.h"
#include "../controller/controller.h" // View llama a Controller
#include <iostream>

// Helpers de visualización
void helper_imprimirNodo(Persona* nodo, int nivel) {
    if (!nodo) return;
    for(int i=0; i<nivel; i++) cout << "   ";
    
    cout << (nodo->isDead ? "[X] " : "[ ] ")
         << nodo->name << " " << nodo->lastName
         << " (" << nodo->age << ")";
         
    if (nodo->isKing) cout << " <--- REY";
    cout << endl;
    
    helper_imprimirNodo(nodo->hijoMayor, nivel+1);
    helper_imprimirNodo(nodo->hijoMenor, nivel+1);
}
// --- FUNCIONES PÚBLICAS ---

void view_mostrarMensaje(string msg) {
    cout << "\n[SISTEMA]: " << msg << endl;
}

void view_anunciarRey(Persona* rey) {
    cout << "--------------------------------" << endl;
    if (rey) cout << "HABEMUS REX: " << rey->name << " " << rey->lastName << endl;
    else cout << "EL LINAJE HA TERMINADO." << endl;
    cout << "--------------------------------" << endl;
}

void view_mostrarArbol(Persona* raiz) {
    cout << "\n=== ARBOL GENEALOGICO ===" << endl;
    if (!raiz) cout << "(Vacio)" << endl;
    else helper_imprimirNodo(raiz, 0);
    cout << "=========================\n" << endl;
}
// BUCLE PRINCIPAL (El usuario vive aquí)
void view_iniciarSistema() {
    int opcion = 0;
    bool ejecutar = true;

    while (ejecutar) {
        cout << "\n1. Cargar Datos" << endl;
        cout << "2. Asignar Rey" << endl;
        cout << "3. Salir" << endl;
        cout << ">> ";
        
        if (!(cin >> opcion)) {
            cin.clear(); cin.ignore(1000, '\n'); opcion = 0;
        }

        switch (opcion) {
            case 1:
                // VIEW LLAMA A CONTROLLER
                controller_eventoCargarDatos();
                break;
            case 2:
                // VIEW LLAMA A CONTROLLER
                controller_eventoAsignarRey();
                break;
            case 3:
                ejecutar = false;
                view_mostrarMensaje("Saliendo...");
                break;
            default:
                view_mostrarMensaje("Opcion invalida.");
        }
    }
}