#include "../headers/arvore_b.h"

void Inicializa(TipoApontador Arvore)
{
    Arvore = NULL;
}

int Pesquisa(Registro *x, TipoApontador Ap)
{
    long i = 1;
    if (Ap == NULL)
        return 0;

    while (i < Ap->n && x->chave > Ap->r[i - 1].chave)
        i++;
    if (x->chave == Ap->r[i - 1].chave)
    {
        *x = Ap->r[i - 1];
        return 1;
    }
    if (x->chave < Ap->r[i - 1].chave)
        Pesquisa(x, Ap->p[i - 1]);
    else
        Pesquisa(x, Ap->p[i]);
}

void Imprime(TipoApontador arvore)
{
    int i = 0;
    if (arvore == NULL)
        return;
    while (i <= arvore->n)
    {
        Imprime(arvore->p[i]);
        if (i != arvore->n)
            printf("%d ", arvore->r[i].chave);
        i++;
    }
}

void InsereNaPagina(TipoApontador Ap, Registro Reg, TipoApontador ApDir)
{
    short NaoAchouPosicao;
    int k;
    k = Ap->n;
    NaoAchouPosicao = (k > 0);
    while (NaoAchouPosicao)
    {
        if (Reg.chave >= Ap->r[k - 1].chave)
        {
            NaoAchouPosicao = 0;
            break;
        }
        Ap->r[k] = Ap->r[k - 1];
        Ap->p[k + 1] = Ap->p[k];
        k--;
        if (k < 1)
            NaoAchouPosicao = 0;
    }
    Ap->r[k] = Reg;
    Ap->p[k + 1] = ApDir;
    Ap->n++;
}

void Ins(Registro Reg, TipoApontador Ap, short *Cresceu, Registro *RegRetorno, TipoApontador *ApRetorno)
{
    long i = 1;
    long j;
    TipoApontador ApTemp;
    if (Ap == NULL)
    {
        *Cresceu = 1;
        (*RegRetorno) = Reg;
        (*ApRetorno) = NULL;
        return;
    }
    while (i < Ap->n && Reg.chave > Ap->r[i - 1].chave)
        i++;
    if (Reg.chave == Ap->r[i - 1].chave)
    {
        printf(" Erro: Registro ja esta presente\n");
        *Cresceu = 0;
        return;
    }
    if (Reg.chave < Ap->r[i - 1].chave)
        i--;
    Ins(Reg, Ap->p[i], Cresceu, RegRetorno, ApRetorno);
    if (Cresceu == 0)
        return;
    if (Ap->n < MM)
    { // Página tem espaço
        InsereNaPagina(Ap, *RegRetorno, *ApRetorno);
        *Cresceu = 0;
        return;
    }
    // Página tem que ser dividida: Overflow
    ApTemp = (TipoApontador)malloc(sizeof(TipoPagina));
    ApTemp->n = 0;
    ApTemp->p[0] = NULL;
    if (i < M + 1)
    {
        InsereNaPagina(ApTemp, Ap->r[MM - 1], Ap->p[MM]);
        Ap->n--;
        InsereNaPagina(Ap, *RegRetorno, *ApRetorno);
    }
    else
        InsereNaPagina(ApTemp, *RegRetorno, *ApRetorno);
    for (j = M + 2; j <= MM; j++)
        InsereNaPagina(ApTemp, Ap->r[j - 1], Ap->p[j]);
    Ap->n = M;
    ApTemp->p[0] = Ap->p[M + 1];
    *RegRetorno = ApTemp->r[M];
    *ApRetorno = ApTemp;
}

void Insere(Registro Reg, TipoApontador *Ap)
{
    short Cresceu;
    Registro RegRetorno;
    TipoPagina *ApRetorno, *ApTemp;
    Ins(Reg, *Ap, &Cresceu, &RegRetorno, &ApRetorno);
    if (Cresceu == 1)
    { // Caso a árvore tenha crescido
        ApTemp = (TipoPagina *)malloc(sizeof(TipoPagina));
        ApTemp->n = 1;
        ApTemp->r[0] = RegRetorno;
        ApTemp->p[1] = ApRetorno;
        ApTemp->p[0] = *Ap;
        *Ap = ApTemp;
    }
}