# AnalizadorLexicoD

## Descripción
Este analizador léxico se ha realizado para aprender de forma didáctica como desarrollar desde cero un analizador léxico teniendo en cuenta todos los factores, como por ejemplo el sistema de entrada, la tabla de símbolos o la gestión de la memoria. Para la realización del mismo se ha consultado la especificación del lenguaje D, más en concreto el listado de componentes léxicos.

## Ejecución
Para la compilación de este analizador léxico se descargará o clonará este repositorio y se insertarán todos los archivos en un mismo directorio. Una vez insertados, se abrirá una terminal Linux, se accederá al directorio con los archivos y se ejecutará el comando `make` para compilarlo.

Una vez compilado, el analizador léxico se ejecutará por terminal con el comando `./analizadorLexicoD [FICHERO_CODIGO_FUENTE.d]`. Con el fichero de ejemplo incluido en el repositorio: `./analizadorLexicoD regression.d`.

Como resultado de la ejecución se imprimirá por terminal la tabla de símbolos inicial (conteniendo solamente las palabras reservadas del lenguaje D) seguida de todos los componentes léxicos detectados en el código fuente, indicados con el formato __< ComponenteLexico , Lexema >__, y finalmente se imprimirá la tabla de símbolos resultante de añadir a la inicial los identificadores detectados en el código fuente.
