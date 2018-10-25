#include "Lista.h"
#include <memory.h>


void ls_Crear(TLista *pLs, size_t TamanioDato) {
    pLs->Corriente = NULL;
    pLs->Primero = NULL;
    pLs->TamanioDato = TamanioDato;
}


void ls_Vaciar(TLista *pLs) {
    TNodoSimple *pNodo, *siguiente;
    for (pNodo = pLs->Primero; (pNodo); pNodo = siguiente) {
        siguiente = pNodo->Siguiente;
        free(pNodo->Elem);
        free(pNodo);
    }
    pLs->Primero = pLs->Corriente = NULL;
}


int ls_Vacia(TLista Ls) {
    return (Ls.Primero == NULL);
}


void ls_ElemCorriente(TLista Ls, void *pE) {
    memcpy(pE, Ls.Corriente->Elem, Ls.TamanioDato);
}


void ls_ModifCorriente(TLista *pLs, void *pE) {
    memcpy(pLs->Corriente->Elem, pE, pLs->TamanioDato);
}


int ls_MoverCorriente(TLista *pLs, TMovimiento_Ls M) {
    switch (M) {
        case LS_PRIMERO:
            pLs->Corriente = pLs->Primero;
            break;
        case LS_SIGUIENTE:
            if (pLs->Corriente->Siguiente == NULL)
                return FALSE;
            else
                pLs->Corriente = pLs->Corriente->Siguiente;
            break;
        case LS_ANTERIOR:
            return FALSE;
    }
    return TRUE;
}


void ls_BorrarCorriente(TLista *pLs) {
    TNodoSimple *PNodo = pLs->Corriente;
    if (pLs->Corriente == pLs->Primero) {
        pLs->Primero = pLs->Corriente->Siguiente;
        pLs->Corriente = pLs->Primero;
    } else {
        TNodoSimple *PAux = pLs->Primero;
        while (PAux->Siguiente != pLs->Corriente)
            PAux = PAux->Siguiente;
        PAux->Siguiente = pLs->Corriente->Siguiente;
        if (PAux->Siguiente) //Si no es el último
            pLs->Corriente = PAux->Siguiente;
        else
            pLs->Corriente = PAux; //Si es el último queda en el anterior al
//borrado
    }
    free(PNodo->Elem);
    free(PNodo);
}


int ls_Insertar(TLista *pLs, TMovimiento_Ls M, void *pE) {
    TNodoSimple *pNodo = (TNodoSimple *) malloc(sizeof(TNodoSimple));
    if (!pNodo)
        return FALSE; //No hay memoria disponible
    if ((pLs->Primero == NULL) || (M == LS_PRIMERO) ||
        ((M == LS_ANTERIOR) && (pLs->Primero == pLs->Corriente))) {
//Si está vacía o hay que insertar en el primero o
//hay que insertar en el anterior y el actual es el primero
        pNodo->Siguiente = pLs->Primero;
        pLs->Primero = pLs->Corriente = pNodo;
    } else {
        if (M == LS_SIGUIENTE) {
            pNodo->Siguiente = pLs->Corriente->Siguiente;
            pLs->Corriente->Siguiente = pNodo;
        } else //LS_ANTERIOR
        {
            TNodoSimple *pAux = pLs->Primero;
            while (pAux->Siguiente != pLs->Corriente)
                pAux = pAux->Siguiente;
            pAux->Siguiente = pNodo;
            pNodo->Siguiente = pLs->Corriente;
        }
    }
    pNodo->Elem = malloc(pLs->TamanioDato);
    memcpy(pNodo->Elem, pE, pLs->TamanioDato);
    pLs->Corriente = pNodo;
    return TRUE;
}
