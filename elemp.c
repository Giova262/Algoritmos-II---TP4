#include <mem.h>
#include "elemp.h"

void TDA_ElemP_Crear(TDA_ElemP *e) {
    strcpy(e->palabra, "");
    ls_Crear(&e->listaOcurrencias, sizeof(UbicacionP));
    e->cantOcurrencias = 0;
}


void TDA_ElemP_SetPalabra(TDA_ElemP *e, const char * palabra) {
    strcpy(e->palabra, palabra);
}


int TDA_ElemP_strcmp(TDA_ElemP *e, const char * palabra) {
    return strcmp(e->palabra, palabra);
}


void TDA_ElemP_AgregarOcurrencia(TDA_ElemP *e, UbicacionP p) {
    ls_Insertar(&e->listaOcurrencias, LS_SIGUIENTE, &p);
    e->cantOcurrencias++;
}


void TDA_ElemP_Destruir(TDA_ElemP *e) {
    ls_Vaciar(&e->listaOcurrencias);
}

unsigned int TDA_ElemP_CantOcurrencias(TDA_ElemP *e) {
    return e->cantOcurrencias;
}
