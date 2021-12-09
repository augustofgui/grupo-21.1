#ifndef INTERCALACAO_SUBSTITUICAO_SELECAO_H
#define INTERCALACAO_SUBSTITUICAO_SELECAO_H

#include "geral.h"
#include "fita.h"
#include "intercalacao_ordenacao_interna.h"
#include <stdio.h>
#include <stdlib.h>

void intercalacao_substituicao_selecao(char argv[], int nro_quantidade, bool imprimir_dados);
void criar_blocos_ordenados_heap(FILE *arquivo_binario, int num_registros, Fitas *fitas, Estatistica *estatistica, bool imprimir_dados);
void intercalacao_balanceada_heap(Fita *origem, Fita *destino, int nro_registros, Estatistica * estatistica, bool imprimir_dados);
bool alguma_fita_disponivel(bool * vetor, int tam);
int acha_posicao_menor_reg_heap(Registro *vetor, int tam, int * quant_fitas);


#endif // INTERCALACAO_SUBSTITUICAO_SELECAO_H
