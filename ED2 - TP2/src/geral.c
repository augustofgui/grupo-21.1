#include "../headers/geral.h"

void verificar_parametros(int argc, int nro_metodo, int nro_quantidade, int nro_situacao)
{
    if (argc < 4)
    {
        printf("ERRO : Parâmetros insuficientes para a execução\n.");
        exit(1);
    }
    if (nro_metodo != 1 && nro_metodo != 2 && nro_metodo != 3)
    {
        printf("ERRO : Método fornecido não corresponde ao enunciado do trabalho. Por favor, corrija os parâmetros de execução.\n");
        exit(1);
    }
    if (nro_quantidade < 100 || nro_quantidade > 471705)
    {
        printf("ERRO : Quantidade de registros fornecida não corresponde ao enunciado do trabalho. Por favor, corrija os parãmetros de execução.\n");
        exit(1);
    }
    if (nro_situacao != 1 && nro_situacao != 2 && nro_situacao != 30)
    {
        printf("ERRO : Situação fornecida não corresponde ao enunciado do trabalho. Por favor, corrija os parãmetros de execução.\n");
        exit(1);
    }
}

FILE *abrir_arquivo(char nome_arquivo[], char modo_abertura[])
{
    FILE *abrir_arquivo = fopen(nome_arquivo, modo_abertura);
    if (abrir_arquivo == NULL)
    {
        printf("ERRO : Impossível abrir arquivo '%s' informado na execução.\n", nome_arquivo);
        exit(1);
    }
    return abrir_arquivo;
}

void imprimir_registro(Registro x)
{
    printf("Inscrição: %ld\n", x.inscricao);
    printf("Nota: %f\n", x.nota);
    printf("Estado: %s\n", x.estado);
    printf("Cidade: %s\n", x.cidade);
    printf("Curso: %s\n", x.curso);
}

FILE *converter_para_binario(FILE *arquivo_texto)
{
    Registro aux;

    FILE *arquivo_binario = abrir_arquivo("provao_binario.bin", "w+b");

    while (fscanf(arquivo_texto, "%ld%f%s%s%s", &aux.inscricao, &aux.nota, aux.estado, aux.cidade, aux.curso))
        fwrite(&aux, sizeof(Registro), 1, arquivo_binario);

    rewind(arquivo_binario);

    return arquivo_binario;
}