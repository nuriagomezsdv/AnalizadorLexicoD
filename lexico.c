
#include "lexico.h"
#include "definiciones.h"
#include "sistemaEntrada.h"
#include "tablaSimbolos.h"
#include "errores.h"
#include <stdio.h>
#include <ctype.h>
#include <malloc.h>

// Componente léxico actual
ComponenteLexico componenteLexico = {0, NULL};

// Variable para indicar si el lexema ha sido aceptado
int aceptado = 0;
// Variable para indicar si el lexema ha sido ignorado
int ignorado = 0;

// Función que acepta un lexema con el identificador de componente léxico indicado
void aceptar(int identificadorComponenteLexico) {
    // Se acepta el lexema y se guarda en el campo lexema del componente léxico
    aceptarLexema(&componenteLexico);
    // Se guarda el identificador de componente léxico en el campo compLexico del componente léxico
    componenteLexico.compLexico = identificadorComponenteLexico;
    // Se indica que e ha aceptado el lexema
    aceptado = 1;
}

// Función que ignora el lexema actual
void ignorar() {
    // Se llama a ignorar lexema del sistema de entrada
    ignorarLexema();
    ignorado = 1;
}

// Función que limpia el componente léxico anterior
void limpiarComponenteLexico() {
    if (componenteLexico.lexema != NULL) {
        componenteLexico.compLexico = 0;
        free(componenteLexico.lexema);
        componenteLexico.lexema = NULL;
    }
}

// Autómatas:

// 1. Identificadores y palabras reservadas
// Automata de cadenas alfanumericas: Cadena de caracteres que comienza con letra o _ y continúa con letras y numeros.
void automataCadenasAlfanumericas() {
    // Se llama cuando se ha reconocido una letra o un _
    char *caracter;

    // Pedimos caracteres hasta encontrarnos con algo que no sea alfanumerico o _
    do {
        caracter = siguienteCaracter();
    } while (isalnum(*caracter) || *caracter == '_');

    // Cuando para es que se ha encontrado algo diferente a un caracter alfanumerico o _
    // Hay que retroceder el caracter que ha parado el automata para que el sistema de entrada lo vuelva a leer
    retroceder();

    // En ente caso llamamos directamente a la funcion del sistema de entrada para aceptar el lexema ya que todavia no tenemos el identificador de componente lexico
    aceptarLexema(&componenteLexico);
    aceptado = 1;
    // Comprobamos si el lexema es una palabra reservada o un identificador preguntando a la tabla de simbolos
    // La función introduce el componente lexico en la estructura componenteLexico
    // Se comprueba si el lexema es NULL o no, si es NULL es que se ha excedido el tamaño maximo del lexema
    if(componenteLexico.lexema != NULL) {
        buscarComponenteLexico(&componenteLexico);
    }
}

// 2. Comentarios

// 2.1 Comentarios de una línea
void automataLineComments() {
    // Se llama cuando se ha reconocido //, hay que reconocer hasta que se encuentre un salto de linea
    char *caracter;
    // Pedimos caracteres hasta encontrarnos con un salto de linea
    do {
        caracter = siguienteCaracter();
    } while (*caracter != '\n');

    // Cuando para es que se ha encontrado un salto de linea
    // Hay que retroceder el caracter que ha parado el automata para que el sistema de entrada lo vuelva a leer
    retroceder();

    ignorar(); // Se ignora el comentario (no se envia al analizador sintactico)
}

// 2.2 Comentarios de varias líneas: BLOCK COMMENTS
void automataBlockComments() {
    // Se llama cuando se ha reconocido /*, hay que reconocer hasta que se encuentre */
    char *caracter;
    int estado = 0;

    do {
        caracter = siguienteCaracter();
        switch (estado) {
            case 0: // Estado 0: No se ha reconocido nada
                if (*caracter == '*') {
                    estado = 1;
                } else {
                    estado = 0;
                }
                break;
            case 1: // Estado 1: Se ha reconocido un *
                if (*caracter == '/') { // Ya tenemos */ y se acepta el comentario
                    ignorar(); // Se ignora el comentario (no se envia al analizador sintactico)
                    // En esta funcion se pone ignorado a 1, por lo que se sale del bucle
                } else if (*caracter == '*') { // Si es * nos quedamos en el estado 1, aun puede llegar  la /
                    estado = 1;
                } else { // Si no es * ni / se vuelve al estado 0, nada reconocido
                    estado = 0;
                }
                break;
            default:
                break;
        }
    } while (ignorado == 0);

}

