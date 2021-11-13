#include "../headers/geral.h"
//#include "../headers/intercalacao_ordenacao_interna.h"
//#include "../headers/intercalacao_substituicao_selecao.h"
#include "../headers/quicksort_externo.h"

int main (int argc, char *argv[]){
    int nro_metodo = atoi(argv[1]);
    int nro_quantidade = atoi(argv[2]);
    int nro_situacao = atoi(argv[3]);
    bool imprimir_dados = false;
    char nome_arquivo[100];

    verificar_parametros(argc, nro_metodo, nro_quantidade, nro_situacao);
    
    if (argc > 5)
        imprimir_dados = (!strcmp(argv[5], "-P"));

    argc > 6 ? strcpy(nome_arquivo, argv[6]) : strcpy(nome_arquivo, "PROVAO.TXT");

    switch (nro_metodo){
        case 1 : 
            //intercalacao_ordenacao_interna(nro_metodo, nro_quantidade, nro_situacao, imprimir_dados);
            break;
        case 2 : 
            //intercalacao_substituicao_selecao(nro_metodo, nro_quantidade, nro_situacao, imprimir_dados);
            break;
        case 3 : 
            quicksort_externo_main(nome_arquivo, nro_quantidade);
            break;
    }

    return 0;
}