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
        cout << "3. Ver Linea de Sucesion (Solo Vivos)" << endl;
        cout << "4. Salir" << endl;
        cout << ">> ";
        
        if (!(cin >> opcion)) {
            cin.clear(); cin.ignore(1000, '\n'); opcion = 0;
        }

        switch (opcion) {
            case 1:
                controller_eventoCargarDatos();
                break;
            case 2:
                controller_eventoAsignarRey();
                break;
            case 3:
                controller_eventoMostrarSucesion();
                break;
            case 4:
                ejecutar = false;
                view_mostrarMensaje("Saliendo...");
                break;
            default:
                view_mostrarMensaje("Opcion invalida.");
        }
    }
}

static int contadorSucesion = 1;

// Función recursiva interna de la vista
void helper_imprimirSucesion(Persona* nodo) {
    if (nodo == nullptr) return;

    // 1. Si está vivo, lo imprimimos
    if (!nodo->isDead) {
        cout << contadorSucesion << ". " << nodo->name << " " << nodo->lastName 
             << " (" << nodo->age << " anios)";
        
        if (nodo->isKing) cout << " [REY ACTUAL]";
        cout << endl;
        
        contadorSucesion++; // Aumentamos el número para el siguiente
    }

    // 2. Primero el primogénito (Izquierda)
    helper_imprimirSucesion(nodo->hijoMayor);

    // 3. Después el hermano (Derecha)
    helper_imprimirSucesion(nodo->hijoMenor);
}

// Función pública
void view_mostrarLineaSucesion(Persona* raiz) {
    cout << "\n=== LINEA DE SUCESION ACTUAL (VIVOS) ===" << endl;
    
    if (raiz == nullptr) {
        cout << "Arbol vacio." << endl;
    } else {
        contadorSucesion = 1; // Reiniciar contador
        helper_imprimirSucesion(raiz);
        
        if (contadorSucesion == 1) { 
            // Si sigue siendo 1, significa que no imprimió a nadie
            cout << "No quedan herederos vivos." << endl;
        }
    }
    cout << "========================================" << endl;
}