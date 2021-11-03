#include "../headers/arvore_binaria.h"

int arvore_binaria_comparacoes = 0, arvore_binaria_transferencias = 0;

void TArvore_Inicia (TNo **pRaiz){
    *pRaiz = NULL ;
}

void TArvore_Insere_Raiz (TNo **pRaiz , int x){
    arvore_binaria_comparacoes++;
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
        arvore_binaria_comparacoes++;
        if (x<(*pAux)->item)
            pAux = &((*pAux)->pEsq);
        else {
            arvore_binaria_comparacoes++;
            if (x>(*pAux)->item)
                pAux = &((*pAux)->pDir);
            else return 0;
        }
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
    arvore_binaria_comparacoes++;
    if (p == NULL )
        return ;
    Infixa(p->pEsq);
    printf(" %d",p->item);
    Infixa(p->pDir);
}

int Buscar (TNo *pRaiz, Registro *x){
    arvore_binaria_comparacoes++;
	if (pRaiz == NULL)
		return 0;
    arvore_binaria_comparacoes++;
	if (x->chave == pRaiz->item){
        x->chave=pRaiz->item;
		return 1;
    }
    arvore_binaria_comparacoes++;
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
        arvore_binaria_transferencias++;
        fread(reg, sizeof(Registro), 1, arquivo_binario);
        TArvore_Insere_Raiz(&arvore, reg->chave);
    }

    Registro *pesquisa = (Registro*) malloc (sizeof(Registro));
    pesquisa->chave = nro_chave;

    int i = 0;
    arvore_binaria_comparacoes++;
    if (Buscar(arvore, pesquisa)) { 
        i++;
        pesquisa[i].chave=nro_chave;
        printf("Registro encontrado!\n");
        printf("Nº de transferências: %d\n", arvore_binaria_transferencias);
        printf("Nº de comparações: %d\n", arvore_binaria_comparacoes);
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
gcc arvore_b.c -c
gcc main.c -c
gcc geral.o sequencial_indexado.o arvore_binaria.o arvore_b.o main.o -o pesquisa
.\pesquisa.exe 2 100 1 10 -P
.\pesquisa.exe 2 100 2 10 -P
.\pesquisa.exe 2 100 3 10 -P
cd ..
.\pesquisa.exe 2 100 1 10 -P
*/
