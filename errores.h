
#ifndef COMPILADORD_ERRORES_H
#define COMPILADORD_ERRORES_H

// Definimos distintos errores
#define TAM_MAX_LEXEMA 100
#define LECTURA_FICHERO 101
#define APERTURA_FICHERO 102
#define MEMORIA_INSUFICIENTE 103
#define FICHERO_NO_PROPORCIONADO 104
#define FLOAT_MAL_FORMADO 105

// Función que imprime los distintos errores según el código de error
void imprimirError(int error);


#endif //COMPILADORD_ERRORES_H
