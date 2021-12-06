#ifndef HEAP_MIN_H
#define HEAP_MIN_H

#include "geral.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int nro_iss_comparacoes = 0;
int nro_iss_leituras = 0;
int nro_iss_escritas = 0;

#define MAXTAM 20

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