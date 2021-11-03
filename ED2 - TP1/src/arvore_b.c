#include "../headers/arvore_b.h"

int ab_comparacoes = 0, ab_transferencias = 0;

int Pesquisa (Registro *x, Apontador Ap) {
    long i = 1;
    ab_comparacoes++;
    if (Ap == NULL){
        //printf ("Não existe\n");
        return 0;
    }
    while (i < Ap->n && x->chave > Ap->r[i-1].chave) i++;
    ab_comparacoes++;
    if (x->chave == Ap->r[i-1].chave){
        *x = Ap->r[i-1];
        return 1;
    }
    ab_comparacoes++;
    if (x->chave < Ap->r[i-1].chave) {
        return Pesquisa (x, Ap->p[i-1]);
    }    
    else {
        return Pesquisa (x, Ap->p[i]);
    }
    return 0;    
}

void Imprime(Apontador arvore) {
    int i = 0;
    ab_comparacoes++;
    if (arvore == NULL)
        return;
    while (i <= arvore->n) {
        Imprime(arvore->p[i]);
        ab_comparacoes++;
        if (i != arvore->n)
            printf("'%d' \n", arvore->r[i].chave);
        i++;
    }
    printf("\n");
}

void InsereNaPagina (Apontador Ap, Registro Reg, Apontador ApDir){
    short naoAchou;
    int k = Ap->n;
    ab_comparacoes++;
    if (k>0)
        naoAchou = 1;
    while (naoAchou){
        ab_comparacoes++;
        if (Reg.chave >= Ap->r[k-1].chave) {
            naoAchou = 0;
            break;
        }
        Ap->r[k] = Ap->r[k-1];
        Ap->p[k+1] = Ap->p[k];
        k--;
        ab_comparacoes++;
        if(k < 1) naoAchou = 0;
    }
    Ap->r[k] = Reg;
    Ap->p[k+1] = ApDir;
    Ap->n++;
}

void Ins (Registro Reg, Apontador Ap, short *Cresceu, Registro *RegRetorno, Apontador *ApRetorno){
    long i = 1; long j;
    Apontador ApTemp;
    ab_comparacoes++;
    if (Ap == NULL) {
        *Cresceu = 1;
        (*RegRetorno) = Reg;
        (*ApRetorno) = NULL;
        return;
    }

    while (i < Ap->n && Reg.chave > Ap->r[i-1].chave) i++;
    ab_comparacoes++;
    if (Reg.chave == Ap->r[i-1].chave) {
        //printf ("Já existe essa chave no local...\n");
        *Cresceu = 0;
        return;
    }
    ab_comparacoes++;
    if (Reg.chave < Ap->r[i-1].chave) i--;
    
    Ins(Reg, Ap->p[i], Cresceu, RegRetorno, ApRetorno);
    ab_comparacoes++;
    if(!*Cresceu) return;

    // A página tem espaço.
    ab_comparacoes++;
    if (Ap->n < MM){
        InsereNaPagina (Ap, *RegRetorno, *ApRetorno);
        *Cresceu = 0;
        return;
    }
    // A página tem que ser dividida (Overflow)
    ApTemp = (Apontador)malloc(sizeof(Pagina));
    ApTemp->n = 0;
    ApTemp->p[0] = NULL;
    ab_comparacoes++;
    if (i < M+1){
        InsereNaPagina(ApTemp, Ap->r[MM-1], Ap->p[MM]);
        Ap->n --;
        InsereNaPagina(Ap, *RegRetorno, *ApRetorno);
    } else
        InsereNaPagina(ApTemp, *RegRetorno, *ApRetorno);
    
    for (j = M + 2; j <= MM; j++) {
        InsereNaPagina(ApTemp, Ap->r[j-1], Ap->p[j]);
    }

    Ap->n = M;
    ApTemp->p[0] = Ap->p[M+1];
    *RegRetorno = Ap->r[M];
    *ApRetorno = ApTemp;

}

void Insere (Registro Reg, Apontador *Ap) {
    short Cresceu;
    Registro RegRetorno;
    Pagina *ApRetorno, *ApTemp;

    Ins (Reg, *Ap, &Cresceu, &RegRetorno, &ApRetorno);
    ab_comparacoes++;
    if (Cresceu){ // Verifica se ocorreu o crescimento da árvore
        ApTemp = (Pagina *) malloc (sizeof(Pagina));
        ApTemp->n = 1;
        ApTemp->r[0] = RegRetorno;
        ApTemp->p[1] = ApRetorno;
        ApTemp->p[0] = *Ap;
        *Ap = ApTemp;
    }
}

int arvore_b(FILE *arquivo_binario, int nro_chave,bool print_registro) {
    rewind(arquivo_binario);
    
    Apontador arv = NULL;

    Registro *reg = (Registro*) malloc (sizeof(Registro));
    
    while (!feof(arquivo_binario)) {
        ab_transferencias++;
        fread(reg, sizeof(Registro), 1, arquivo_binario);
        Insere(*reg, &arv);
    }
    
    Registro *pesquisa = (Registro*) malloc (sizeof(Registro));
    pesquisa->chave = nro_chave;

    ab_comparacoes++;
    if (Pesquisa(pesquisa, arv)) { 
        printf("Registro encontrado!\n");
        printf("Nº de transferências: %d\n", ab_transferencias);
        printf("Nº de comparações: %d\n", ab_comparacoes);
        if (print_registro)
            imprimir_registro(*pesquisa);
        return 1; 
    }
   
    return 0; 
}