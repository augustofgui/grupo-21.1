#include "../headers/geral.h"
//#include "../headers/intercalacao_ordenacao_interna.h"
#include "../headers/intercalacao_substituicao_selecao.h"
#include "../headers/quicksort_externo.h"

int main(int argc, char *argv[])
{
    int nro_metodo = atoi(argv[1]);
    int nro_quantidade = atoi(argv[2]);
    int nro_situacao = atoi(argv[3]);
    bool imprimir_dados = false;
    char nome_arquivo[50];
    
    verificar_parametros(argc, nro_metodo, nro_quantidade, nro_situacao);

    if (argc > 4)
        imprimir_dados = (!strcmp(argv[4], "-P"));

    switch(nro_situacao){
        case 1 : 
            strcpy(nome_arquivo, "txt/PROVAO_DESORDENADO.TXT");
            break;
        case 2 : 
            strcpy(nome_arquivo, "txt/PROVAO_ORDENADO_ASC.TXT");
            break;
        case 3 : 
            strcpy(nome_arquivo, "txt/PROVAO_ORDENADO_DESC.TXT");
            break;
        case 4 : 
            strcpy(nome_arquivo, "txt/DEBUG.TXT");
            break;
        default : {
            printf("ERRO : Situação fornecida não corresponde ao enunciado do trabalho. Por favor, corrija os parãmetros de execução.\n");
            exit(1);
        }
    }

    switch (nro_metodo)
    {
    case 1:
        //intercalacao_ordenacao_interna(nome_arquivo, nro_quantidade, imprimir_dados);
        break;
    case 2:
        intercalacao_substituicao_selecao(nome_arquivo, imprimir_dados);
        break;
    case 3:
        quicksort_externo_main(nome_arquivo, nro_quantidade, imprimir_dados);
        break;
    }

    return 0;
}