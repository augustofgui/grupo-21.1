#ifndef geral_h
#define geral_h

/* ED2 - TP 1 -> https://github.com/augustofgui/ed2-tp1
    - Augusto Guilarducci (20.1.4012)
    - Caio Monteiro (20.1.4110)
    - Paulo Correa (20.1.4036)
    - Pedro Lucas Damasceno (20.1.4003)
*/

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

//Verificação dos parâmetros de execução
void verificar_parametros(int argc, char *argv[]);
//Criação do arquivo binário a partir dos parâmetros
FILE *criar_arquivo(int nro_metodo, int nro_registros, int nro_situacao);
//Imprimir resultado
void imprimir_registro(Registro x);
void imprimir_nao_encontrado(int nro_chave);

#endif