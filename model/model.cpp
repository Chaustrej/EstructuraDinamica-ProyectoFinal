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
