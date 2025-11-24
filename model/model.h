#ifndef MODEL_H
#define MODEL_H

#include <string>
using namespace std;

struct Persona {
    int id;
    string name;
    string lastName;
    char gender;
    int age;
    int fatherId;
    bool isDead;
    bool wasKing;
    bool isKing;
    Persona* hijoMayor;
    Persona* hijoMenor;
    Persona* siguienteEnLista;
};

Persona* model_crearPersona(int id, string n, string l, char g, int a, int fId, bool d, bool wk, bool ik);
Persona* model_construirArbol(Persona* cabezaLista);
Persona* model_encontrarHeredero(Persona* nodo);
void model_limpiarReyes(Persona* nodo);
Persona* model_cargarDesdeCSV(string nombreArchivo);

#endif