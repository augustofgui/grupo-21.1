#include "../headers/arvore_bx.h"
#include <stdio.h>

int pesquisa_bx(Registro* registro, ApontadorBX pagina, int * bx_comparacoes){
    long long i = 1;
    if(pagina == NULL) return 0;

    if(pagina->tipo == Interna){
        while(i < pagina->UU.U0.ni && registro->chave > pagina->UU.U0.ri[i - 1]) i++;
        (*bx_comparacoes)+= i + 2;

        if(registro->chave < pagina->UU.U0.ri[i - 1])
            return pesquisa_bx(registro, pagina->UU.U0.pi[i - 1], bx_comparacoes);
        else
            return pesquisa_bx(registro, pagina->UU.U0.pi[i], bx_comparacoes);
    }

    while(i < pagina->UU.U1.ne && registro->chave > pagina->UU.U1.re[i - 1].chave) i++;

    (*bx_comparacoes)+= i + 2;
    if(registro->chave == pagina->UU.U1.re[i - 1].chave){
        *registro = pagina->UU.U1.re[i - 1];
        return 1;
    }
    
    return 0;
}

void insere_bx( Registro registro, ApontadorBX * raiz, int * bx_comparacoes ){
    if((*raiz) == NULL ){
        ApontadorBX pag_temp = (ApontadorBX) malloc(sizeof(PaginaBX));
        pag_temp->tipo = Externa;
        pag_temp->UU.U1.ne = 1;
        pag_temp->UU.U1.re[0] = registro;
        (*raiz) = pag_temp;
        return;
    }

    Registro reg_out;
    PaginaBX * pag_out;

    if(ins_bx(registro, *raiz, bx_comparacoes, &reg_out, &pag_out)){
        ApontadorBX pag_temp = (ApontadorBX) malloc(sizeof(PaginaBX));
        pag_temp->tipo = Interna;
        pag_temp->UU.U0.ni = 1;
        pag_temp->UU.U0.ri[0] = reg_out.chave;
        pag_temp->UU.U0.pi[1] = pag_out;
        pag_temp->UU.U0.pi[0] = (*raiz);
        (*raiz) = pag_temp;
    }

    return;
}

int ins_interna_bx( Registro registro, ApontadorBX raiz, int * bx_comparacoes, Registro * reg_out, ApontadorBX * pag_out){
    long long i = 1;
    
    while(i < raiz->UU.U0.ni && registro.chave > raiz->UU.U0.ri[i - 1]) i++;

    (*bx_comparacoes) += i + 1;
    if(registro.chave == raiz->UU.U0.ri[i - 1]) return 0;    

    (*bx_comparacoes)++;
    if(registro.chave < raiz->UU.U0.ri[i - 1]) i--;
    
    
    if(!ins_bx(registro, raiz->UU.U0.pi[i], bx_comparacoes, reg_out, pag_out)) return 0;
    
    if(raiz->UU.U0.ni < NN){
        insere_pagina_bx(*reg_out, raiz, *pag_out, bx_comparacoes);
        return 0;
    }
    Registro aux;

    ApontadorBX temp = (ApontadorBX) malloc(sizeof(PaginaBX));
    temp->tipo = Interna;
    temp->UU.U0.ni = 0;
    temp->UU.U0.pi[0] = NULL;

    if(i < (N + 1)){
        aux.chave = raiz->UU.U0.ri[NN - 1];
        insere_pagina_bx(aux, temp, raiz->UU.U0.pi[NN], bx_comparacoes);
        raiz->UU.U0.ni--;
        insere_pagina_bx(*reg_out, raiz, *pag_out, bx_comparacoes);
    } else insere_pagina_bx(*reg_out, temp, *pag_out, bx_comparacoes);
    
    long long j;
    for (j = (N + 2); j <= NN; j++){
        aux.chave = raiz->UU.U0.ri[j - 1];
        insere_pagina_bx(aux, temp, raiz->UU.U0.pi[j], bx_comparacoes);
    }

    raiz->UU.U0.ni = N;
    temp->UU.U0.pi[0] = raiz->UU.U0.pi[N + 1];
    reg_out->chave = raiz->UU.U0.ri[N];
    *pag_out = temp;

    return 1;
}