// 2.3 Comentarios de varias líneas: NESTED COMMENTS (pueden estar anidados)
void automataNestedComments() {
    // Se llama cuando se ha reconocido /+, hay que reconocer hasta que se encuentre +/
    char *caracter;
    int estado = 0;
    int contadorComentarios = 1; // Contador de comentarios anidados

    do {
        caracter = siguienteCaracter();
        switch (estado) {
            case 0: // Estado 0: No se ha reconocido nada
                if (*caracter == '+') { // Se ha reconocido un +, vamos a estado 1 a ver si se cierra un comentario
                    estado = 1;
                } else if (*caracter == '/') { // Se ha reconocido un /, vamos a estado 2 a ver si se abre un comentario
                    estado = 2;
                } else {
                    estado = 0;
                }
                break;
            case 1: // Estado 1: Se ha reconocido un +
                if (*caracter == '/') { // Ya tenemos +/ y disminuimos en uno el contador de comentarios anidados
                    contadorComentarios--;
                    if (contadorComentarios == 0) { // Si el contador es 0 se acepta el comentario, están todos cerrados
                        ignorar(); // Se ignora el comentario (no se envia al analizador sintactico)
                        // En esta funcion se pone ignorado a 1, por lo que se sale del bucle
                    } else { // Si no se vuelve al estado 0, nada reconocido
                        estado = 0;
                    }
                } else if (*caracter != '+') { // Si es + nos quedamos en el estado 1, aun puede llegar /
                    estado = 1;
                } else { // Si no es + ni / se vuelve al estado 0, nada reconocido
                    estado = 0;
                }
                break;
            case 2: // Estado 2: Se ha reconocido un /
                if (*caracter ==
                    '+') { // Si es + tenemos /+ entonces se aumenta en uno el contador de comentarios anidados
                    contadorComentarios++;
                } else { // Si no es + se vuelve al estado 0, nada reconocido
                    estado = 0;
                }
                break;
            default:
                break;
        }
    } while (ignorado == 0);

}

// 3. Strings
void automataStrings() {
    // Se llama cuando se ha reconocido ", hay que reconocer hasta que se encuentre ", pero que no sea \"
    char *caracter;
    int estado = 0;

    do {
        caracter = siguienteCaracter();
        switch (estado) {
            case 0: // Estado 0: No se ha reconocido nada
                if (*caracter == '"') {
                    aceptar(STRING_LITERAL);
                } else if (*caracter == '\\') { // Si es \ se pasa al estado 1 para ignorar que entre "
                    estado = 1;
                } else { // Si no es " ni \ se mantiene en el estado 0, nada reconocido
                    estado = 0;
                }
                break;
            case 1: // Estado 1: Se ha reconocido el caracter '\'
                // Sea cual sea el caracter que llege ahora se vuelve al estado 0, nada reconocido
                // Ya que ahora no importa que llegue " ya que se tendría \" y estaría escapado
                estado = 0;
                break;
            default:
                break;
        }
    } while (aceptado == 0);

}

// 4. Números flotantes

