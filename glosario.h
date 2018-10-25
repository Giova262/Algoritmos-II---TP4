#ifndef INC_2017_2_7541_TP3_GLOSARIO_H
#define INC_2017_2_7541_TP3_GLOSARIO_H

/*
 * Este TDA deberá poder devolver cualquier palabra incluida en el documento del TDA así como
 * la cantidad de veces que aparece, pagina, líneas y posición dentro del documento.
 * El TDA se implementa con un árbol binario, el cual estará ordenado por palabra. A su vez cada
 * palabra contendrá una lista con la página, línea y posición de la palabra.
 */

#include "Lista.h"
#include "ab.h"

#define MAX_REPORTE 200
#define MAX_RANKING 200


typedef struct {
     TAB arbol;
} TDAGlosario;


/*
 * Esta primitiva crea la estructura parseando el documento pasado por parámetro teniendo en
 * cuenta la configuración para parsearlo y deja lista la estructura para su explotación.
 */
int CrearGlosario(TDAGlosario * g, char * documento, char * arch_config);

/*
 * Esta primitiva elimina la información de la estructura.
 */
int DestruirGlosario(TDAGlosario * g);

/*
 * Esta primitiva devuelve una lista con las páginas, líneas y posición de la palabra dentro del
 * documento del TDA. En caso de no existir la palabra devuelve error, sino true y la lista
 * resultado
 */
int ConsultarpalabraGlosario(TDAGlosario * g, char * palabra, TLista * lResultado);

/*
 * Esta primitiva devuelve una lista con las palabras contenidas en el TDA y la cantidad de
 * apariciones en el documento, ordenada de menor a mayor por este número de apariciones.
 */
int Ranking_palabras_Glosario(TDAGlosario * g, TLista * lResultado);


#endif //INC_2017_2_7541_TP3_GLOSARIO_H
