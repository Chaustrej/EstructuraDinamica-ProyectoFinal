#include "view.h"
#include "../controller/controller.h"
#include <iostream>
#include <cctype>

void helper_imprimirNodo(Persona* nodo, int nivel) {
    if (!nodo) return;
    for(int i=0; i<nivel; i++) cout << "   ";
    
        cout << (nodo->isDead ? "[X] " : "[ ] ")
            << nodo->name << " " << nodo->lastName
            << " (" << nodo->age << ")";
    
        if (nodo->isKing && !nodo->isDead) cout << " <--- REY";
    cout << endl;
    
    helper_imprimirNodo(nodo->hijoMayor, nivel+1);
    helper_imprimirNodo(nodo->hijoMenor, nivel+1);
}

void view_mostrarMensaje(string msg) {
    cout << "\n[SISTEMA]: " << msg << endl;
}

void view_anunciarRey(Persona* rey) {
    cout << "--------------------------------" << endl;
    if (rey) cout << "REY ACTUAL: " << rey->name << " " << rey->lastName << endl;
    else cout << "EL LINAJE HA TERMINADO." << endl;
    cout << "--------------------------------" << endl;
}

void view_mostrarArbol(Persona* raiz) {
    cout << "\n=== ARBOL GENEALOGICO ===" << endl;
    if (!raiz) cout << "(Vacio)" << endl;
    else helper_imprimirNodo(raiz, 0);
    cout << "=========================\n" << endl;
}

int view_menuEdicionPersona() {
    int opcion;
    cout << "\n--- MENU DE EDICION ---" << endl;
    cout << "1. Nombre" << endl;
    cout << "2. Apellido" << endl;
    cout << "3. Genero" << endl;
    cout << "4. Edad" << endl;
    cout << "5. Estado de vida" << endl;
    cout << "6. Editar todos los campos" << endl;
    cout << "0. Terminar edicion" << endl;
    cout << ">> Seleccione una opcion: ";
    if (!(cin >> opcion)) {
        cin.clear(); cin.ignore(1000, '\n');
        return -1;
    }
    return opcion;
}

string view_pedirNuevoNombre(Persona* p) {
    string n;
    cout << "Nombre actual (" << p->name << "): ";
    cin >> n;
    return n;
}

string view_pedirNuevoApellido(Persona* p) {
    string l;
    cout << "Apellido actual (" << p->lastName << "): ";
    cin >> l;
    return l;
}

char view_pedirNuevoGenero(Persona* p) {
    char g;
    cout << "Genero actual (" << p->gender << ") [H/M]: ";
    cin >> g;
    g = static_cast<char>(toupper(g));
    while (g != 'H' && g != 'M') {
        cout << "Ingrese 'H' o 'M': ";
        cin >> g;
        g = static_cast<char>(toupper(g));
    }
    return g;
}

int view_pedirNuevaEdad(Persona* p) {
    int a;
    cout << "Edad actual (" << p->age << "): ";
    while (!(cin >> a)) {
        cin.clear(); cin.ignore(1000, '\n');
        cout << "Edad invalida. Intente de nuevo: ";
    }
    return a;
}

bool view_pedirNuevoEstadoVida(Persona* p) {
    int flag;
    cout << "Esta muerto? (Actual: " << (p->isDead ? "Si" : "No") << ") [1=Si, 0=No]: ";
    while (!(cin >> flag) || (flag != 0 && flag != 1)) {
        cin.clear(); cin.ignore(1000, '\n');
        cout << "Ingrese 1 para Si o 0 para No: ";
    }
    return flag == 1;
}

