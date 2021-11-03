#ifndef arvore_bx_h
#define arvore_bx_h

#include "geral.h"

#define M 4

typedef enum {Interna, Externa} TipoPaginaBX;

typedef struct PaginaBX * ApontadorBX;
typedef struct PaginaBX{
    TipoPaginaBX tipo;

    union {
        struct {
            // pagina index
            int ni;
            int ri[M * 2];
            ApontadorBX pi[(M * 2) + 1];
        } U0;
        struct {
            // folha
            int ne;
            Registro re[(M * 2) * 2];
        } U1;
    } UU;
}PaginaBX;

void insere_bx( Registro registro, ApontadorBX * raiz, int * bx_comparacoes ){


    if((*raiz) == NULL ){
        (*raiz) = (PaginaBX *) malloc(sizeof(PaginaBX));
        (*raiz)->tipo = Externa;
        (*raiz)->UU.U1.ne = 1;
        (*raiz)->UU.U1.re[0] = registro;
        return;
    }

    Registro reg_out;
    PaginaBX * pag_out;

    if(ins_bx(registro, raiz, bx_comparacoes, &reg_out, &pag_out)){
        PaginaBX * pag_temp = (PaginaBX*) malloc(sizeof(PaginaBX));
        pag_temp->tipo = Interna;
        pag_temp->UU.U0.ni = 1;
        pag_temp->UU.U0.ri[0] = reg_out.chave;
        pag_temp->UU.U0.pi[0] = (*raiz);
        pag_temp->UU.U0.pi[1] = pag_out;
        (*raiz) = pag_temp;
    }

}

int ins_bx( Registro registro, ApontadorBX * raiz, int * bx_comparacoes, Registro * reg_out, ApontadorBX * pag_out){

}


int arvore_bx(FILE * arquivo_binario, int nro_metodo, int nro_registros, int nro_situacao, int nro_chave, bool print_registro){
    rewind(arquivo_binario);

    int bx_transferencias = 0;
    int bx_comparacoes = 0;
    
    ApontadorBX arvore_bx;
    arvore_bx = NULL;

    Registro aux;
    
    while (!feof(arquivo_binario)) {
        bx_transferencias++;
        fread(&aux, sizeof(Registro), 1, arquivo_binario);
        insere_bx(aux, &arvore_bx, &bx_comparacoes);
    }
    
    Registro pesquisa;
    pesquisa.chave = nro_chave;

    int i = 0;
    bx_comparacoes++;
    if (pesquisa_bx(pesquisa, arvore_bx)) { 
        printf("Registro encontrado!\n");
        printf("Nº de transferências: %d\n", bx_transferencias);
        printf("Nº de comparações: %d\n", bx_comparacoes);

        if (print_registro)
            imprimir_registro(pesquisa);

        return 1; 
    }
   
    return 0; 
}

#endif