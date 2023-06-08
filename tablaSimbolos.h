
#ifndef COMPILADORD_TABLASIMBOLOS_H
#define COMPILADORD_TABLASIMBOLOS_H
#include "definiciones.h"

// Función que inicializa la tabla de símbolos
void inicializarTablaSimbolos();

// Función que busca un lexema en la tabla de símbolos
// La función introduce el componente lexico en la estructura componenteLexico
void buscarComponenteLexico(ComponenteLexico* componenteLexico);

// Función que limpia la memoria utilizada por la tabla de símbolos
void limpiarMemoriaTablaSimbolos();

// Función que imprime el contenido de la tabla de símbolos
void imprimirTablaSimbolos();

#endif //COMPILADORD_TABLASIMBOLOS_H
