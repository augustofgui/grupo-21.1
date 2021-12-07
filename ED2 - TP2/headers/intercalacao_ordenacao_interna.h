#ifndef INTERCALACAO_ORDENACAO_INTERNA_H
#define INTERCALACAO_ORDENACAO_INTERNA_H

#include "geral.h"
#include "fita.h"
#include <stdio.h>
#include <stdlib.h>

// ----- Funções que executam a intercalação com ordenação interna.
void intercalacao_ordenacao_interna(char argv[], int nro_quantidade, bool imprimir_dados);
void criar_blocos_ordenados(FILE * arquivo_binario, int num_registros, Fitas * fitas, Estatistica * estatistica, bool imprimir_dados);
void intercalacao_balanceada(Fita * origem, Fita * destino, int nro_registros, int tam_antigo_bloco, Estatistica * estatistica, bool imprimir_dados);
int acha_posicao_menor_reg(Registro * vetor, int tam);

#endif // INTERCALACAO_ORDENACAO_INTERNA_H