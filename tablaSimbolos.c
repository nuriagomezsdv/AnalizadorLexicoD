
#include <malloc.h>
#include <string.h>
#include "tablaSimbolos.h"
#include "abb.h"

// Definimos el número de palabras reservadas del lenguaje D
#define NUM_PALABRAS_RESERVADAS 113

// Definimos la tabla de simbolos como un abb
abb tablaSimbolos;

// Función que crea un componente léxico
void crearCompLexico(ComponenteLexico *componenteLexico, int compLexico, char *lexema){
    // Introducimos el componente léxico en el campo componente léxico
    componenteLexico->compLexico = compLexico;
    // Reservamos memoria para el lexema del componente léxico
    componenteLexico->lexema = (char *) malloc(sizeof(char) * strlen(lexema) + 1);
    // Copiamos la palabra reservada en el lexema del componente lexico
    // Al haber reservado memoria para strlen(lexema)+1 caracteres, no hay que preocuparse por el \0, se va a copiar automáticamente
    strcpy(componenteLexico->lexema, lexema);
}

// Función que inicializa la tabla de símbolos
void inicializarTablaSimbolos(){
    // Introducimos las palabras reservadas en la tabla de símbolos
    ComponenteLexico componentesLexicos[NUM_PALABRAS_RESERVADAS];
    // Creamos los componentes léxicos de las palabras reservadas
    // Introducimos las palabras reservadas en el array buscando un orden en el que el árbol quede lo más equilibrado posible para que la búsqueda sea más eficiente
    crearCompLexico(&componentesLexicos[0],NOTHROW, "nothrow");
    crearCompLexico(&componentesLexicos[1], NEW, "new");
    crearCompLexico(&componentesLexicos[2], null, "new");
    crearCompLexico(&componentesLexicos[3], GOTO, "goto");
    crearCompLexico(&componentesLexicos[4], STATIC, "static");
    crearCompLexico(&componentesLexicos[5], SHARED, "shared");
    crearCompLexico(&componentesLexicos[6], SUPER, "super");
    crearCompLexico(&componentesLexicos[7], SWITCH, "switch");
    crearCompLexico(&componentesLexicos[8], SYNCHRONIZED, "syncronized");
    crearCompLexico(&componentesLexicos[9], STRUCT, "struct");
    crearCompLexico(&componentesLexicos[10], SHORT, "short");
    crearCompLexico(&componentesLexicos[11], SCOPE, "scope");
    crearCompLexico(&componentesLexicos[12], DELEGATE, "delegate");
    crearCompLexico(&componentesLexicos[13], DEBUG, "debug");
    crearCompLexico(&componentesLexicos[14], DEPRECATED, "deprecated");
    crearCompLexico(&componentesLexicos[15], DEFAULT, "default");
    crearCompLexico(&componentesLexicos[16], DCHAR, "dchar");
    crearCompLexico(&componentesLexicos[17], DO, "do");
    crearCompLexico(&componentesLexicos[18], DOUBLE, "double");
    crearCompLexico(&componentesLexicos[19], DELETE, "delete");
    crearCompLexico(&componentesLexicos[20],PROTECTED, "protected");
    crearCompLexico(&componentesLexicos[21], PRAGMA, "pragma");
    crearCompLexico(&componentesLexicos[22], PURE, "pure");
    crearCompLexico(&componentesLexicos[23], PACKAGE, "package");
    crearCompLexico(&componentesLexicos[24], PRIVATE, "private");
    crearCompLexico(&componentesLexicos[25], PUBLIC, "public");
    crearCompLexico(&componentesLexicos[26], WCHAR, "wchar");
    crearCompLexico(&componentesLexicos[27], WHILE, "while");
    crearCompLexico(&componentesLexicos[28], WITH, "with");
    crearCompLexico(&componentesLexicos[29], BOOL, "bool");
    crearCompLexico(&componentesLexicos[30], BREAK, "break");
    crearCompLexico(&componentesLexicos[31], BYTE, "byte");
    crearCompLexico(&componentesLexicos[32], BODY, "body");
    crearCompLexico(&componentesLexicos[33], ENUM, "enum");
    crearCompLexico(&componentesLexicos[34], ELSE, "else");
    crearCompLexico(&componentesLexicos[35], EXPORT, "export");
    crearCompLexico(&componentesLexicos[36], EXTERN, "extern");
    crearCompLexico(&componentesLexicos[37], IN, "in");
    crearCompLexico(&componentesLexicos[38], IFLOAT, "ifloat");
    crearCompLexico(&componentesLexicos[39], INVARIANT, "invariant");
    crearCompLexico(&componentesLexicos[40], IS, "is");
    crearCompLexico(&componentesLexicos[41], IREAL, "ireal");
    crearCompLexico(&componentesLexicos[42], IMPORT, "import");
    crearCompLexico(&componentesLexicos[43], INT, "int");
    crearCompLexico(&componentesLexicos[44], INTERFACE, "interface");
    crearCompLexico(&componentesLexicos[45], INOUT, "inout");
    crearCompLexico(&componentesLexicos[46], IMPORT, "import");
    crearCompLexico(&componentesLexicos[47], IMMUTABLE, "immutable");
    crearCompLexico(&componentesLexicos[48], IF, "if");
    crearCompLexico(&componentesLexicos[49], IDOUBLE, "idouble");
    crearCompLexico(&componentesLexicos[50], MIXIN, "mixin");
    crearCompLexico(&componentesLexicos[51], MODULE, "module");
    crearCompLexico(&componentesLexicos[52], MACRO, "macro");
    crearCompLexico(&componentesLexicos[53], OUT, "out");
    crearCompLexico(&componentesLexicos[54], OVERRIDE, "override");
    crearCompLexico(&componentesLexicos[55], REF, "ref");
    crearCompLexico(&componentesLexicos[56], RETURN, "return");
    crearCompLexico(&componentesLexicos[57], REAL, "real");
    crearCompLexico(&componentesLexicos[58], ULONG, "ulong");
    crearCompLexico(&componentesLexicos[59], UCENT, "ucent");
    crearCompLexico(&componentesLexicos[60], UNITTEST, "unittest");
    crearCompLexico(&componentesLexicos[61], UBYTE, "ubyte");
    crearCompLexico(&componentesLexicos[62], USHORT, "ushort");
    crearCompLexico(&componentesLexicos[63], UINT, "uint");
    crearCompLexico(&componentesLexicos[64], UNION, "union");
    crearCompLexico(&componentesLexicos[65], USHORT, "ushort");
    crearCompLexico(&componentesLexicos[66], ALIGN, "align");
    crearCompLexico(&componentesLexicos[67], ASSERT, "assert");
    crearCompLexico(&componentesLexicos[68], ASM, "asm");
    crearCompLexico(&componentesLexicos[69], AUTO, "auto");
    crearCompLexico(&componentesLexicos[70], ALIAS, "alias");
    crearCompLexico(&componentesLexicos[71], ABSTRACT, "abstract");
    crearCompLexico(&componentesLexicos[72], CFLOAT, "cfloat");
    crearCompLexico(&componentesLexicos[73], CATCH, "catch");
    crearCompLexico(&componentesLexicos[74], CDOUBLE, "cdouble");
    crearCompLexico(&componentesLexicos[75], CAST, "cast");
    crearCompLexico(&componentesLexicos[76], CASE, "case");
    crearCompLexico(&componentesLexicos[77], CENT, "cent");
    crearCompLexico(&componentesLexicos[78], CONST, "const");
    crearCompLexico(&componentesLexicos[79], CLASS, "class");
    crearCompLexico(&componentesLexicos[80], CONTINUE, "continue");
    crearCompLexico(&componentesLexicos[81], CREAL, "creal");
    crearCompLexico(&componentesLexicos[82], CHAR, "char");
    crearCompLexico(&componentesLexicos[83], CDOUBLE, "cdouble");
    crearCompLexico(&componentesLexicos[84], FOR, "for");
    crearCompLexico(&componentesLexicos[85], FOREACH, "foreach");
    crearCompLexico(&componentesLexicos[86], FUNCTION, "function");
    crearCompLexico(&componentesLexicos[87], FOREACH_REVERSE, "foreach_reverse");
    crearCompLexico(&componentesLexicos[88], FINAL, "final");
    crearCompLexico(&componentesLexicos[89], FINALLY, "finally");
    crearCompLexico(&componentesLexicos[90], FLOAT, "float");
    crearCompLexico(&componentesLexicos[91], FALSE, "false");
    crearCompLexico(&componentesLexicos[92], LAZY, "lazy");
    crearCompLexico(&componentesLexicos[93], LONG, "long");
    crearCompLexico(&componentesLexicos[94], TRUE, "true");
    crearCompLexico(&componentesLexicos[95], THIS, "this");
    crearCompLexico(&componentesLexicos[96], TYPEID, "typeid");
    crearCompLexico(&componentesLexicos[97], TYPEOF, "typeof");
    crearCompLexico(&componentesLexicos[98], TRY, "try");
    crearCompLexico(&componentesLexicos[99], THROW, "throw");
    crearCompLexico(&componentesLexicos[100], TEMPLATE, "template");
    crearCompLexico(&componentesLexicos[101], VERSION, "version");
    crearCompLexico(&componentesLexicos[102], VOID, "void");
    crearCompLexico(&componentesLexicos[103], file, "__FILE__");
    crearCompLexico(&componentesLexicos[104], line, "__LINE__");
    crearCompLexico(&componentesLexicos[105], module, "__MODULE__");
    crearCompLexico(&componentesLexicos[106], function, "__FUNCTION__");
    crearCompLexico(&componentesLexicos[107], parameters, "__parameters");
    crearCompLexico(&componentesLexicos[108], file_full_path, "__FILE_FULL_PATH__");
    crearCompLexico(&componentesLexicos[109], pretty_function, "__PRETTY_FUNCTION__");
    crearCompLexico(&componentesLexicos[110], gshared, "__gshared");
    crearCompLexico(&componentesLexicos[111], traits, "__traits");
    crearCompLexico(&componentesLexicos[112], vector, "__vector");

    // Insertamos los componentes léxicos en la tabla de símbolos
    for(int i = 0; i < NUM_PALABRAS_RESERVADAS; i++){
        insertar(&tablaSimbolos, componentesLexicos[i]);
    }

}

