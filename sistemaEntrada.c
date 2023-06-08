
#include <bits/types/FILE.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sistemaEntrada.h"
#include "errores.h"

// Definimos el tamaño de cada buffer del sistema de doble centinela
#define TAM_BUFFER 64

// El archivo de entrada
FILE *archivo = NULL;

// Definimos el sistema de doble centinela como un struct con dos arrays de caracteres y dos punteros
struct sistemaDobleCentinela {
    char buffer1[TAM_BUFFER];
    char buffer2[TAM_BUFFER];
    char *inicio;
    char *delantero;
};

// Definimos el sistema de doble centinela
struct sistemaDobleCentinela sistemaDobleCentinela;

// Definimos un contador de caracteres aceptados
int caracteresAceptados = 0;

// Variable que indica si ha retrocedido un caracter
int retrocedido = 0;

// Función que carga el siguiente bloque de caracteres en el buffer
void _cargarBloque(int bloque) {

    if (bloque == 2) {
        if (retrocedido ==
            1) { // Si se ha retrocedido un caracter no se carga el siguiente bloque, simplemente se cambia el puntero delantero de bloque
            retrocedido = 0;
            sistemaDobleCentinela.delantero = sistemaDobleCentinela.buffer2;
        } else { // Cargamos el buffer 2
            size_t bytes_leidos = fread(sistemaDobleCentinela.buffer2, sizeof(char), TAM_BUFFER - 1, archivo);
            if (bytes_leidos == 0 && !feof(archivo)) {
                imprimirError(LECTURA_FICHERO);
                exit(1);
            }
            // Añadimos EOF al final de los bytes leidos
            // En caso de haberse llenado el buffer se colocara al final de este
            // En caso de no haberse llenado representa el EOF de fin de archivo
            sistemaDobleCentinela.buffer2[bytes_leidos] = EOF;

            // Cambiamos el puntero delantero al principio del buffer 2
            sistemaDobleCentinela.delantero = sistemaDobleCentinela.buffer2;
        }
    } else if (bloque == 1) { // Si se ha retrocedido un caracter no se carga el siguiente bloque
        if (retrocedido ==
            1) { // Si se ha retrocedido un caracter no se carga el siguiente bloque, simplemente se cambia el puntero delantero de bloque
            retrocedido = 0;
            sistemaDobleCentinela.delantero = sistemaDobleCentinela.buffer1;
        } else {// Cargamos el buffer 1
            size_t bytes_leidos = fread(sistemaDobleCentinela.buffer1, sizeof(char), TAM_BUFFER - 1, archivo);
            if (bytes_leidos == 0 && !feof(archivo)) {
                imprimirError(LECTURA_FICHERO);
                exit(1);
            }

            // Añadimos EOF al final de los bytes leídos
            // En caso de haberse llenado el buffer se colocará al final de este
            // En caso de no haberse llenado representa el EOF de fin de archivo
            sistemaDobleCentinela.buffer1[bytes_leidos] = EOF;

            // Cambiamos el puntero delantero al principio del buffer 1
            sistemaDobleCentinela.delantero = sistemaDobleCentinela.buffer1;
        }
    }
};

// Función que inicializa el sistema de entrada
void inicializarSistemaEntrada(char *archivoEntrada) {
    sistemaDobleCentinela.inicio = sistemaDobleCentinela.buffer1;
    sistemaDobleCentinela.delantero = sistemaDobleCentinela.buffer1;

    // Cargamos el buffer 1
    // Abrimos el archivo
    archivo = fopen(archivoEntrada, "r");
    if (archivo == NULL) {
        imprimirError(APERTURA_FICHERO);
        exit(1);
    }

    // Leemos el archivo y lo guardamos en el buffer 1
    // Leemos todos los bytes del archivo menos el último, donde prondremos el EOF
    size_t bytes_leidos = fread(sistemaDobleCentinela.buffer1, sizeof(char), TAM_BUFFER - 1, archivo);
    if (bytes_leidos == 0 && !feof(archivo)) {
        imprimirError(LECTURA_FICHERO);
        exit(1);
    }

    // Añadimos EOF al final de los bytes leidos
    // En caso de haberse llenado el buffer se colocara al final de este
    // En caso de no haberse llenado representa el EOF de fin de archivo
    sistemaDobleCentinela.buffer1[bytes_leidos] = EOF;

}

