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
    int tam_bloco;
} Fita;

typedef struct {
    Fita * entrada;
    Fita  * saida;
} Fitas;

void intercalacao_ordenacao_interna(char argv[], int nro_quantidade, bool imprimir_dados);
void criar_blocos_ordenados(FILE * arquivo_binario, int num_registros, Fitas fitas, bool imprimir_dados);
Fitas cria_fitas();
Fita * cria_fitas_entrada();
Fita * cria_fitas_saida();

#endif // INTERCALACAO_ORDENACAO_INTERNA_H