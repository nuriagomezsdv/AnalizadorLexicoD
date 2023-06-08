
Para la compilación de este analizador léxico se insertarán todos los archivos en un mismo directorio. Una vez insertados, se abrirá una terminal Linux, se accederá al directorio con los archivos y se ejecutará el comando make para compilarlo.

Una vez compilado, el analizador léxico se ejecutará por terminal con el comando ./analizadorLexicoD [FICHERO_CODIGO_FUENTE.d]. Por ejemplo ./analizadorLexicoD regression.d .

Como resultado de la ejecución se imprimirá por terminal la tabla de símbolos inicial (conteniendo solamente las palabras reservadas del lenguaje D) seguida de todos los componentes léxicos detectados en el código fuente, indicados con el formato < ComponenteLexico , Lexema >, y finalmente se imprimirá la tabla de símbolos resultante de añadir a la inicial los identificadores detectados en el código fuente.
