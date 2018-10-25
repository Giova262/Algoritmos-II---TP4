#ifndef INC_2017_2_7541_TP3_PARSER_H
#define INC_2017_2_7541_TP3_PARSER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PALABRA 100

typedef struct{
    char palabra[MAX_PALABRA];
    unsigned int pagina;
    unsigned int linea;
    unsigned int caracter;
}UbicacionP;


typedef struct TDA_PA{
    char palabra[MAX_PALABRA];
    int ubicacion;
    int linea;
    int pagina;
    FILE* archivo_entrada;
    FILE* archivo_configuracion;
    char* nombre_archivo_entrada;
    char* nombre_archivo_configuracion;
}TDA_PA;


/*
 * recibe el archivo a parsear y un archivo de configuración. El archivo posee el
 * caracter de cambio de página y los caracteres separadores de palabras
 */
void PA_CREAR(TDA_PA *p, char *archConfiguracion, char *archDocumento);

/*
 * destruye la estructura del TDA
 */
void PA_DESTRUIR(TDA_PA *p);

/*
 * devuelve la palabra del archivo de entrada, con la pagina, línea y posición
 * en la línea.
 * RETURN: Cuando no hay más palabras retorna FALSE.
 */
int PA_SIGPALABRA(TDA_PA *p, UbicacionP *up, char *palabra);

#endif //INC_2017_2_7541_TP3_PARSER_H
