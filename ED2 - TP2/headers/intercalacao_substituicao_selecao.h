#ifndef INTERCALACAO_SUBSTITUICAO_SELECAO_H
#define INTERCALACAO_SUBSTITUICAO_SELECAO_H

#include "geral.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h> 

void preencheVetor (Registro* vetor,FILE* fileEntrada);
void converter_para_char (int num,char* c);
void esvaziarVetor (Registro* vetor,int* n);
void sub (FILE* nome_arquivo, Registro* vetor, int numeroArq,int* n);
void intercalacao_substituicao_selecao(FILE* nome_arquivo);

#endif