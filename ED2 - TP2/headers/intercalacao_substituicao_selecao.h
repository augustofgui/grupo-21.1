#ifndef INTERCALACAO_SUBSTITUICAO_SELECAO_H
#define INTERCALACAO_SUBSTITUICAO_SELECAO_H

#include "geral.h"
#include "fita.h"
#include "intercalacao_ordenacao_interna.h"
#include <stdio.h>
#include <stdlib.h>

void intercalacao_substituicao_selecao(char argv[], int nro_quantidade, bool imprimir_dados);
void criar_blocos_ordenados_heap(FILE *arquivo_binario, int num_registros, Fitas *fitas, Estatistica *estatistica, bool imprimir_dados);

#endif // INTERCALACAO_SUBSTITUICAO_SELECAO_H
