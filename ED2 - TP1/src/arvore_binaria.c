#include "../headers/arvore_binaria.h"
#include "../headers/geral.h"

int nro_posicao = 0;

int arvore_binaria(FILE *arquivo_binario, int nro_registros, int nro_chave, bool print_registro){
    TArvore arvore;
    
    int aux;
    Registro encontrado;
    TArvore_Inicia(&arvore);
    fread(&aux, sizeof(int), 1, arquivo_binario);
    TArvore_Insere_Raiz(&arvore, aux);

    for (int i = 1; i < nro_registros; i++){
        fseek(arquivo_binario, sizeof(Registro) - sizeof(int), SEEK_CUR);
        fread(&aux, sizeof(int), 1, arquivo_binario);
        TArvore_Insere(arvore, aux);
    }

    long int deslocamento_ponteiro = buscar_na_arvore(arvore, nro_chave);
    if (deslocamento_ponteiro >= 0){
        if (print_registro){
            rewind(arquivo_binario);
            fseek(arquivo_binario, deslocamento_ponteiro, SEEK_SET);
            fread(&encontrado, sizeof(Registro), 1, arquivo_binario);
            imprimir_registro(encontrado);
        }
        return 1;
    }
    return 0;
}

int buscar_na_arvore(TNo * p, int x){
    if (p == NULL)
        return - 1;
    if (p->chave == x)
        return p->posicao;
    if (p->chave > x)
        return buscar_na_arvore(p->pEsquerda, x);
    else
        return buscar_na_arvore(p->pDireita, x);
}

//Manter como especificado
void TArvore_Inicia (TNo ** pRaiz){
    *pRaiz = NULL;
}

void TArvore_Insere_Raiz (TNo ** ppRaiz , int x){
    if (*ppRaiz == NULL){
        *ppRaiz = TNo_Cria(x);
        return;
    }

    TArvore_Insere(*ppRaiz, x);
}

int TArvore_Insere (TNo *pRaiz , int x){
    if (pRaiz == NULL)
        return -1;
    
    if (x < pRaiz->chave){
        if (pRaiz->pEsquerda == NULL){
            pRaiz->pEsquerda = TNo_Cria(x);
            return 1;
        }
        return TArvore_Insere(pRaiz->pEsquerda, x);
    }

    if (x > pRaiz->chave){
        if (pRaiz->pDireita == NULL){
            pRaiz->pDireita = TNo_Cria(x);
            return 1;
        }
        return TArvore_Insere(pRaiz->pDireita, x);
    }

    return 0;
}

TNo * TNo_Cria (int x){
    TNo *pAux = (TNo*)malloc(sizeof(TNo));
    pAux->chave = x;
    pAux->posicao = nro_posicao;
    nro_posicao++;
    pAux->pEsquerda = NULL;
    pAux->pDireita = NULL;
    return pAux;
}
