#ifndef geral_h
#define geral_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

typedef struct registro
{
    int chave;
    long int dado1;
    char dado2[1000];
    char dado3[500];
} Registro;

FILE *criarArquivo(int metodo_Pesquisa, int nro_Registros, int tipo_Ordenacao);
void arrayToInteger(int *array_Parametros, int argc, char *argv[]);

#endif