// Función que busca un lexema en la tabla de símbolos
void buscarComponenteLexico(ComponenteLexico* componenteLexico){
    ComponenteLexico compBusqueda = {0, NULL};
    // Buscamos el lexema en la tabla de símbolos
    // Si lo encontramos, se le asigna el componente léxico correspondiente
    // Si no lo encontramos, le asignamos el componente léxico ID y lo insertamos en la tabla de simbolos
    // Buscar_nodo asignara el ComponenteLexico correspondiente a compLexico en caso de encontrar el lexema
    buscar_nodo(tablaSimbolos, componenteLexico->lexema, &compBusqueda);
    // Si no se ha encontrado el lexema en la tabla de símbolos, lo añadimos como un ID
    if(compBusqueda.compLexico == 0){
        // Asignamos el componente léxico ID
        componenteLexico->compLexico = ID;
        compBusqueda.compLexico = ID;
        // Realizamos una copia del lexema del componente léxico para asignarselo a compBusqueda e introducirlo en la tabla de símbolos
        char *lexema = (char *) malloc(sizeof(char) * strlen(componenteLexico->lexema) + 1);
        strcpy(lexema, componenteLexico->lexema);
        compBusqueda.lexema = lexema;
        // Introducimos el componente léxico en la tabla de símbolos
        insertar(&tablaSimbolos, compBusqueda);
    }else{
        // Asignamos el componente léxico correspondiente
        componenteLexico->compLexico = compBusqueda.compLexico;
    }

}

// Funcion que limpia la memoria utilizada por la tabla de símbolos
void limpiarMemoriaTablaSimbolos(){
    // Liberamos la memoria utilizada por la tabla de símbolos
    destruir(&tablaSimbolos);
}

// Función que imprime el contenido de la tabla de símbolos
void imprimirTablaSimbolos(){
    // Imprimimos la tabla de símbolos
    printf("\n  ------ TABLA DE SÍMBOLOS ------\n");
    imprimirABB(tablaSimbolos);
    printf("  -------------------------------\n");
}