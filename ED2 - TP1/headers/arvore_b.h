#include "geral.h"

#define MM 4
#define M 2

typedef struct Pagina *Apontador;

typedef struct Pagina {
    short n;
    Registro r[MM];
    Apontador p[MM + 1];
} Pagina;

int Pesquisa (Registro *x, Apontador Ap);
void Imprime(Apontador arvore);
void InsereNaPagina(Apontador Ap, Registro Reg, Apontador ApDir);
void Ins(Registro Reg, Apontador Ap, short *Cresceu, Registro *RegRetorno, Apontador *ApRetorno);
void Insere (Registro Reg, Apontador *Ap);
int arvore_b(FILE *arquivo_binario, int nro_chave, bool print_registro);