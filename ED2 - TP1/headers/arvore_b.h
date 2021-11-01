#include "geral.h"

#define MM 4
#define M 2

int cont = -1; int count = 0;

typedef struct TipoPagina *TipoApontador;
typedef struct TipoPagina {
    int pageNum;
    short n;
    Registro r[MM];
    TipoApontador p[MM + 1];
} TipoPagina;

void Inicializa(TipoApontador Arvore);
int Pesquisa(FILE *arquivo_binario, Registro *x, TipoApontador Ap);
int PesquisanoArquivo(FILE *arquivo_binario, Registro Reg, TipoApontador pagina);
void Imprime(TipoApontador arvore);
void InsereNaPagina(TipoApontador Ap, Registro Reg, TipoApontador ApDir);
void Ins(Registro Reg, TipoApontador Ap, short *Cresceu, Registro *RegRetorno, TipoApontador *ApRetorno);
void salvar(FILE *arquivo_binario, TipoApontador pagina, Registro Reg[]);
void saveAux(FILE *arquivo_binario, TipoApontador p, int Nivel);
void Insere(FILE *arquivo_binario, Registro Reg, TipoApontador *Ap);
int arvore_externa(FILE *arquivo_binario, int nro_metodo, int nro_registros, int nro_situacao, int nro_chave, char argv[5]);