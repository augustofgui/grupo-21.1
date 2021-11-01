#include "../headers/arvore_b.h"

void Inicializa(TipoApontador Arvore)
{
    Arvore = NULL;
}

int Pesquisa(FILE *arquivo_binario, Registro *x, TipoApontador Ap) {
    long i = 1;
    int pes;
    int achou;
    if (Ap == NULL)
        return 0;

    while (i < Ap->n && x->chave > Ap->r[i - 1].chave)
        i++;
    if (x->chave == Ap->r[i - 1].chave)
    {
        achou = PesquisanoArquivo(arquivo_binario,Ap->r[i-1],Ap);
        return achou;
    }
    if (x->chave < Ap->r[i - 1].chave)
        pes = Pesquisa(arquivo_binario, x, Ap->p[i - 1]);
    else
        pes = Pesquisa(arquivo_binario, x, Ap->p[i]);
    return 0;    
}

int PesquisanoArquivo(FILE *arquivo_binario, Registro Reg, TipoApontador pagina) {
    Registro reg[2*M];
    int i;
    FILE *arq = fopen(arquivo_binario,"rb");
    if (arq == NULL)
    exit(1);
    fseek(arq, pagina->pageNum*(2*M*sizeof(Registro)), SEEK_SET);
    fread(reg, (2*M*sizeof(Registro)),1,arq);
    fclose(arq);
    for(i = 0; i < 2*M; i++) {
        if (Reg.chave == reg[i].chave)
            return 1;
    }        
}    

void Imprime(TipoApontador arvore) {
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
        Ins(Reg, Ap->p[i-1], Cresceu, RegRetorno, ApRetorno);
    else
        Ins(Reg, Ap->p[i], Cresceu, RegRetorno, ApRetorno);    
    if (!*Cresceu)
        return;
    if (Ap->n < MM)
    { // Verificando se tem espaço na página
        InsereNaPagina(Ap, *RegRetorno, *ApRetorno);
        *Cresceu = 0;
        return;
    }
    // Página tem que ser dividida: Overflow
    ApTemp = (TipoApontador)malloc(sizeof(TipoPagina));
    ApTemp->n = 0;
    ApTemp->p[0] = NULL;
    cont++;
    ApTemp->pageNum = cont;
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

void salvar(FILE *arquivo_binario, TipoApontador pagina, Registro Reg[]) {

    FILE* arq;
    if (!file_exists(arquivo_binario)){
        arq = fopen(arquivo_binario,"wb");
        if (arq == NULL)
            exit(1);
        fseek(arq, pagina->pageNum*(MM*sizeof(Registro)), SEEK_SET);
        fwrite(Reg,(MM*sizeof(Registro)),1,arq);
        fclose(arq);
    }

    else{
        arq = fopen(arquivo_binario,"r+b");
        if (arq == NULL)
            exit(1);
        fseek(arq, pagina->pageNum*(MM*sizeof(Registro)), SEEK_SET);
        fwrite(Reg, (MM*sizeof(Registro)),1,arq);
        fclose(arq);
        }
    }

void saveAux(FILE *arquivo_binario, TipoApontador p, int Nivel) {
  int i,j;

  if (p == NULL)
    return;
  for (i = 0; i < p->n; i++)
    salvar(arquivo_binario, p, p->r);
  for (j = 0; j <= p->n; j++)
    saveAux(arquivo_binario, p->p[j], Nivel + 1);
}

void Insere(FILE *arquivo_binario, Registro Reg, TipoApontador *Ap) {
    short Cresceu;
    Registro RegRetorno;
    TipoPagina *ApRetorno, *ApTemp;
    Ins(Reg, *Ap, &Cresceu, &RegRetorno, &ApRetorno);
    if (Cresceu)
    { // Caso a árvore tenha crescido
        ApTemp = (TipoPagina *)malloc(sizeof(TipoPagina));
        ApTemp->n = 1;
        ApTemp->r[0] = RegRetorno;
        ApTemp->p[1] = ApRetorno;
        cont++;
        ApTemp->pageNum = cont;
        ApTemp->p[0] = *Ap;
        *Ap = ApTemp;
    }
    // Salvar no arquivo
    saveAux(arquivo_binario,*Ap, MM);
}

int arvore_externa(FILE *arquivo_binario, int nro_metodo, int nro_registros, int nro_situacao, int nro_chave, char argv[5]) {
    TipoApontador *arv;
    int pesquisa;
    Registro reg;
    arv=(TipoApontador*) malloc(sizeof(TipoApontador));
    Inicializa(arv);
    pesquisa = Pesquisa(arquivo_binario, nro_chave, arv);
    if (pesquisa == 1) {
        Insere(arquivo_binario, reg, arv);
        count++;
        if (nro_chave <= 0) {
            count--;
        }
        return 1;
    }
    else 
        return 0;
}