// 4.1 DecimalExponent (e o E)
void automataDecimalExponent() {
    // Se llama cuando se reconoce una e una E después de un LeadingDecimal o DecimalDigitNoStartingUS
    // Puede haber un + o un -
    // Se reconoce hasta que se encuentre un caracter que no sea un número ni _
    char *caracter;
    int estado = 0;

    caracter = siguienteCaracter();

    do {
        switch (estado) {
            case 0:
                if (*caracter == '+' || *caracter == '-' || isdigit(*caracter) || *caracter == '_') {
                    estado = 1;
                }else{
                    // Despues de una e o E no puede haber un caracter que no sea un + , - , numero o _
                    // Hay que retroceder el caracter leido para que el sistema de entrada lo vuelva a leer
                    retroceder();
                    // Ignoramos el floating point mal formado
                    ignorar();
                    // Informamos del error
                    imprimirError(FLOAT_MAL_FORMADO);
                }
                break;
            case 1:
                do {
                    caracter = siguienteCaracter();
                } while (isdigit(*caracter) || *caracter == '_');

                // Cuando se sale del bucle se ha reconocido un caracter que no es un número ni _
                // Hay que retroceder el caracter que ha parado el automata para que el sistema de entrada lo vuelva a leer
                retroceder();
                aceptar(FLOATING_POINT_LITERAL);

                break;
            default:
                break;
        }
    } while (aceptado == 0 && ignorado == 0);

}

// 4.2 DecimalDigitNoStartingUS (números que no empiezan por _)
void automataDecimalDigitNoStartingUS() {
    // Se llama cuando se encuentra un . seguido de un numero (por tanto no empieza por _), hay que reconocer hasta que se encuentre un caracter que no sea un número ni _
    char *caracter;

    do{
        caracter = siguienteCaracter();
    } while (isdigit(*caracter) || *caracter == '_');

    // Se tiene un numero seguido de un punto y seguido de un numero
    // Se comprueba si hay una e o una E
    if(*caracter == 'e' || *caracter == 'E') {
        automataDecimalExponent();
    }else{
        // Cuando se sale del bucle se ha reconocido un caracter que no es un número ni _
        // Hay que retroceder el caracter que ha parado el automata para que el sistema de entrada lo vuelva a leer
        retroceder();
        aceptar(FLOATING_POINT_LITERAL);
    }

}

// 4.3 LeadingDecimal (números que pueden empezar por 0)
void automataLeadingDecimal() {
    // Se llama cuando se ha reconocido un 0 seguido de un numero distinto de cero, hay que reconocer hasta que se encuentre un caracter que no sea un número ni _
    // Luego tiene que haber un . o una e o una E
    // Si se encuentra una e o una E se llama a automataDecimalExponent()
    // Despues del punto si hay un numero se llama a automataDecimalDigitNoStartingUS()
    // Si no es un digito aceptamos el leading decimal seguido de punto, es un floating point

    char *caracter;
    int estado = 0;

    do {
        switch (estado) {
            case 0: // Estado 0: Se ha reconocido un 0 seguido de un numero distinto de cero
                do {
                    caracter = siguienteCaracter();
                } while (isdigit(*caracter) || *caracter == '_');
                // Cuando se sale del bucle se ha reconocido un caracter que no es un número ni _
                if (*caracter == '.') {
                    estado = 1;
                } else if (*caracter == 'e' || *caracter == 'E') {
                    automataDecimalExponent();
                } else {
                    // Despues de un numero que empieza por 0 no puede haber un caracter que no sea un punto o una e o una E
                    // Hay que retroceder el caracter leido para que el sistema de entrada lo vuelva a leer
                    retroceder();
                    // Ignoramos el leading decimal mal formado
                    ignorar();
                    // Informamos del error
                    imprimirError(FLOAT_MAL_FORMADO);
                }
                break;
            case 1: // Estado 1: Se ha reconocido un .
                caracter = siguienteCaracter();
                // Si despues del punto hay un numero se llama a automataDecimalDigitNoStartingUS()
                if (isdigit(*caracter)) {
                    automataDecimalDigitNoStartingUS();
                } else {
                    // Se ha leido un caracter que no es un numero, hay que retroceder para que el sistema de entrada lo vuelva a leer
                    retroceder();
                    // Aceptamos el leading decimal seguido de punto, es un floating point
                    aceptar(FLOATING_POINT_LITERAL);
                }

                break;
            default:
                break;
        }
    } while (aceptado == 0 && ignorado == 0);

}