void finalizarSistemaEntrada() {
    fclose(archivo);
}

// Función que devuelve el siguiente carácter del fichero de entrada
char *siguienteCaracter() {
    // Definimos el puntero al siguiente carácter
    char *caracter = NULL;

    // Comprobamos si el puntero delantero está en un caracter EOF
    if (*sistemaDobleCentinela.delantero == EOF) {
        // Comprobamos si el puntero delantero está al final de algun bloque o es el fin de fichero
        if (sistemaDobleCentinela.delantero == sistemaDobleCentinela.buffer1 + TAM_BUFFER - 1) {
            // El puntero delantero está al final del buffer 1
            // Cargamos el bloque 2
            _cargarBloque(2);
        } else if (sistemaDobleCentinela.delantero == sistemaDobleCentinela.buffer2 + TAM_BUFFER - 1) {
            // El puntero delantero está al final del buffer 2
            // Cargamos el bloque 1
            _cargarBloque(1);
        }
    }

    // Devolvemos el siguiente carácter
    caracter = sistemaDobleCentinela.delantero;

    // Movemos el puntero delantero al siguiente carácter
    sistemaDobleCentinela.delantero++;

    // Aumento el numero de caracteres aceptados
    caracteresAceptados++;
    return caracter;
}

// Función que llama el analizador léxico cuando ha aceptado un lexema
void aceptarLexema(ComponenteLexico *componenteLexico) {
    int caracteresALeer = 0;
    // Se comprueba si el tamaño del lexema es mayor que el tamaño del buffer
    if (caracteresAceptados > TAM_BUFFER - 1) {
        // El tamaño del lexema es mayor que el tamaño del buffer
        // Se devuelve un error
        imprimirError(TAM_MAX_LEXEMA);
        // Se indica que ha habido un error poniendo el lexema a NULL
        componenteLexico->lexema = NULL;
    } else {
        // Reservamos memoria dinamica para el lexema
        componenteLexico->lexema = (char *) malloc(sizeof(char) * (caracteresAceptados + 1));
        if (componenteLexico->lexema == NULL) {
            imprimirError(MEMORIA_INSUFICIENTE);
            exit(1);
        }

        // Copiamos el lexema aceptado desde el puntero inicio al puntero delantero
        // El puntero inicio apunta al principio del lexema aceptado
        // Hay que tener en cuenta que el puntero delantero puede estar en un bloque diferente al puntero inicio

        // Comprobamos si el puntero inicio está en el bloque 1
        if (sistemaDobleCentinela.inicio >= sistemaDobleCentinela.buffer1 &&
            sistemaDobleCentinela.inicio <= sistemaDobleCentinela.buffer1 + TAM_BUFFER - 1) {
            // Comprobamos si el puntero delantero está en el bloque 1
            if (sistemaDobleCentinela.delantero >= sistemaDobleCentinela.buffer1 &&
                sistemaDobleCentinela.delantero < sistemaDobleCentinela.buffer1 + TAM_BUFFER - 1) {
                // El puntero inicio está en el bloque 1 y el puntero delantero también
                // Se copia el lexema desde el puntero inicio al puntero delantero
                strncpy(componenteLexico->lexema, sistemaDobleCentinela.inicio, caracteresAceptados + 1);

                // El puntero delantero está en el bloque 2
            } else {
                // Se copia el lexema desde el puntero inicio hasta el final del bloque 1
                caracteresALeer = sistemaDobleCentinela.buffer1 + TAM_BUFFER - 1 - sistemaDobleCentinela.inicio;
                strncpy(componenteLexico->lexema, sistemaDobleCentinela.inicio, caracteresALeer);

                // Se copia el lexema desde el principio del bloque 2 hasta el puntero delantero
                caracteresALeer = caracteresAceptados - caracteresALeer;
                strncpy(componenteLexico->lexema +
                        (sistemaDobleCentinela.buffer1 + TAM_BUFFER - 1 - sistemaDobleCentinela.inicio),
                        sistemaDobleCentinela.buffer2, caracteresALeer + 1);

            }
        } else { // El puntero inicio está en el bloque 2

            // Comprobamos si el puntero delantero está en el bloque 1
            if (sistemaDobleCentinela.delantero >= sistemaDobleCentinela.buffer1 &&
                sistemaDobleCentinela.delantero <= sistemaDobleCentinela.buffer1 + TAM_BUFFER - 1) {
                // Se copia el lexema desde el puntero inicio hasta el final del bloque 2
                caracteresALeer = sistemaDobleCentinela.buffer2 + TAM_BUFFER - 1 - sistemaDobleCentinela.inicio;
                strncpy(componenteLexico->lexema, sistemaDobleCentinela.inicio, caracteresALeer);

                // Se copia el lexema desde el principio del bloque 1 hasta el puntero delantero
                caracteresALeer = caracteresAceptados - caracteresALeer;
                strncpy(componenteLexico->lexema +
                        (sistemaDobleCentinela.buffer2 + TAM_BUFFER - 1 - sistemaDobleCentinela.inicio),
                        sistemaDobleCentinela.buffer1, caracteresALeer + 1);

            } else { // El puntero delantero está en el bloque 2 y el puntero inicio también

                // Se copia el lexema desde el puntero inicio al puntero delantero
                strncpy(componenteLexico->lexema, sistemaDobleCentinela.inicio, caracteresAceptados + 1);
            }
        }
        // Asignamos al ultimo caracter del lexema el caracter de fin de cadena
        componenteLexico->lexema[caracteresAceptados] = '\0';

    }

    // Movemos el puntero inicio al siguiente carácter
    sistemaDobleCentinela.inicio = sistemaDobleCentinela.delantero;

    // Reseteamos el número de caracteres aceptados
    caracteresAceptados = 0;
}


