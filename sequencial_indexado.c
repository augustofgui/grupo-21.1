#include "geral.h"

int sequencial_Indexado(FILE *arquivo_Binario, int n_Metodo, int n_Registros, int n_Situacao, int n_Chave, char argv[5])
{
    int itens_Pagina = defineItensPagina(n_Registros);
    int tam_Tabela = (n_Registros / itens_Pagina) + 1;
    int tabela_Indice[tam_Tabela];
    int indice_Pagina = buscarPagina(tabela_Indice, tam_Tabela, n_Situacao, n_Chave);
}

int buscarPagina(int *tabela_Indice, int tam_Tabela, int n_Situacao, int n_Chave)
{
    int aux;

    switch (n_Situacao)
    {
    case 1:
        for (aux = 0; aux < tam_Tabela; aux++)
            if (tabela_Indice[aux] > n_Chave)
                return (aux - 1);
        return (aux - 1);
    case 2:
        for (aux = tam_Tabela - 1; aux > -1; aux--)
            if (tabela_Indice[aux] < n_Chave)
                return (aux + 1);
        return (aux + 1);
    }

    return -1;
}

void montarTabela(FILE *arquivo, int *tabela_Indice, int itens_Pagina)
{
    Registro aux[itens_Pagina];

    for (int i = 0; fread(&aux, sizeof(Registro), itens_Pagina, arquivo); i++)
        tabela_Indice[i] = aux[0].chave;
}

int defineItensPagina(int n_Registros)
{
    switch (n_Registros)
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
    }
}