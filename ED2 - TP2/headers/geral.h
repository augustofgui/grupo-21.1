#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct registro
{
    long int inscricao;
    float nota;
    char estado[2];
    char cidade[50];
    char curso[30];
} Registro;

void verificar_parametros(int argc, int nro_metodo, int nro_quantidade, int nro_situacao);
FILE *abrir_arquivo(char nome_arquivo[], char modo_abertura[]);
FILE *converter_para_binario(FILE *arquivo_texto);