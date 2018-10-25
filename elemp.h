#ifndef INC_2017_2_7541_TP3_ELEMP_H
#define INC_2017_2_7541_TP3_ELEMP_H

#include "Lista.h"
#include "parser.h"


/* TDA ElemPalabra del elemento del arbol binario */

typedef struct {
    char palabra[MAX_PALABRA];
    TLista listaOcurrencias;
    unsigned int cantOcurrencias;
} TDA_ElemP;

/*
 * Crea el elemento del Arbol binario
 */
void TDA_ElemP_Crear(TDA_ElemP *e);

/*
 * Guarda el nombre de la palabra
 */
void TDA_ElemP_SetPalabra(TDA_ElemP *e, const char * palabra);

/*
 * Compara la clave con la palabra. Retorna lo que devuelve strcmp de la comparacion
 */
int TDA_ElemP_strcmp(TDA_ElemP *e, const char * palabra);

/*
 * Se agrega la ocurrencia de la palabra en la lista
 */
void TDA_ElemP_AgregarOcurrencia(TDA_ElemP *e, UbicacionP p);

/*
 * Retorna la cantidad de Ocurrencias de de la palabra
 */
unsigned int TDA_ElemP_CantOcurrencias(TDA_ElemP *e);

/*
 * Destruye el elemento
 */
void TDA_ElemP_Destruir(TDA_ElemP *e);

#endif //INC_2017_2_7541_TP3_ELEMP_H
