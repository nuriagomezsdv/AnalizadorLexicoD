
#ifndef COMPILADORD_SISTEMAENTRADA_H
#define COMPILADORD_SISTEMAENTRADA_H
#include "definiciones.h"

// Función que devuelve el siguiente carácter del fichero de entrada
char* siguienteCaracter();

// Función que llama el analizador léxico cuando ha aceptado un lexema en el siguienre caracter
// Devuelve el lexema del componente léxico
void aceptarLexema(ComponenteLexico *componenteLexico);

// Función que llama el analizador léxico cuando ha aceptado un lexema en el siguiente caracter
void retroceder();

// Función que llama el analizador léxico para ignorar un caracter
void ignorarCaracter();

// Función que llama el analizador léxico para ignorar un lexema
void ignorarLexema();

// Función que inicializa el sistema de entrada
void inicializarSistemaEntrada(char* ficheroEntrada);

// Funcion que finaliza el sistema de entrada
void finalizarSistemaEntrada();

#endif //COMPILADORD_SISTEMAENTRADA_H
