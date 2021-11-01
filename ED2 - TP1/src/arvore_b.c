#include "../headers/arvore_b.h"

int ab_comparacoes = 0, ab_insercoes = 0;

void Inicializa(Apontador Arvore) {
    Arvore = NULL;
}

int Pesquisa (Registro *x, Apontador Ap){
    long i = 1;
    if (Ap == NULL){
        //printf ("Não existe\n");
        return 0;
    }
    while (i < Ap->n && x->chave > Ap->r[i-1].chave) i++;

    if (x->chave == Ap->r[i-1].chave){
        *x = Ap->r[i-1];
        return 1;
    }

    if (x->chave < Ap->r[i-1].chave)
        return Pesquisa (x, Ap->p[i-1]);
    else   
        return Pesquisa (x, Ap->p[i]);

    return 0;    
}

void Imprime(Apontador arvore) {
    int i = 0;
    if (arvore == NULL)
        return;
    while (i <= arvore->n) {
        Imprime(arvore->p[i]);
        if (i != arvore->n)
            printf("'%d' \n", arvore->r[i].chave);
        i++;
    }
    printf("\n");
}

void InsereNaPagina (Apontador Ap, Registro Reg, Apontador ApDir){
    short naoAchou;
    int k = Ap->n;
    if (k>0)
        naoAchou = 1;
    while (naoAchou){
        if (Reg.chave >= Ap->r[k-1].chave) {
            naoAchou = 0;
            break;
        }
        Ap->r[k] = Ap->r[k-1];
        Ap->p[k+1] = Ap->p[k];
        k--;
        if(k < 1) naoAchou = 0;
    }
    Ap->r[k] = Reg;
    Ap->p[k+1] = ApDir;
    Ap->n++;
}

void Ins (Registro Reg, Apontador Ap, short *Cresceu, Registro *RegRetorno, Apontador *ApRetorno){
    long i = 1; long j;
    Apontador ApTemp;

    if (Ap == NULL) {
        *Cresceu = 1;
        (*RegRetorno) = Reg;
        (*ApRetorno) = NULL;
        return;
    }

    while (i < Ap->n && Reg.chave > Ap->r[i-1].chave) i++;

    if (Reg.chave == Ap->r[i-1].chave) {
        //printf ("Já existe essa chave no local...\n");
        *Cresceu = 0;
        return;
    }

    if (Reg.chave < Ap->r[i-1].chave) i--;
    
    Ins(Reg, Ap->p[i], Cresceu, RegRetorno, ApRetorno);

    if(!*Cresceu) return;

    // A página tem espaço.
    if (Ap->n < MM){
        InsereNaPagina (Ap, *RegRetorno, *ApRetorno);
        *Cresceu = 0;
        return;
    }
    // A página tem que ser dividida (Overflow)
    ApTemp = (Apontador)malloc(sizeof(Pagina));
    ApTemp->n = 0;
    ApTemp->p[0] = NULL;

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

    if (Cresceu){ // Verifica se ocorreu o crescimento da árvore
        ApTemp = (Pagina *) malloc (sizeof(Pagina));
        ApTemp->n = 1;
        ApTemp->r[0] = RegRetorno;
        ApTemp->p[1] = ApRetorno;
        ApTemp->p[0] = *Ap;
        *Ap = ApTemp;
    }
}

int arvore_b(FILE *arquivo_binario, int nro_metodo, int nro_registros, int nro_situacao, int nro_chave,bool print_registro) {
    rewind(arquivo_binario);
    
    Apontador arv;
    Inicializa(arv);

    Registro *reg = (Registro*) malloc (sizeof(Registro));
    
    while (!feof(arquivo_binario)) {
        fread(reg, sizeof(Registro), 1, arquivo_binario);
        Insere(*reg, &arv);
        ab_insercoes++;
    }
    
    Registro *pesquisa = (Registro*) malloc (sizeof(Registro));
    pesquisa->chave = nro_chave;

    if (Pesquisa(pesquisa, arv)) {
        ab_comparacoes++;
        printf("Registro '%d' encontrado!\n", pesquisa->chave);
        printf("N° de inserções:'%d'.\n", ab_insercoes);
        printf("N° de comparações:'%d'.\n", ab_comparacoes);
        if (print_registro)
            imprimir_registro(pesquisa[ab_comparacoes]);
        return 1;
    }    
    else
        return 0;
}