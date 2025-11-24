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
