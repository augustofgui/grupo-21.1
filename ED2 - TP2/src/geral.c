#include "../headers/geral.h"

void merge_sort(Registro *vetor, int margem_esquerda, int n, int nro_situacao)
{
    if (margem_esquerda < n)
    {
        int nova_margem = (margem_esquerda + n) / 2;
        merge_sort(vetor, margem_esquerda, nova_margem);
        merge_sort(vetor, nova_margem + 1, n);
        (nro_situacao == 1) ? merge_sort_crescente(vetor, margem_esquerda, nova_margem, n) : merge_sort_decrescente(vetor, margem_esquerda, nova_margem, n);
    }
}

void merge_sort_crescente(int *vetor, int margem_esquerda, int nova_margem, int n)
{
    int tamanho_esquerda = (nova_margem - margem_esquerda + 1), tamanho_direita = (n - nova_margem);
    Registro *vetor_esquerda = (Registro *)malloc(tamanho_esquerda * sizeof(Registro)));
    Registro *vetor_direita = (Registro *)malloc(tamanho_direita * sizeof(Registro));
    int i, j;

    for (i = 0; i < tamanho_esquerda; i++)
        vetor_esquerda[i] = vetor[i + margem_esquerda];

    for (j = 0; j < tamanho_direita; j++)
        vetor_direita[j] = vetor[nova_margem + j + 1];

    i = 0, j = 0;

    for (int k = margem_esquerda; k <= n; k++)
    {
        if (i == tamanho_esquerda)
            vetor[k] = vetor_direita[j++];
        else if (j == tamanho_direita)
            vetor[k] = vetor_esquerda[i++];
        else if (vetor_esquerda[i].nota < vetor_direita[j].nota)
            vetor[k] = vetor_esquerda[i++];
        else
            vetor[k] = vetor_direita[j++];
    }

    free(vetor_direita);
    free(vetor_esquerda);
}

void merge_sort_decrescente(int *vetor, int margem_esquerda, int nova_margem, int n)
{
    int tamanho_esquerda = (nova_margem - margem_esquerda + 1), tamanho_direita = (n - nova_margem);
    Registro *vetor_esquerda = (Registro *)malloc(tamanho_esquerda * sizeof(Registro)));
    Registro *vetor_direita = (Registro *)malloc(tamanho_direita * sizeof(Registro));
    int i, j;

    for (i = 0; i < tamanho_esquerda; i++)
        vetor_esquerda[i] = vetor[i + margem_esquerda];

    for (j = 0; j < tamanho_direita; j++)
        vetor_direita[j] = vetor[nova_margem + j + 1];

    i = 0, j = 0;

    for (int k = margem_esquerda; k <= n; k++)
    {
        if (i == tamanho_esquerda)
            vetor[k] = vetor_direita[j++];
        else if (j == tamanho_direita)
            vetor[k] = vetor_esquerda[i++];
        else if (vetor_esquerda[i].nota > vetor_direita[j].nota)
            vetor[k] = vetor_esquerda[i++];
        else
            vetor[k] = vetor_direita[j++];
    }

    free(vetor_direita);
    free(vetor_esquerda);
}

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
    printf("%08ld %05.1f%s\n", x.inscricao, x.nota, x.estado_cidade_curso);
}

FILE *converter_para_binario(FILE *arquivo_texto)
{
    Registro aux;

    FILE *arquivo_binario = abrir_arquivo("arquivo_binario.bin", "w+b");

    while (fscanf(arquivo_texto, "%ld %f", &aux.inscricao, &aux.nota) != EOF)
    {
        fgets(aux.estado_cidade_curso, 82, arquivo_texto);
        fwrite(&aux, sizeof(Registro), 1, arquivo_binario);
    }

    rewind(arquivo_binario);

    return arquivo_binario;
}

void converter_para_txt(FILE *arquivo_binario)
{
    Registro aux;

    FILE *arquivo_txt = abrir_arquivo("arquivo_texto.txt", "w+");

    while (fread(&aux, sizeof(Registro), 1, arquivo_binario))
        fprintf(arquivo_txt, "%08ld %05.1f%s\n", aux.inscricao, aux.nota, aux.estado_cidade_curso);

    fclose(arquivo_txt);
}