// 5. Números enteros (8 y 8_000) (INTEGER_LITERAL)
void automataNumerosEnteros() {
    // Se llama cuando se ha reconocido un número distinto de 0, hay que reconocer hasta que se encuentre un caracter que no sea un número ni _
    char *caracter;

    do {
        caracter = siguienteCaracter();
    } while (isdigit(*caracter) || *caracter == '_');

    // Si se encuentra un . después de un número entero se llama a automataDecimalDigitNoStartingUS()
    if (*caracter == '.') {
        caracter = siguienteCaracter();
        // Si despues del punto hay un número se llama a automataDecimalDigitNoStartingUS()
        if (isdigit(*caracter)) {
            automataDecimalDigitNoStartingUS();
        } else {
            // Si despues del punto no hay un número se acepta el número entero seguido del punto, que es un numero flotante
            // Hay que retroceder el caracter que se ha leido para que el sistema de entrada lo vuelva a leer
            retroceder();
            aceptar(FLOATING_POINT_LITERAL);
        }
    } else if(*caracter == 'e' || *caracter == 'E'){
        // Si se encuentra una e o una E después de un número entero se llama a automataDecimalExponent()
        automataDecimalExponent();
    } else {
        // Cuando para es que se ha encontrado un caracter que no es un número ni _
        // Hay que retroceder el caracter que ha parado el automata para que el sistema de entrada lo vuelva a leer
        retroceder();

        // Se acepta el número entero
        aceptar(INTEGER_LITERAL);
    }

}

// 6. Números binarios (0b0) (INTEGER_LITERAL)
void automataNumerosBinarios() {
    // Se llama cuando se ha reconocido un 0
    // Hay que ver si se reconoce una b o B y entonces reconocer hasta que se encuentre un caracter que no sea un 0 o 1
    char *caracter;

    caracter = siguienteCaracter();

    // Si el caracter es b o B se sigue leyendo el numero binario hasta que se encuentre un caracter que no sea 0 o 1
    if (*caracter == 'b' || *caracter == 'B') {
        do {
            caracter = siguienteCaracter();
        } while (*caracter == '0' || *caracter == '1' || *caracter == '_');
        // Cuando para es que se ha encontrado un caracter que no es un 0 ni 1 ni _
        // Hay que retroceder el caracter que ha parado el automata para que el sistema de entrada lo vuelva a leer
        retroceder();
        // Se acepta el número binario
        aceptar(INTEGER_LITERAL);

    // Si es un numero se llama al automata de numeros flotantes, se tiene un 0 seguido de un numero
    } else if (isdigit(*caracter)) {
        automataLeadingDecimal();
    // Si es una e o una E se llama al automata de exponentes
    } else if( *caracter == 'e' || *caracter == 'E'){
        automataDecimalExponent();
    // Si no es b o B ni un numero ni e o E, se retrocede el caracter y se acepta el 0
    }else {
        retroceder();
        aceptar(INTEGER_LITERAL);
    }
}

