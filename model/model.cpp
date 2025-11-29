#include "model.h"
#include <iostream>
#include <fstream>

int stringToInt(string s) { try { return stoi(s); } catch (...) { return 0; } }

string obtenerCampo(string linea, int indice) {
    string campo = ""; int comas = 0;
    for (char c : linea) {
        if (c == ',') { comas++; if (comas > indice) break; }
        else if (comas == indice) campo += c;
    }
    return campo;
}

// ==========================================
// GESTION DE MEMORIA Y ARBOL
// ==========================================
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

void model_limpiarReyes(Persona* nodo) {
    if (!nodo) return;
    nodo->isKing = false;
    model_limpiarReyes(nodo->hijoMayor);
    model_limpiarReyes(nodo->hijoMenor);
}

// ==========================================
// LOGICA DE SUCESION
// ==========================================

// FASE 1: Busqueda de varones
Persona* buscarCandidatoVaron(Persona* nodo) {
    if (nodo == nullptr) return nullptr;

    bool esVaron = (nodo->gender == 'H');
    bool estaVivo = (!nodo->isDead);
    bool edadCorrecta = (nodo->age < 70);

    if (esVaron && estaVivo && edadCorrecta) {
        return nodo;
    }

    // 1. Rama de Primogénitos (Izquierda)
    Persona* candidatoIzq = buscarCandidatoVaron(nodo->hijoMayor);
    if (candidatoIzq != nullptr) return candidatoIzq;

    // 2. Rama de segundos hijos (Derecha)
    Persona* candidatoDer = buscarCandidatoVaron(nodo->hijoMenor);
    if (candidatoDer != nullptr) return candidatoDer;

    return nullptr;
}

// FASE 2: Busqueda de mujeres (Salica modificada)
void buscarCandidataMujer(Persona* nodo, Persona*& mejorCandidata) {
    if (nodo == nullptr) return;

    // Analizar nodo actual
    bool esMujer = (nodo->gender == 'M');
    bool estaViva = (!nodo->isDead);
    bool rangoEdad = (nodo->age > 15 && nodo->age < 70);

    if (esMujer && estaViva && rangoEdad) {
        if (mejorCandidata == nullptr) {
            mejorCandidata = nodo;
        } else {
            // Regla: "La más joven"
            if (nodo->age < mejorCandidata->age) {
                mejorCandidata = nodo;
            }
        }
    }

    buscarCandidataMujer(nodo->hijoMayor, mejorCandidata);
    buscarCandidataMujer(nodo->hijoMenor, mejorCandidata);
}

Persona* model_encontrarHeredero(Persona* raiz) {
    if (raiz == nullptr) return nullptr;
    // 1.intento varones
    Persona* reyVaron = buscarCandidatoVaron(raiz);
    
    if (reyVaron != nullptr) {
        return reyVaron;
    }

    // 2. intento mujeres (Si no hay varones en NINGUNA parte)
    Persona* reina = nullptr;
    buscarCandidataMujer(raiz, reina);
    
    return reina;
}

Persona* model_obtenerReyActual(Persona* nodo) {
    if (nodo == nullptr) return nullptr;
    
    if (nodo->isKing && !nodo->isDead) return nodo;
    
    Persona* izq = model_obtenerReyActual(nodo->hijoMayor);
    if (izq) return izq;
    
    return model_obtenerReyActual(nodo->hijoMenor);
}

void model_ejecutarMuerteRey(Persona* raiz) {
    if (raiz == nullptr) return;

    // 1. Buscar al Rey Actual
    Persona* reyActual = model_obtenerReyActual(raiz);

    if (reyActual != nullptr) {
        // 2. Aplicar lógica de muerte/retiro
        reyActual->isKing = false;
        reyActual->wasKing = true;
        reyActual->isDead = true; // Lo matamos para que la lógica de sucesión busque al siguiente
    }

    // 2.5 Asegurar que no queden banderas de reyes activos rezagadas
    model_limpiarReyes(raiz);

    // 3. Buscar al NUEVO heredero con el rey anterior ya muerto
    Persona* nuevoRey = model_encontrarHeredero(raiz);

    // 4. Coronar al nuevo
    if (nuevoRey != nullptr) {
        nuevoRey->isKing = true;
    }
}

void model_actualizarDatos(Persona* p, string n, string l, char g, int a, bool d) {
    if (p == nullptr) return;
    
    p->name = n;
    p->lastName = l;
    p->gender = g;
    p->age = a;
    p->isDead = d;
    
    // NOTA: No tocamos id, fatherId, ni isKing/wasKing
}
// ==========================================
// CARGA CSV
// ==========================================
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

bool model_guardarEnCSV(Persona* cabeza, string arch) {
    ofstream f(arch); if (!f.is_open()) return false;
    f << "id,nombre,apellido,genero,edad,fatherId,isDead,wasKing,isKing\n";
    Persona* actual = cabeza;
    while (actual) {
        f << actual->id << ','
          << actual->name << ','
          << actual->lastName << ','
          << actual->gender << ','
          << actual->age << ','
          << actual->fatherId << ','
          << (actual->isDead ? 1 : 0) << ','
          << (actual->wasKing ? 1 : 0) << ','
          << (actual->isKing ? 1 : 0) << '\n';
        actual = actual->siguienteEnLista;
    }
    f.close();
    return true;
}