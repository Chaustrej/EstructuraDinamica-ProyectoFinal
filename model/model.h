#ifndef MODEL_H
#define MODEL_H

#include <string>
using namespace std;

struct Persona {
    int id;
    string name;
    string lastName;
    char gender; // 'H' o 'M'
    int age;
    int fatherId;
    bool isDead;
    bool wasKing;
    bool isKing;

    Persona* hijoMayor;  
    Persona* hijoMenor;  
    Persona* siguienteEnLista;
};

// --- FUNCIONES BASICAS ---
Persona* model_crearPersona(int id, string n, string l, char g, int a, int fId, bool d, bool wk, bool ik);
Persona* model_cargarDesdeCSV(string nombreArchivo);
Persona* model_construirArbol(Persona* cabezaLista);
void model_limpiarReyes(Persona* nodo);
Persona* model_encontrarHeredero(Persona* raiz);
Persona* model_obtenerReyActual(Persona* nodo);
void model_ejecutarMuerteRey(Persona* raiz);

#endif