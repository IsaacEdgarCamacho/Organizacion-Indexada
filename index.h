#ifndef _INDEX_H_
#define _INDEX_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct campo{
    char nombre[15];
    int tipo;
    int longitud;
}campo;

typedef campo registro[];
typedef campo clave[];

int I_CREATE(char* nfisico, registro reg, clave cl);


#endif //_INDEX_H_