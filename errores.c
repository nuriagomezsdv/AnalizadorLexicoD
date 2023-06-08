
#include "stdio.h"
#include "errores.h"

// Función que imprime los distintos errores en función del código de error
void imprimirError(int error){
    switch(error){
        case TAM_MAX_LEXEMA:
            printf("Error: Tamaño máximo del lexema superado\n.");
            break;
        case LECTURA_FICHERO:
            printf("Error: No se ha podido leer el fichero.\n");
            break;
        case APERTURA_FICHERO:
            printf("Error: No se ha podido abrir el fichero.\n");
            break;
        case MEMORIA_INSUFICIENTE:
            printf("Error: Memoria insuficiente.\n");
            break;
        case FICHERO_NO_PROPORCIONADO:
                printf("Error: Debe indicar el nombre del fichero a analizar.\n ./analizadorLexicoD [FICHERO_CODIGO_FUENTE.d]\n");
                break;
        case FLOAT_MAL_FORMADO:
                printf("Error: Floating point mal formado.\n");
                break;
        default:
            printf("Error desconocido.\n");
            break;
    }

}