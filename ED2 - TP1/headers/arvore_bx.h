#ifndef arvore_bx_h
#define arvore_bx_h

#include "geral.h"

#define N 4
#define NN N*2

typedef enum {Interna, Externa} TipoPaginaBX;

typedef struct PaginaBX * ApontadorBX;
typedef struct PaginaBX{
    TipoPaginaBX tipo;

    union {
        struct { // pagina index
            int ni;
            int ri[NN];
            ApontadorBX pi[NN + 1];
        } U0;

        struct { // folha
            int ne;
            Registro re[NN];
        } U1;
    } UU;
} PaginaBX;

int pesquisa_bx(Registro* registro, ApontadorBX pagina, int * bx_comparacoes);
void insere_bx( Registro registro, ApontadorBX * raiz, int * bx_comparacoes );
int ins_interna_bx( Registro registro, ApontadorBX raiz, int * bx_comparacoes, Registro * reg_out, ApontadorBX * pag_out);
int ins_externa_bx( Registro registro, ApontadorBX raiz, int * bx_comparacoes, Registro * reg_out, ApontadorBX * pag_out);
void insere_pagina_bx(Registro registro, ApontadorBX pagina, ApontadorBX aux, int * bx_comparacoes);
int ins_bx( Registro registro, ApontadorBX raiz, int * bx_comparacoes, Registro * reg_out, ApontadorBX * pag_out);
int arvore_bx(FILE * arquivo_binario, int nro_metodo, int nro_registros, int nro_situacao, int nro_chave, bool print_registro);

#endif