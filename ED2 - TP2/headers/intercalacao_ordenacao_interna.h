#ifndef INTERCALACAO_ORDENACAO_INTERNA_H
#define INTERCALACAO_ORDENACAO_INTERNA_H

#include "geral.h"
#include <stdio.h>
#include <stdlib.h>


#define TEXT 50
#define TAM_BLOCO 20
#define NUM_FITAS_ENTRADA 20
#define NUM_FITAS_SAIDA 20
#define NUM_FITAS NUM_FITAS_ENTRADA + NUM_FITAS_SAIDA

typedef struct {
    FILE * arquivo;
    int quant_itens;
    int tam_ultimo_bloco;
    bool preenchida;
} Fita;

typedef struct {
    Fita entrada[NUM_FITAS_ENTRADA];
    Fita saida[NUM_FITAS_SAIDA];
    bool fitas_preenchidas[NUM_FITAS];
} Fitas;

void intercalacao_ordenacao_interna(char argv[], int nro_quantidade, bool imprimir_dados);
void criar_blocos_ordenados(FILE * arquivo_binario, int num_registros, Fitas * fitas, Estatistica * estatistica, bool imprimir_dados);
void escreve_na_fita(FILE * arquivo_binario, Fita * fita_destino, int tam, Estatistica * estatistica, bool imprimir_dados);
void intercalacao_balanceada(Fita * origem, Fita * destino, int nro_registros, int tam_antigo_bloco, Estatistica * estatistica, bool imprimir_dados);
void fitas_rewind(Fitas * fitas);
int acha_posicao_menor_reg(Registro * vetor, int tam);
Fitas cria_fitas();
void cria_fitas_tipo(Fita * vetor, int n, char * tipo);

#endif // INTERCALACAO_ORDENACAO_INTERNA_H