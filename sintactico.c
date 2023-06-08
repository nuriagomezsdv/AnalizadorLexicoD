
#include "stdio.h"
#include "sintactico.h"
#include "definiciones.h"
#include "lexico.h"

// Función que ejecuta el analizador sintáctico
void analizadorSintactico(char *ficheroEntrada){
    ComponenteLexico componenteLexico;

    // Llamamos a la inicialización del analizador léxico
    inicializarAnalizadorLexico(ficheroEntrada);

    // Bucle que se ejecuta mientras no se llegue al final del fichero
    do{
        // Llamamos a la función que devuelve el siguiente componente léxico
        componenteLexico = siguienteComponenteLexico();
        // Imprimimos el componente léxico
        // Comprobamos que el lexema no sea NULL (significa que ha habido un error)
        if(componenteLexico.lexema != NULL) {
            printf("< Componente Léxico: %d , Lexema: %s >\n", componenteLexico.compLexico, componenteLexico.lexema);
        }
    }while(componenteLexico.compLexico != EOF);

    // LLamamos a la finalizacion del analizador lexico
    finalizarAnalizadorLexico();
}