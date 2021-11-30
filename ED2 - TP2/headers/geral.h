#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct registro
{
    long int inscricao;
    float nota;
    char estado_cidade_curso[82];
} Registro;

void verificar_parametros(int argc, int nro_metodo, int nro_quantidade, int nro_situacao);
FILE *abrir_arquivo(char nome_arquivo[], char modo_abertura[]);
FILE *converter_para_binario(FILE *arquivo_texto);
void converter_para_txt(FILE *arquivo_binario);
void imprimir_registro(Registro x);
void merge_sort(Registro *vetor, int margem_esquerda, int n, int nro_situacao);
void merge_sort_crescente(int *vetor, int margem_esquerda, int nova_margem, int n);
void merge_sort_decrescente(int *vetor, int margem_esquerda, int nova_margem, int n);