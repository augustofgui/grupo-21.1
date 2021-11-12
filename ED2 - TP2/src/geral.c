#include "../headers/geral.h"

void verificar_parametros(int argc, int nro_metodo, int nro_quantidade, int nro_situacao){  
    if (argc < 4)
        printf("ERRO : Parâmetros insuficientes para a execução\n.");
        exit(1);
    if (nro_metodo != 1 && nro_metodo != 2 && nro_metodo != 3)
        printf("ERRO : Método fornecido não corresponde ao enunciado do trabalho. Por favor, corrija os parâmetros de execução.\n");
        exit(1);
    if (nro_quantidade < 100 || nro_quantidade > 471705)
        printf("ERRO : Quantidade de registros fornecida não corresponde ao enunciado do trabalho. Por favor, corrija os parãmetros de execução.\n");
        exit(1);
}

FILE* abrir_arquivo(char argv[]){
    FILE *abrir_arquivo = fopen(argv, "r+");
    if (abrir_arquivo == NULL){
        printf("ERRO : Impossível abrir arquivo '%s' informado na execução.\n", argv);
        exit(1);
    }
    return abrir_arquivo;
}