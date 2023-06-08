
#ifndef COMPILADORD_LEXICO_H
#define COMPILADORD_LEXICO_H
#include "definiciones.h"

// Función que devuelve el siguiente componente léxico del archivo de entrada
// Si ComponenteLexico.lexema = NULL, significa que ha habido un error
ComponenteLexico siguienteComponenteLexico();

// Función que inicializa el analizador léxico
void inicializarAnalizadorLexico(char* ficheroEntrada);

// Funcion que finaliza el analizador lexico
void finalizarAnalizadorLexico();

#endif //COMPILADORD_LEXICO_H