// BUCLE PRINCIPAL (El usuario vive aquí)
void view_iniciarSistema() {
    int opcion = 0;
    bool ejecutar = true;

    while (ejecutar) {
        cout << "\n--- MENU REAL ---" << endl;
        cout << "1. Cargar Datos" << endl;
        cout << "2. Ver Arbol y Estado Actual" << endl;
        cout << "3. Ver Linea de Sucesion (Solo Vivos)" << endl;
        cout << "4. Matar Rey Actual y Asignar Nuevo" << endl;
        cout << "5. Editar Datos de una Persona" << endl;  // <--- NUEVO
        cout << "6. Salir" << endl; // <--- CAMBIO DE NUMERO
        cout << ">> ";
        
        if (!(cin >> opcion)) {
            cin.clear(); cin.ignore(1000, '\n'); opcion = 0;
        }

        switch (opcion) {
            case 1: controller_eventoCargarDatos(); break;
            case 2: controller_eventoAsignarRey(); break;
            case 3: controller_eventoMostrarSucesion(); break;
            case 4: controller_eventoMatarRey(); break;
            case 5: controller_eventoEditarPersona(); break;
            case 6: ejecutar = false; view_mostrarMensaje("Saliendo..."); break;
            default: view_mostrarMensaje("Opcion invalida.");
        }
    }
}

static int contadorSucesion = 1;

void helper_imprimirSucesion(Persona* nodo) {
    if (nodo == nullptr) return;

    // 1. Si está vivo, lo imprimimos
    if (!nodo->isDead) {
        cout << contadorSucesion << ". " << nodo->name << " " << nodo->lastName 
             << " (" << nodo->age << " anios)";
        
        if (nodo->isKing && !nodo->isDead) cout << " [REY ACTUAL]";
        cout << endl;
        
        contadorSucesion++; 
    }

    // 2. Primero el primogénito (Izquierda)
    helper_imprimirSucesion(nodo->hijoMayor);

    // 3. Después el hermano (Derecha)
    helper_imprimirSucesion(nodo->hijoMenor);
}

void view_mostrarLineaSucesion(Persona* raiz) {
    cout << "\n=== LINEA DE SUCESION ACTUAL (VIVOS) ===" << endl;
    
    if (raiz == nullptr) {
        cout << "Arbol vacio." << endl;
    } else {
        contadorSucesion = 1; 
        helper_imprimirSucesion(raiz);
        
        if (contadorSucesion == 1) { 
            cout << "No quedan herederos vivos." << endl;
        }
    }
    cout << "========================================" << endl;
}

void view_mostrarCambioRey(Persona* reyAntiguo, Persona* reyNuevo) {
    cout << "\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
    cout << "       SUCESO EN EL REINO       " << endl;
    cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
    
    if (reyAntiguo) {
        cout << "El Rey " << reyAntiguo->name << " ha fallecido." << endl;
    } else {
        cout << "No habia Rey reinante." << endl;
    }

    if (reyNuevo) {
        cout << ">>> LARGA VIDA AL NUEVO REY: " << reyNuevo->name << " " << reyNuevo->lastName << " <<<" << endl;
    } else {
        cout << ">>> EL LINAJE SE HA EXTINGUIDO. NO HAY HEREDEROS. <<<" << endl;
    }
    cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n" << endl;
}

void view_pedirDatosEdicion(Persona* p, string& n, string& l, char& g, int& a, bool& d) {
    cout << "\n=== EDITANDO NODO (ID: " << p->id << ") ===" << endl;
    cout << "Nota: Ingrese el dato nuevo para cada campo." << endl;
    
    cout << "Nombre actual (" << p->name << "): ";
    cin >> n;
    
    cout << "Apellido actual (" << p->lastName << "): ";
    cin >> l;
    
    cout << "Genero actual (" << p->gender << ") [H/M]: ";
    cin >> g;
    
    cout << "Edad actual (" << p->age << "): ";
    if (!(cin >> a)) { cin.clear(); cin.ignore(1000, '\n'); a = p->age; } // Validación simple
    
    cout << "Esta muerto? (Actual: " << (p->isDead ? "Si" : "No") << ") [1=Si, 0=No]: ";
    int tempDead;
    if (!(cin >> tempDead)) { tempDead = 0; }
    d = (tempDead == 1);
    
    cout << ">>> Datos capturados para actualizacion." << endl;
}