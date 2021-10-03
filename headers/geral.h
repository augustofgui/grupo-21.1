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

//Verificação dos parâmetros e adequação char->int
void verif_Parametros(int argc);
void array_ToInteger(int argc, char *argv[]);
//Criação do arquivo binário a partir dos parâmetros da execução
FILE *criar_Arquivo(int metodo_Pesquisa, int nro_Registros, int tipo_Ordenacao);
//Imprimir resultado
void imprimir_Registro(Registro x);
void imprimir_NaoEncontrado();

#endif