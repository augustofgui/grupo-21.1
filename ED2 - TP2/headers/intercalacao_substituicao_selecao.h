#ifndef INTERCALACAO_SUBSTITUICAO_SELECAO_H
#define INTERCALACAO_SUBSTITUICAO_SELECAO_H

#include "geral.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h> 

#define MAXTAM 20

void preencheVetor (Registro* vetor,FILE* fileEntrada);
void converter_para_char (int num,char* c);
void esvaziarVetor (Registro* vetor,int* n);
void sub (FILE* nome_arquivo, Registro* vetor,int* n);
void intercalacao_substituicao_selecao(char* nome_arquivo, bool imprimir_dados);

////////////////////HEAP

void Refaz (int Esq, int Dir, Registro *A);
void RefazPeloIndice (int Esq, int Dir, Registro *A);
void Constroi (Registro *A, int  *n);
void ConstroiPeloIndice (Registro *A, int *n);
Registro Min (Registro *A);
Registro RetiraMin (Registro *A, int *n);
void Aumenta (int i, double new, Registro *A);
void Insere (Registro *x, Registro *A, int *n);
void Imprime (Registro *A, int *n);

#endif