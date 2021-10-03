#include "../headers/geral.h"

int sequencial_Indexado(int argc, char argv[])
{
    FILE *arquivo_Binario = criarArquivo(argv[1], argv[2], argv[3]);
    int itens_Pagina = defineItensPagina(argv[2]);
    int tam_Tabela = itens_Pagina / argv[2] + 1;
    int tabela_Indice[tam_Tabela];
    int indice_Pagina = buscarPagina(tabela_Indice, tam_Tabela, argv[3], argv[4]);
    //Buscar página no arquivo de acordo com o índice encontrado.
    fclose(arquivo_Binario);
    //Buscar o registro na página em memória principal.
    //Caso encontrado, imprimir e retornar 1. Se não, retornar 0.
}

int buscar_Pagina(int *tabela_Indice, int tam_Tabela, int tipo_Ordenacao, int chave_Buscada)
{
    int aux;

    switch (tipo_Ordenacao)
    {
    case 1:
        for (aux = 0; aux < tam_Tabela; aux++)
            if (tabela_Indice[aux] > chave_Buscada)
                return (aux - 1);
        return (aux - 1);
    case 2:
        for (aux = tam_Tabela - 1; aux > -1; aux--)
            if (tabela_Indice[aux] < chave_Buscada)
                return (aux + 1);
        return (aux + 1);
    }

    return -1;
}

void montar_Tabela(FILE *arquivo, int *tabela_Indice, int itens_Pagina)
{
    Registro aux[itens_Pagina];

    for (int i = 0; fread(&aux, sizeof(Registro), itens_Pagina, arquivo); i++)
        tabela_Indice[i] = aux[0].chave;
}

int define_ItensPagina(int nro_Registros)
{
    switch (nro_Registros)
    {
    case 100:
        return 5;
    case 1000:
        return 50;
    case 10000:
        return 100;
    case 100000:
        return 200;
    case 1000000:
        return 1000;
    default:
        printf("Número de registros não condiz com as instruções.\n");
        exit(1);
    }
}