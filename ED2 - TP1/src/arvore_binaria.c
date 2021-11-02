#include "../headers/arvore_binaria.h"

int ab_comparacoes = 0, ab_transferencias = 0;

void TArvore_Inicia (TNo **pRaiz){
    *pRaiz = NULL ;
}

void TArvore_Insere_Raiz (TNo **pRaiz , int x){
    if (*pRaiz==NULL) {
        *pRaiz = TNo_Cria(x);
        return;
    }
    TArvore_Insere(pRaiz,x);
}

int TArvore_Insere (TNo **pRaiz , int x){
    TNo **pAux;
    pAux = pRaiz;

    while (*pAux!=NULL) {
        if (x<(*pAux)->item)
            pAux = &((*pAux)->pEsq);
        else if (x>(*pAux)->item)
            pAux = &((*pAux)->pDir);
        else
            return 0;
    }
    *pAux = TNo_Cria(x);
    return 1;
}

TNo *TNo_Cria (int x){
    TNo *pAux = (TNo*)malloc(sizeof(TNo));
    pAux->item = x;
    pAux->pEsq = NULL;
    pAux->pDir = NULL;
    return pAux;
}

void Infixa(TNo *p){
    if (p == NULL )
        return ;
    Infixa(p->pEsq);
    printf(" %d",p->item);
    Infixa(p->pDir);
}

int Buscar (TNo *pRaiz, Registro *x){
    ab_comparacoes++;
	if (pRaiz == NULL)
		return 0;
    ab_comparacoes++;
	if (x->chave == pRaiz->item)
		return 1;
    ab_comparacoes++;
	if (x->chave < pRaiz->item)
		return Buscar(pRaiz->pEsq, x);
	else
		return Buscar(pRaiz->pDir, x);
}

int arvore_binaria(FILE *arquivo_binario, int nro_metodo, int nro_registros, int nro_situacao, int nro_chave,bool print_registro) {
    rewind(arquivo_binario);

    nro_metodo=nro_registros=nro_situacao=0;
    nro_registros=nro_metodo=0;

    TNo* arvore;
    TArvore_Inicia(&arvore);

    Registro *reg = (Registro*) malloc (sizeof(Registro));
    
    while (!feof(arquivo_binario)) {
        ab_transferencias++;
        fread(reg, sizeof(Registro), 1, arquivo_binario);
        TArvore_Insere_Raiz(&arvore, reg->chave);
    }

    Registro *pesquisa = (Registro*) malloc (sizeof(Registro));
    pesquisa->chave = nro_chave;

    int i = 0;
    ab_comparacoes++;
    if (Buscar(arvore, pesquisa)) { 
        i++;
        pesquisa[i].chave=nro_chave;
        printf("Registro encontrado!\n");
        printf("Nº de transferências: %d\n", ab_transferencias);
        printf("Nº de comparações: %d\n", ab_comparacoes);
        if (print_registro)
            imprimir_registro(pesquisa[i]);
        return 1; 
    }
   
    return 0; 
}

/*
cd .\src\
gcc geral.c -c
gcc sequencial_indexado.c -c
gcc arvore_binaria.c -c
gcc main.c -c
gcc geral.o sequencial_indexado.o arvore_binaria.o main.o -o pesquisa
cd ..
.\pesquisa.exe 2 100 1 10 -P
*/