#ifndef QUICKSORT_EXTERNO_H
#define QUICKSORT_EXTERNO_H

#include <limits.h>

#define TAM_AREA 20

typedef struct {
    Registro array[TAM_AREA];
    int nro_cels_ocupadas;
} TipoArea;

void quicksort_externo_main(char argv[], int nro_quantidade, bool imprimir_dados);
void quicksort_externo(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, int Esq, int Dir, bool imprimir_dados);
void Particao(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, TipoArea Area, int Esq, int Dir, int *i, int *j, bool imprimir_dados);
void LeSup(FILE **ArqLEs, Registro *UltLido, int *Ls, bool *OndeLer, bool imprimir_dados);
void LeInf(FILE **ArqLi, Registro *UltLido, int *Li, bool *OndeLer, bool imprimir_dados);
void EscreveMax(FILE **ArqLEs, Registro R, int *Es, bool imprimir_dados);
void EscreveMin(FILE **ArqEi, Registro R, int *Ei, bool imprimir_dados);
void FAVazia(TipoArea* Area);
void RetiraUltimo(TipoArea *Area, Registro *R);
void RetiraPrimeiro(TipoArea *Area, Registro *R);
void InsereItem(Registro *UltLido, TipoArea *Area);
void PrintArea(TipoArea Area);
void print_ordenacao(bool imprimir_dados);

#endif // QUICKSORT_EXTERNO_H