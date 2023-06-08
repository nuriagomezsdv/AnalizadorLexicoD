
#include <stdlib.h>
#include "tablaSimbolos.h"
#include "sintactico.h"
#include "errores.h"

int main( int argc, char *argv[]) {
    // Comprobamos que se ha pasado un fichero de entrada
    if (argc != 2) {
        imprimirError(FICHERO_NO_PROPORCIONADO);
        exit(1);
    }
    // Llamamos a la inicialización la tabla de símbolos
    inicializarTablaSimbolos();
    // Imprimimos la tabla de símbolos
    imprimirTablaSimbolos();
    // Llamamos al analizador sintáctico para que comience
    analizadorSintactico(argv[1]);
    // Imprimimos la tabla de símbolos
    imprimirTablaSimbolos();
    // Limpiamos la memoria utilizada
    // Utilizamos valgrind para comprobar que no hay errores de memoria
    limpiarMemoriaTablaSimbolos();

    return 0;
}