// Función que devuelve el siguiente componente léxico del archivo de entrada
ComponenteLexico siguienteComponenteLexico() {
    // Se leen caracteres del archivo de entrada hasta encontrarse el carácter EOF
    char *caracter = NULL;
    int estado = 0;
    aceptado = 0;

    // Se limpia la estructura componenteLexico ya enviada al analizador sintáctico
    if (componenteLexico.lexema != NULL) {
        limpiarComponenteLexico();
    }

    do {
        // Se llama a la función que devuelve el siguiente caracter del archivo de entrada
        caracter = siguienteCaracter();
        switch (estado) {
            case 0: // Estado 0: Estado inicial, no se ha reconocido nada
                // Si el caracter es una letra o un guion bajo, se llama al automata de cadenas alfanumericas
                if (isalpha(*caracter) || *caracter == '_') {
                    automataCadenasAlfanumericas();
                    estado = 0;
                }
                    // Si el caracter es un digito distinto de cero, se llama al automata de numeros enteros
                else if (isdigit(*caracter) && *caracter != '0') {
                    automataNumerosEnteros();
                    estado = 0;
                    ignorado = 0;
                    // Si el caracter es un 0, se llama al automata de numeros binarios
                } else if (*caracter == '0') {
                    automataNumerosBinarios();
                    estado = 0;
                    ignorado = 0;
                } else {
                    switch (*caracter) {
                        case EOF: // Si el caracter es EOF se devuelve el componente lexico EOF
                            componenteLexico.compLexico = EOF;
                            componenteLexico.lexema = NULL;
                            break;
                        case '{':
                            aceptar('{');
                            break;
                        case '}':
                            aceptar('}');
                            break;
                        case '(':
                            aceptar('(');
                            break;
                        case ')':
                            aceptar(')');
                            break;
                        case '[':
                            aceptar('[');
                            break;
                        case ']':
                            aceptar(']');
                            break;
                        case ',':
                            aceptar(',');
                            break;
                        case ';':
                            aceptar(';');
                            break;
                        case '.':
                            estado = 8;
                            break;
                        case '+':
                            estado = 1;
                            break;
                        case '-':
                            estado = 2;
                            break;
                        case '*':
                            estado = 16;
                            break;
                        case '=':
                            estado = 3;
                            break;
                        case '<':
                            estado = 4;
                            break;
                        case '>':
                            estado = 5;
                            break;
                        case '!':
                            estado = 6;
                            break;
                        case '"':
                            automataStrings();
                            estado = 0;
                            break;
                        case '/':
                            estado = 7;
                            break;
                        case '$':
                            aceptar('$');
                            break;
                        case '%':
                            estado = 9;
                            break;
                        case '&':
                            estado = 11;
                            break;
                        case '|':
                            estado = 12;
                            break;
                        case '?':
                            aceptar('?');
                            break;
                        case ':':
                            aceptar(':');
                            break;
                        case '^':
                            estado = 17;
                            break;
                        case '~':
                            estado = 19;
                            break;
                        case '@':
                            aceptar('@');
                            break;
                        case '#':
                                aceptar('#');
                                break;

                        default:
                            // Si no es nada de lo anterior, se ignora el caracter (\n, \t, espacio en blanco, etc )
                            ignorarCaracter();
                            break;
                    }
                }
                break;
            case 1: // Estado 1: Se ha reconocido un +
                if (*caracter == '+') {
                    aceptar(MAS_MAS);
                } else if (*caracter == '=') {
                    aceptar(MAS_IGUAL);
                } else {
                    retroceder();
                    aceptar('+');
                }

                break;
            case 2: // Estado 2: Se ha reconocido un -
                if (*caracter == '-') {
                    aceptar(MENOS_MENOS);
                } else if (*caracter == '=') {
                    aceptar(MENOS_IGUAL);
                } else {
                    retroceder();
                    aceptar('-');
                }
                break;
            case 3: // Estado 3: Se ha reconocido un =
                if (*caracter == '=') {
                    aceptar(IGUAL_IGUAL);
                } else if(*caracter == '>'){
                    aceptar(IGUAL_MAYOR);
                }else {
                    retroceder();
                    aceptar('=');
                }
                break;
            case 4: // Estado 4: Se ha reconocido un <
                if (*caracter == '=') {
                    aceptar(MENOR_IGUAL);
                } else if(*caracter == '<'){
                    estado = 13;
                }else {
                        retroceder();
                        aceptar('<');
                    }

                break;
            case 5: // Estado 5: Se ha reconocido un >
                if (*caracter == '=') {
                    aceptar(MAYOR_IGUAL);
                } else if (*caracter == '>') {
                    estado = 14;
                }else {
                    retroceder();
                    aceptar('>');
                }
                break;
            case 6: // Estado 6: Se ha reconocido un !
                if (*caracter == '=') {
                    aceptar(DISTINTO);
                } else {
                    retroceder();
                    aceptar('!');
                }
                break;
            case 7: // Estado 7: Se ha reconocido un /
                if (*caracter == '/') {
                    automataLineComments();
                    estado = 0;
                    ignorado = 0;
                } else if (*caracter == '*') {
                    automataBlockComments();
                    estado = 0;
                    ignorado = 0;
                } else if (*caracter == '+') {
                    automataNestedComments();
                    estado = 0;
                    ignorado = 0;
                } else if( *caracter == '=' ){
                    aceptar(DIVISION_IGUAL);
                }else{
                    retroceder();
                    aceptar('/');
                }
                break;
            case 8: // Estado 8: Se ha reconocido un .
                // Si el siguiente caracter es un digito se llama al automata de numeros flotantes
                if (isdigit(*caracter)) {
                    automataDecimalDigitNoStartingUS();
                    estado = 0;
                    ignorado = 0;
                    // Si el siguiente caracter no es un digito se acepta el componente lexico punto
                } else if( *caracter == '.'){
                    estado = 10;
                } else {
                    retroceder();
                    aceptar('.');
                }
                break;
            case 9: // Estado 9: Se ha reconocido un %
                if (*caracter == '=') {
                    aceptar(MODULO_IGUAL);
                } else {
                    retroceder();
                    aceptar('%');
                }
                break;
            case 10: // Estado 10: Se ha reconocido un ..
                if (*caracter == '.') {
                    aceptar(PUNTO_PUNTO_PUNTO);
                } else {
                    retroceder();
                    aceptar(PUNTO_PUNTO);
                }
                break;
            case 11: // Estado 11: Se ha reconocido un &
                if (*caracter == '&') {
                    aceptar(AND_AND);
                } else if (*caracter == '=') {
                    aceptar(AND_IGUAL);
                }else {
                    retroceder();
                    aceptar('&');
                }
                break;
            case 12: // Estado 12: Se ha reconocido un |
                if (*caracter == '|') {
                    aceptar(OR_OR);
                } else if (*caracter == '=') {
                    aceptar(OR_IGUAL);
                }else {
                    retroceder();
                    aceptar('|');
                }
                break;
            case 13: // Estado 13: Se ha reconocido un <<
                if (*caracter == '=') {
                    aceptar(MENOR_MENOR_IGUAL);
                } else {
                    retroceder();
                    aceptar(MENOR_MENOR);
                }
                break;
            case 14: // Estado 14: Se ha reconocido un >>
                if (*caracter == '=') {
                    aceptar(MAYOR_MAYOR_IGUAL);
                } else if(*caracter == '>'){
                    estado = 15;
                }else {
                    retroceder();
                    aceptar(MAYOR_MAYOR);
                }
                break;
            case 15: // Estado 15: Se ha reconocido un >>>
                if (*caracter == '=') {
                    aceptar(MAYOR_MAYOR_MAYOR_IGUAL);
                } else {
                    retroceder();
                    aceptar(MAYOR_MAYOR_MAYOR);
                }
                break;
            case 16: // Estado 16: Se ha reconocido un *
                if (*caracter == '=') {
                    aceptar(POR_IGUAL);
                } else {
                    retroceder();
                    aceptar('*');
                }
                break;
            case 17: // Estado 17: Se ha reconocido un ^
                if (*caracter == '=') {
                    aceptar(ELEVADO_IGUAL);
                } else if(*caracter == '^'){
                    estado = 18;
                }else {
                    retroceder();
                    aceptar('^');
                }
                break;
            case 18: // Estado 18: Se ha reconocido un ^^
                if (*caracter == '=') {
                    aceptar(ELEVADO_ELEVADO_IGUAL);
                } else {
                    retroceder();
                    aceptar(ELEVADO_ELEVADO);
                }
                break;
            case 19: // Estado 19: Se ha reconocido un ~
                if (*caracter == '=') {
                    aceptar(TILDE_IGUAL);
                } else {
                    retroceder();
                    aceptar('~');
                }
                break;

        }

    // Bucle que se ejecuta mientras no se llegue al final del fichero y no se haya aceptado un componente léxico
    } while (*caracter != EOF && aceptado == 0);

    return componenteLexico;
}


// Función que inicializa el analizador léxico, inicializando el sistema de entrada
void inicializarAnalizadorLexico(char *ficheroEntrada) {
    inicializarSistemaEntrada(ficheroEntrada);
}

// Función que finaliza el analizador léxico, finalizando el sistema de entrada
void finalizarAnalizadorLexico() {
    finalizarSistemaEntrada();
}





