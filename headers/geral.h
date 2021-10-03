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
    char dado3[5000];
} Registro;

void verif_Parametros(int argc);
void array_ToInteger(int argc, char *argv[]);
FILE *criarArquivo(int metodo_Pesquisa, int nro_Registros, int tipo_Ordenacao);
void imprimirRegistro(Registro x);

#endif