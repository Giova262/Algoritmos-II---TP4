#include <stdio.h>
#include "glosario.h"
#include "parser.h"
#include "elemp.h"

/*
 * Funcion para reportar las ocurrencias de una palabra
 */
void mostrarPalabra(TDA_ElemP eab) {
    UbicacionP u;
    puts(eab.palabra);

    if (!ls_Vacia(eab.listaOcurrencias)) {
        ls_MoverCorriente(&eab.listaOcurrencias, LS_PRIMERO);
        do {
            ls_ElemCorriente(eab.listaOcurrencias, &u);
            printf("pagina %d linea %d posicion %d\n", u.pagina, u.linea, u.caracter);

        } while (ls_MoverCorriente(&eab.listaOcurrencias, LS_SIGUIENTE));
    }

}

void eliminarElemP(TDA_ElemP eab) {
    TDA_ElemP_Destruir(&eab);
}


/*
 * Recorrido InOrder con una funcion para procesar el nodo
 * del arbol
 */
void InOrder(TAB ab, int MOV, void (*procesar)(TDA_ElemP)) {
    TDA_ElemP eab;
    int error;
    AB_MoverCte(&ab, MOV, &error);
    if (!error) {
        InOrder(ab, IZQ, procesar);
        AB_ElemCte(ab, &eab);
        procesar(eab);
        InOrder(ab, DER, procesar);
    }
}


int CrearGlosario(TDAGlosario *g, char *documento, char *arch_config) {
    TDA_PA parser;
    UbicacionP up;
    TDA_ElemP ep, epAux;
    char palabra[MAX_PALABRA];
    int salir = 0;
    int errCode;

    AB_Crear(&g->arbol, sizeof(TDA_ElemP));

    PA_CREAR(&parser, arch_config, documento);


    while (PA_SIGPALABRA(&parser, &up, palabra)) {

        if (AB_Vacio(g->arbol)) {
            TDA_ElemP_Crear(&epAux);
            TDA_ElemP_SetPalabra(&epAux, palabra);
            TDA_ElemP_AgregarOcurrencia(&epAux, up);
            AB_Insertar(&g->arbol, RAIZ, &epAux, &errCode);
        } else {
            AB_MoverCte(&g->arbol, RAIZ, &errCode);

            do {
                AB_ElemCte(g->arbol, &ep);

                if (TDA_ElemP_strcmp(&ep, palabra) == 1) {
                    AB_MoverCte(&g->arbol, IZQ, &errCode);
                    if (errCode) {
                        TDA_ElemP_Crear(&epAux);
                        TDA_ElemP_SetPalabra(&epAux, palabra);
                        TDA_ElemP_AgregarOcurrencia(&epAux, up);
                        AB_Insertar(&g->arbol, IZQ, &epAux, &errCode);
                        salir = 0;
                    } else {
                        salir = 1;
                    }
                }

                if (TDA_ElemP_strcmp(&ep, palabra) == -1) {
                    AB_MoverCte(&g->arbol, DER, &errCode);
                    if (errCode) {
                        TDA_ElemP_Crear(&epAux);
                        TDA_ElemP_SetPalabra(&epAux, palabra);
                        TDA_ElemP_AgregarOcurrencia(&epAux, up);
                        AB_Insertar(&g->arbol, DER, &epAux, &errCode);
                        salir = 0;
                    } else {
                        salir = 1;
                    }
                }

                if (TDA_ElemP_strcmp(&ep, palabra) == 0) {

                    ep.cantOcurrencias++;
                    ls_Insertar(&ep.listaOcurrencias,LS_SIGUIENTE,&up);

                    AB_ModifCte(&g->arbol,&ep);

                    salir = 0;
                }

            } while (salir == 1);
        }
    }

    return TRUE;
}


int ConsultarpalabraGlosario(TDAGlosario *g, char *palabra, TLista *lResultado) {
    int errCode;
    TDA_ElemP ep;
    int salir = 0;
    UbicacionP up;
    char lineaReporte[MAX_REPORTE];

    AB_MoverCte(&g->arbol, RAIZ, &errCode);

    do {
        AB_ElemCte(g->arbol, &ep);

        if (TDA_ElemP_strcmp(&ep, palabra) == 1) {
            AB_MoverCte(&g->arbol, IZQ, &errCode);
            if (errCode) {
                salir = 0; // no lo encontré
            } else {
                salir = 1;
            }
        }

        if (TDA_ElemP_strcmp(&ep, palabra) == -1) {
            AB_MoverCte(&g->arbol, DER, &errCode);
            if (errCode) {
                salir = 0; // no lo encontré
            } else {
                salir = 1;
            }
        }

        if (TDA_ElemP_strcmp(&ep, palabra) == 0) {
            // LLeno la lista
            ls_MoverCorriente(&ep.listaOcurrencias, LS_PRIMERO);
            do {
                ls_ElemCorriente(ep.listaOcurrencias, &up);
                sprintf(lineaReporte, "pagina %d linea %d posicion %d", up.pagina, up.linea, up.caracter);
                ls_Insertar(lResultado, LS_SIGUIENTE, lineaReporte);
            } while (ls_MoverCorriente(&ep.listaOcurrencias, LS_SIGUIENTE ));

            return TRUE;
        }
    } while(salir == 1);

    return FALSE;
}

int Proceso_2(TDA_ElemP eab,TLista* listaOcurrencias){
    TDA_ElemP cte,aux;


    if( ls_Vacia(*listaOcurrencias) ){
        ls_Insertar(listaOcurrencias,LS_PRIMERO,&eab);
    }
    else{
        ls_MoverCorriente(listaOcurrencias,LS_PRIMERO);
        do{
            ls_ElemCorriente(*listaOcurrencias,&cte);
            if(eab.cantOcurrencias>cte.cantOcurrencias ){
                continue;
            }
            if(eab.cantOcurrencias==cte.cantOcurrencias ){
                ls_Insertar(listaOcurrencias,LS_SIGUIENTE,&eab);
                return 0;
            }
            if(eab.cantOcurrencias<cte.cantOcurrencias ){
                ls_ElemCorriente(*listaOcurrencias,&aux);
                ls_ModifCorriente(listaOcurrencias,&eab);
                ls_Insertar(listaOcurrencias,LS_SIGUIENTE,&aux);
                return 0;
            }

        }while(ls_MoverCorriente(listaOcurrencias,LS_SIGUIENTE));
        ls_Insertar(listaOcurrencias,LS_SIGUIENTE,&eab);
    }
    return 1;
}

void LLenar_Lista_Rank(TAB a,int mov,TLista* listaOcurrencias){

    TDA_ElemP eab;
    int error;
    AB_MoverCte(&a,mov,&error);
    if( !error ){

        LLenar_Lista_Rank(a,IZQ,listaOcurrencias);
        AB_ElemCte(a,&eab);
        Proceso_2(eab,listaOcurrencias);
        LLenar_Lista_Rank(a,DER,listaOcurrencias);
    }
}

int Ranking_palabras_Glosario(TDAGlosario *g, TLista *lResultado) {
// Recorrido inorden y contar los elementos de la lista de los nodos.

    LLenar_Lista_Rank(g->arbol,RAIZ,lResultado);
    return TRUE;
}

int DestruirGlosario(TDAGlosario *g) {
    // Recorremos arbol para eliminar las estrucutras
    InOrder(g->arbol, RAIZ, eliminarElemP);
    AB_Vaciar(&g->arbol);
    return TRUE;
}
