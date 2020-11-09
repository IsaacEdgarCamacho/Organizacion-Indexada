# Organizacion Indexada
Características:
Soporta acceso secuencial, dinámico y por referencia.
Soporta clave primaria y secundarias. El contenido de la clave primaria no puede repetirse
en diferentes registros. Por otro lado las claves secundarias pueden tener duplicados.
Crear:
int I_CREATE (const char* nfisico, const campo *reg, const campo *cl_prim);
reg y cl_prim: Permiten inicializar la estructura del archivo según los datos que deba
contener (ver mas abajo). La clave primaria es obligatoria en esta organización y al ejecutar
I_CREATE, además de crear el archivo, se creará el índice por la clave primaria.
Devuelve un código de resultado(RES_OK / RES_ERROR/ RES_EXISTE)
Abrir:
int I_OPEN (const char* nombre_fisico, int modo);
modo: Lectura/Escritura.
Devuelve el file handler si puede abrir el archivo o RES_NULL si no.
Cerrar:
int I_CLOSE (int handler);
875.06 Organización de Datos.
Operaciones en Organizaciones de Archivos
Devuelve un código de resultado(RES_OK / RES_ERROR).
Agregar índice:
int I_ADD_INDEX(int handler, const campo *cl);
cl : Describe los campos por los cuales se creará el índice en cuestión (Ver mas abajo).
Devuelve el ID del índice creado o un código de error. El ID 0 se reserva para la clave
primaria.
Esta primitiva permite agregar los índices secundarios que sean necesarios. Por ser
secundarios, es importante tener en cuenta que estos índices podrán tener valores
repetidos.
Devuelve : ( IndexId / RES_ERROR / RES_EXISTE_INDICE )
Quitar índice:
int I_DROP_INDEX(int handler, int indexId);
indexId: Id devuelto por int I_ADD_INDEX. No puede eliminarse el IndexId 0 pues es la
clave primaria.
Devuelve un código de error. (RES_OK / RES_NO_EXISTE_INDICE / RES_ES_PRIM /
RES_ERROR ). Devuelve RES_ES_PRIM si se intenta eliminar el índice principal del archivo.
Verificar existencia de un índice
int I_IS_INDEX (int handler, campo *clave)
Verifica si existe un índice creado según la clave indicada en cl. Siempre antes de usar un
índice que no sea el principal debe utilizarse I_IS_INDEX para averiguar su Id.
Devuelve: (Index Id / RES_NO_EXISTE_INDICE / RES_ERROR)
Posicionar:
int I_START(int handler, int indexId, char* operador, const void* val_ref);
indexId: Id del índice devuelto por I_ADD_INDEX o 0 para la clave primaria. Permite
identificar el índice que se desea inicializar.
operador: puede ser cualquier string representando un operador relacional: “=”, “>”, “<”,
“>=”, “<=”, “!=”.
val_ref: es un puntero a un registro con valores validos solo en los campos que definen al
índice que referencia el parámetro indexId".
Devuelve un código de resultado(RES_OK / RES_ERROR / RES_NO_EXISTE_INDICE. /
RES_NO_EXISTE ). Devuelve RES_NO_EXISTE si no hay ningún registro que cumpla la
condición deseada.
Esta primitiva inicializa el índice indicado por IndexId para hacer lectura secuencial.
Posiciona el record pointer del índice en el primer registro que cumple la condición al
comparar el valor de su clave (la correspondiente al índice que se está inicializando, no
necesariamente la clave primaria) con val_ref, usando operador.
I_START no devuelve ningún registro de datos (no hace ninguna lectura), sólo posiciona el
record pointer. Se debe usar I_READNEXT para leer el registro apuntado por el record
pointer y es un error intentar utilizar I_READ a tal fin.
975.06 Organización de Datos.
Operaciones en Organizaciones de Archivos
La utilización de I_START se considera como un acceso de tipo dinámico. Al realizar
I_START se posiciona un puntero en un índice (primario o secundario) quedando disponible
para luego recorrer el archivo mediante accesos de tipo secuencial (con el I_READNEXT,
explicado a continuación).
A continuación se detalla la forma en que se realizan las búsquedas de registros en el índice.