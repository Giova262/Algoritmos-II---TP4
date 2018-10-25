#include <stdio.h>
#include<mem.h>
#include <stdlib.h>
#include <string.h>
//#include "tda-parser.h"
#include "parser.h"
#include "Lista.h"


/*Analiza los separadores del archivo configuraciones y los compara con los caracteres que va leyendo del archivo de entrada.
Devuelve 1 si el separador es de separa_palabra, devuelve 3 si el separador es de salto_linea, y devuelve 0 si no es separador*/


int chequeoDeTipoSeparadores2(FILE* archivo_configuracion,char caracter)

{
    int i;
    int j=1;
    char c;
    char tipo_separador[14];

    rewind(archivo_configuracion);
    c=getc(archivo_configuracion);

    do {

        if (c== '['){

            i=-1;
            c=getc(archivo_configuracion);
            while (c!=']'){
                i++;
                tipo_separador[i]=c;
                c=getc(archivo_configuracion);
            }
            i++;
            tipo_separador[i]='\0';

            while((c!='[')&&(c!=EOF)){

                c=getc(archivo_configuracion);

                if ( c=='"'){

                    c=getc(archivo_configuracion);
                    if((caracter==c)&&( strcmp(tipo_separador,"SEPARA_PALABRA")==0)){

                        j=0;
                        return 1;

                    }

                    if((caracter==c)&&( strcmp(tipo_separador,"SALTO_PAGINA")==0)){
                        j=0;
                        return 3;

                    }
                }
            }
        }
    } while(c!=EOF);

    if (j!=0) return 0;

}

void PA_CREAR(TDA_PA * p, char * archConfiguracion, char * archDocumento) {

    p->linea=1;
    p->pagina=1;
    p->ubicacion=1;
    p->archivo_entrada=fopen(archDocumento,"rt");
    p->archivo_configuracion=fopen(archConfiguracion,"rt");
}

/*Cierra los archivos entrada y configuracion, y destruye el tda.*/
void PA_DESTRUIR(TDA_PA * p) {

    if (p->archivo_entrada!=NULL)
        fclose(p->archivo_entrada);
    if (p->archivo_configuracion!=NULL)
        fclose(p->archivo_configuracion);
}


int PA_SIGPALABRA(TDA_PA * p, UbicacionP *up, char *palabra) {
    //HOLA MUNDO;CRUEL|JA MUNDO LOCO;HOLA
    //        SO
    int i=0;
    char c;


    c=getc(p->archivo_entrada);
    if( c==EOF ) return FALSE;

    up->caracter=p->ubicacion;

    while ((chequeoDeTipoSeparadores2(p->archivo_configuracion,c)!=1)&& (chequeoDeTipoSeparadores2(p->archivo_configuracion,c)!=3)&&(c!=EOF))
    {
        p->palabra[i]=c;
        i++;
        c=getc(p->archivo_entrada);
        p->ubicacion++;
        up->linea=p->linea;
        up->pagina=p->pagina;

    }

    p->palabra[i]='\0';
    p->ubicacion++;
    strcpy(up->palabra,p->palabra);
    strcpy(palabra,p->palabra);

    if (c=='\n')
    {
        p->ubicacion=1;
        p->linea++;
    }

    if ((chequeoDeTipoSeparadores2(p->archivo_configuracion,c)!=0)&&(chequeoDeTipoSeparadores2(p->archivo_configuracion,c)!=1))
    {
        p->ubicacion=1;
        p->linea=0;
        p->pagina++;
    }

    //printf("%s\n",palabra);


    return TRUE;
}
