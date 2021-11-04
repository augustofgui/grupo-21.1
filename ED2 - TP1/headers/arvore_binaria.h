#ifndef arvore_binaria_h
#define arvore_binaria_h

#include "../headers/geral.h"

typedef struct No {
    int chave;
    int posicao;
     struct No *pEsquerda, *pDireita;
} TNo ;

typedef TNo * TArvore;

int buscar_na_arvore(TNo * p, int x);
void TArvore_Inicia (TNo ** pRaiz);
void TArvore_Insere_Raiz (TNo ** ppRaiz , int x);
int TArvore_Insere (TNo *pRaiz , int x);
TNo * TNo_Cria (int x);
void Prefixa(TNo * p);
int Buscar (TNo *pRaiz, Registro *x);
int arvore_binaria(FILE *arquivo_binario, int nro_registros, int nro_chave,bool print_registro);

#endif