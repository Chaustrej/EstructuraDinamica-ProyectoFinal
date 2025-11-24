#include "model.h"
#include <iostream>
#include <fstream>

// Helpers privados
int stringToInt(string s) { try { return stoi(s); } catch (...) { return 0; } }
string obtenerCampo(string linea, int indice) {
    string campo = ""; int comas = 0;
    for (char c : linea) {
        if (c == ',') { comas++; if (comas > indice) break; }
        else if (comas == indice) campo += c;
    }
    return campo;
}

Persona* model_crearPersona(int id, string n, string l, char g, int a, int fId, bool d, bool wk, bool ik) {
    Persona* p = new Persona;
    p->id = id; p->name = n; p->lastName = l; p->gender = g; p->age = a;
    p->fatherId = fId; p->isDead = d; p->wasKing = wk; p->isKing = ik;
    p->hijoMayor = nullptr; p->hijoMenor = nullptr; p->siguienteEnLista = nullptr;
    return p;
}

Persona* model_buscarPorId(Persona* cabeza, int id) {
    while (cabeza) { if (cabeza->id == id) return cabeza; cabeza = cabeza->siguienteEnLista; }
    return nullptr;
}

Persona* model_construirArbol(Persona* lista) {
    Persona* raiz = nullptr;
    Persona* actual = lista;
    while (actual) {
        if (actual->fatherId == 0) raiz = actual;
        else {
            Persona* padre = model_buscarPorId(lista, actual->fatherId);
            if (padre) {
                if (!padre->hijoMayor) padre->hijoMayor = actual;
                else if (actual->age > padre->hijoMayor->age) {
                    padre->hijoMenor = padre->hijoMayor; padre->hijoMayor = actual;
                } else padre->hijoMenor = actual;
            }
        }
        actual = actual->siguienteEnLista;
    }
    return raiz;
}

Persona* model_encontrarHeredero(Persona* nodo) {
    if (!nodo) return nullptr;
    if (!nodo->isDead) return nodo;
    Persona* izq = model_encontrarHeredero(nodo->hijoMayor);
    if (izq) return izq;
    return model_encontrarHeredero(nodo->hijoMenor);
}

void model_limpiarReyes(Persona* nodo) {
    if (!nodo) return;
    nodo->isKing = false;
    model_limpiarReyes(nodo->hijoMayor);
    model_limpiarReyes(nodo->hijoMenor);
}

Persona* model_cargarDesdeCSV(string arch) {
    ifstream f(arch); if (!f.is_open()) return nullptr;
    string l; getline(f, l);
    Persona *cab = nullptr, *ult = nullptr;
    while (getline(f, l)) {
        Persona* p = model_crearPersona(
            stringToInt(obtenerCampo(l,0)), obtenerCampo(l,1), obtenerCampo(l,2),
            obtenerCampo(l,3)[0], stringToInt(obtenerCampo(l,4)), stringToInt(obtenerCampo(l,5)),
            stringToInt(obtenerCampo(l,6))==1, stringToInt(obtenerCampo(l,7))==1, stringToInt(obtenerCampo(l,8))==1
        );
        if (!cab) { cab = p; ult = p; } else { ult->siguienteEnLista = p; ult = p; }
    }
    f.close(); return cab;
}