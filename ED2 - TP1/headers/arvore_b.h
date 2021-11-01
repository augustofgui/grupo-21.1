#include "geral.h"

#define MM 4
#define M 2

typedef struct TipoPagina *TipoApontador;
typedef struct TipoPagina
{
    short n;
    Registro r[MM];
    TipoApontador p[MM + 1];
} TipoPagina;

void Inicializa(TipoApontador Arvore);
void Imprime(TipoApontador arvore);
void InsereNaPagina(TipoApontador Ap, Registro Reg, TipoApontador ApDir);
void Ins(Registro Reg, TipoApontador Ap, short *Cresceu, Registro *RegRetorno, TipoApontador *ApRetorno);
void Insere(Registro Reg, TipoApontador *Ap);