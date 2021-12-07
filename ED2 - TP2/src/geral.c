#include "../headers/geral.h"
#include "../headers/quicksort_externo.h"

void merge_sort(Registro *vetor, int margem_esquerda, int n, Estatistica * estatistica)
{
    if (margem_esquerda < n)
    {
        int nova_margem = (margem_esquerda + n) / 2;
        merge_sort(vetor, margem_esquerda, nova_margem, estatistica);
        merge_sort(vetor, nova_margem + 1, n, estatistica);
        merge_sort_ascendente(vetor, margem_esquerda, nova_margem, n, estatistica);
    }
}

void merge_sort_ascendente(Registro *vetor, int margem_esquerda, int nova_margem, int n, Estatistica * estatistica)
{
    int tamanho_esquerda = (nova_margem - margem_esquerda + 1), tamanho_direita = (n - nova_margem);
    Registro *vetor_esquerda = (Registro *)malloc(tamanho_esquerda * sizeof(Registro));
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
        else if (vetor_esquerda[i].nota < vetor_direita[j].nota){
            vetor[k] = vetor_esquerda[i++];
            estatistica->nro_comparacoes++;
        }
        else{
            vetor[k] = vetor_direita[j++];
            estatistica->nro_comparacoes++;
        }
    }

    free(vetor_direita);
    free(vetor_esquerda);
}

void selection_sort_ascendente(Registro *array, int n)
{
    Registro aux;
    int min;

    for (int i = 0; i < n - 1; i++)
    {
        min = i;
        for (int j = i + 1; j < n; j++)
        {
            if (array[j].nota < array[min].nota)
                min = j;
        }
        if (i != min)
        {
            aux = array[i];
            array[i] = array[min];
            array[min] = aux;
        }
    }
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
    if (nro_situacao != 1 && nro_situacao != 2 && nro_situacao != 3 && nro_situacao != 4)
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

void converter_para_binario(FILE *arquivo_texto, char *nome_binario, char *nome_txt, int nro_quantidade)
{
    Registro aux;

    printf(ANSI_BOLD "\nArquivo: " ANSI_COLOR_YELLOW "%s\n" ANSI_RESET, nome_txt);
    printf(ANSI_BOLD ANSI_COLOR_YELLOW "Convertendo" ANSI_RESET " o arquivo .txt para binário. Aguarde...\n");

    FILE *arquivo_binario = abrir_arquivo(nome_binario, "w+b");

    while (nro_quantidade--)
    {
        fscanf(arquivo_texto, "%ld %f", &aux.inscricao, &aux.nota);
        fgets(aux.estado_cidade_curso, 87, arquivo_texto);
        aux.estado_cidade_curso[85] = '\0';
        fwrite(&aux, sizeof(Registro), 1, arquivo_binario);
    }

    fclose(arquivo_binario);
}

void converter_para_txt(FILE *arquivo_binario, char *argv, int nro_registros)
{
    Registro aux;
    rewind(arquivo_binario);
    printf(ANSI_BOLD ANSI_COLOR_YELLOW "Convertendo" ANSI_RESET " o arquivo binário para .txt. Aguarde...\n");

    FILE *arquivo_txt = abrir_arquivo(argv, "w+");

    while (nro_registros--)
    {
        fread(&aux, sizeof(Registro), 1, arquivo_binario);
        fprintf(arquivo_txt, "%08ld %05.1f%s\n", aux.inscricao, aux.nota, aux.estado_cidade_curso);
    }

    printf(ANSI_BOLD "Resultado da ordenação impresso em: " ANSI_RESET ANSI_COLOR_YELLOW "RESULTADO.TXT" ANSI_RESET "\n\n");

    fclose(arquivo_txt);
}

void print_estatisticas(int nro_comparacoes, int nro_leituras, int nro_escritas, double tempo_execucao)
{
    printf(ANSI_BOLD ANSI_COLOR_YELLOW "\n- ESTATÍSTICAS DA EXECUÇÃO -     \n" ANSI_RESET);
    printf(ANSI_BOLD "\nNº de comparações: %d" ANSI_RESET "\n", nro_comparacoes);
    printf(ANSI_BOLD "Nº de leituras(fread): %d" ANSI_RESET "\n", nro_leituras);
    printf(ANSI_BOLD "Nº de escritas(fwrite): %d" ANSI_RESET "\n", nro_escritas);
    printf(ANSI_BOLD "Tempo de execução: " ANSI_COLOR_YELLOW "%f" ANSI_RESET ANSI_BOLD " segundos" ANSI_RESET "\n\n", tempo_execucao);
}

void PrintFRead(Registro *R)
{
    printf(ANSI_BOLD ANSI_COLOR_BLUE "fread" ANSI_RESET "  : %08ld %05.1f%s\n", R->inscricao, R->nota, R->estado_cidade_curso);
}

void PrintFWrite(Registro *R)
{
    printf(ANSI_BOLD ANSI_COLOR_RED "fwrite" ANSI_RESET " : %08ld %05.1f%s\n", R->inscricao, R->nota, R->estado_cidade_curso);
}
