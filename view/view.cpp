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