// Función que llama el analizador léxico cuando acepta un lexema en el siguiente carácter
void retroceder() {
    // Retrocedemos el puntero delantero
    if (sistemaDobleCentinela.delantero == sistemaDobleCentinela.buffer1) {
        // El puntero delantero está al principio del buffer 1
        // Lo ponemos al final del buffer 2
        sistemaDobleCentinela.delantero = sistemaDobleCentinela.buffer2 + TAM_BUFFER - 1;
        retrocedido = 1;
    } else if (sistemaDobleCentinela.delantero == sistemaDobleCentinela.buffer2) {
        // El puntero delantero está al principio del buffer 2
        // Lo ponemos al final del buffer 1
        sistemaDobleCentinela.delantero = sistemaDobleCentinela.buffer1 + TAM_BUFFER - 1;
        retrocedido = 1;
    } else {
        // El puntero delantero está en medio de alguno de los buffers
        // Lo retrocedemos en 1
        sistemaDobleCentinela.delantero--;
    }
    // Disminuimos el numero de caracteres aceptados
    caracteresAceptados--;
}

// Función que llama el analizador léxico para ignorar un carácter
void ignorarCaracter() {
    // Movemos el puntero inicio al siguiente carácter
    sistemaDobleCentinela.inicio = sistemaDobleCentinela.delantero;
    // Disminuimos el numero de caracteres aceptados
    caracteresAceptados--;
}

// Función que llama el analizador léxico para ignorar un lexema
void ignorarLexema() {
    // Movemos el puntero inicio al siguiente carácter
    sistemaDobleCentinela.inicio = sistemaDobleCentinela.delantero;
    // Reseteamos el número de caracteres aceptados
    caracteresAceptados = 0;
}
