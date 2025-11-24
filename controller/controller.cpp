#include "controller.h"
#include "../model/model.h" 
#include "../view/view.h"    
#include <iostream>

// Al usar 'static', estas variables son privadas de este archivo
// pero persisten durante toda la ejecución.
static Persona* listaGlobal = nullptr;
static Persona* raizArbol = nullptr;
