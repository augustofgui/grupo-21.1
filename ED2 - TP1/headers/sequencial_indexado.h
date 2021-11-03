#ifndef sequencial_indexado_h
#define sequencial_indexado_h

#include "geral.h"

int sequencial_indexado(FILE *arquivo_binario, int nro_metodo, int nro_registros, int nro_situacao, int nro_chave, bool imprimir_registro);
int buscar_indice(int *tabela_indice, int tam_tabela, int nro_situacao, int nro_chave);
void montar_tabela(FILE *arquivo_binario, int *tabela_indice, int itens_pagina);
int definir_itens_por_pagina(int nro_registros);

#endif