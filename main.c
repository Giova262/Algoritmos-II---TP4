#include <stdio.h>
#include <mem.h>
#include "glosario.h"
#include "elemp.h"

#define INDEXER_INI "config.txt"



int main(int argc, char **argv) {
    // parsing
    int i;
    char *palabra = NULL;
    int show_ranking = FALSE;
    char *docFileName = NULL;

    TDAGlosario glosario;
    TDA_ElemP resultado;
    TLista listaPalabra;
    char lineaReporte[MAX_REPORTE];
    TLista listaRanking;

    // Parseo de argumentos
    for (i = 1; i < argc; i++) {
        char* arg=argv[i] ;

        if (strcmp(arg, "-cp") == 0) {
            /* Tiene que existir próximo argumento, si no es un error */
            if (!(i + 1 < argc)) {
                fprintf(stderr, "-cp se requiere la palabra");
                return EXIT_FAILURE;
            }

            palabra = argv[++i];
            continue;
        }

        if (strcmp(arg, "-rp") == 0) {
            show_ranking = TRUE;
            continue;
        }

        // el nombre del documento puede venir en cualquier lado
        docFileName = arg;
    }

   if (!CrearGlosario(&glosario, docFileName, INDEXER_INI)) {

        fprintf(stderr, "Error al crear el Glosario para el documento \"%s\"\n", docFileName);
        return EXIT_FAILURE;
    }

    ls_Crear(&listaPalabra, MAX_REPORTE);
    ls_Crear(&listaRanking, sizeof(TDA_ElemP));

    if (palabra) {
        if (!ConsultarpalabraGlosario(&glosario, palabra, &listaPalabra)) {
            fprintf(stderr, "Error al consultar el Glosario con la palabra \"%s\"\n", palabra);
        }

        // Mostramos la lista de ocurrencias de la palabra
        if (!ls_Vacia(listaPalabra)) {
            puts(palabra);
            ls_MoverCorriente(&listaPalabra, LS_PRIMERO);
            do {
                ls_ElemCorriente(listaPalabra, lineaReporte);
                puts(lineaReporte);
            } while (ls_MoverCorriente(&listaPalabra, LS_SIGUIENTE));
        }
    }

    if (show_ranking) {
        if (!Ranking_palabras_Glosario(&glosario, &listaRanking)) {
            fprintf(stderr, "Error al consultar el ranking de palabras\n");
        }

        // Mostramos la lista lista ranking de palabras
        if (!ls_Vacia(listaRanking)) {
            ls_MoverCorriente(&listaRanking, LS_PRIMERO);
            do {
                ls_ElemCorriente(listaRanking,&resultado);
                //puts(lineaRanking);
                printf("repeticiones:%d %10s\n",resultado.cantOcurrencias,resultado.palabra);
            } while (ls_MoverCorriente(&listaRanking, LS_SIGUIENTE));
        }
    }

    ls_Vaciar(&listaPalabra);
    ls_Vaciar(&listaRanking);

    if (!DestruirGlosario(&glosario)) {
        fprintf(stderr, "Error al destruir el Glosario");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

