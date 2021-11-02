#ifndef arvore_binaria_h
#define arvore_binaria_h

#include "geral.h"

typedef struct No {
    int item;
    Registro r;
    struct No *pEsq;
    struct No *pDir;
} TNo ;

void TArvore_Inicia (TNo **pRaiz);
void TArvore_Insere_Raiz (TNo **pRaiz , int x);
int TArvore_Insere (TNo **pRaiz , int x);
TNo *TNo_Cria (int x);
void Infixa(TNo *p);
int Buscar (TNo *pRaiz, Registro *x);
int arvore_binaria(FILE *arquivo_binario, int nro_metodo, int nro_registros, int nro_situacao, int nro_chave,bool print_registro);

#endif