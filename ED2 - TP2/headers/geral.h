#include <time.h>
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
FILE *converter_para_binario(FILE *arquivo_texto, char* argv);
void converter_para_txt(FILE *arquivo_binario, char* argv);
void imprimir_registro(Registro x);
void merge_sort(Registro *vetor, int margem_esquerda, int n);
void merge_sort_ascendente(Registro *vetor, int margem_esquerda, int nova_margem, int n);
void print_estatisticas(int nro_comparacoes, int nro_leituras, int nro_escritas, double tempo_execucao);