int ins_externa_bx( Registro registro, ApontadorBX raiz, int * bx_comparacoes, Registro * reg_out, ApontadorBX * pag_out){
    long long i = 1;

    while(i < raiz->UU.U1.ne && registro.chave > raiz->UU.U1.re[i - 1].chave) i++;

    (*bx_comparacoes) += i + 1;

    if(registro.chave == raiz->UU.U1.re[i - 1].chave) return 0;

    (*bx_comparacoes)++;
    if(registro.chave < raiz->UU.U1.re[i - 1].chave) i--;
    
    (*bx_comparacoes)++;
    if(raiz->UU.U1.ne < NN){
        *reg_out = registro;
        insere_pagina_bx(registro, raiz, *pag_out, bx_comparacoes);
        return 0;
    }
    *reg_out = registro;
    *pag_out = NULL;    

    ApontadorBX temp = (ApontadorBX) malloc(sizeof(PaginaBX));
    temp->tipo = Externa;
    temp->UU.U1.ne = 0;
    
    if(i < (N + 1)){
        insere_pagina_bx(raiz->UU.U1.re[NN - 1], temp, *pag_out, bx_comparacoes);
        raiz->UU.U1.ne--;
        insere_pagina_bx(*reg_out, raiz, *pag_out, bx_comparacoes);
    } else insere_pagina_bx(*reg_out, temp, *pag_out, bx_comparacoes);

    long long j;
    for (j = 1; j <= N; j++)
        insere_pagina_bx(raiz->UU.U1.re[NN - j], temp, *pag_out, bx_comparacoes);
    
    raiz->UU.U1.ne = N;
    *reg_out = raiz->UU.U1.re[N];
    *pag_out = temp;
    return 1;
}

void insere_pagina_bx(Registro registro, ApontadorBX pagina, ApontadorBX aux, int * bx_comparacoes){
    short nao_achou_posicao = 0;
    long long p;

    if(pagina->tipo == Externa){
        p = pagina->UU.U1.ne;
        nao_achou_posicao = (p > 0);

        while(nao_achou_posicao){
            (*bx_comparacoes)++;
            if (registro.chave >= pagina->UU.U1.re[p - 1].chave){
                nao_achou_posicao = 0;
                break;
            }

            pagina->UU.U1.re[p] = pagina->UU.U1.re[p - 1];
            p--;

            if(p < 1)
                nao_achou_posicao = 0;
        }

        pagina->UU.U1.re[p] = registro;
        pagina->UU.U1.ne++;

    } else {
        p = pagina->UU.U0.ni;
        nao_achou_posicao = (p > 0);

        while(nao_achou_posicao){
            (*bx_comparacoes)++;
            if (registro.chave >= pagina->UU.U0.ri[p - 1]){
                nao_achou_posicao = 0;
                break;
            }
            pagina->UU.U0.ri[p] = pagina->UU.U0.ri[p - 1];
            pagina->UU.U0.pi[p + 1] = pagina->UU.U0.pi[p];
            p--;

            if(p < 1)
                nao_achou_posicao = 0;
        }

        pagina->UU.U0.ri[p] = registro.chave;
        pagina->UU.U0.pi[p + 1] = aux;
        pagina->UU.U0.ni++;
    }

    return;
}

int ins_bx( Registro registro, ApontadorBX raiz, int * bx_comparacoes, Registro * reg_out, ApontadorBX * pag_out){
    if(raiz->tipo == Externa)
        return ins_externa_bx(registro, raiz, bx_comparacoes, reg_out, pag_out);
    else
        return ins_interna_bx(registro, raiz, bx_comparacoes, reg_out, pag_out);
}

int arvore_bx(FILE * arquivo_binario, int nro_metodo, int nro_registros, int nro_situacao, int nro_chave, bool print_registro){
    rewind(arquivo_binario);

    int bx_transferencias = 0;
    int bx_comparacoes = 0;
    
    ApontadorBX arvore_bx;
    arvore_bx = NULL;

    Registro aux;
    
    while (fread(&aux, sizeof(Registro), 1, arquivo_binario)){
        bx_transferencias++;
        insere_bx(aux, &arvore_bx, &bx_comparacoes);
    }
    
    Registro pesquisa;
    pesquisa.chave = nro_chave;

    bx_comparacoes++;
    if (pesquisa_bx(&pesquisa, arvore_bx, &bx_comparacoes)) { 
        printf("Registro encontrado!\n");
        printf("Nº de transferências: %d\n", bx_transferencias);
        printf("Nº de comparações: %d\n", bx_comparacoes);

        if (print_registro)
            imprimir_registro(pesquisa);

        return 1; 
    }
   
    return 0; 
}