#include "geral.h"

int sequencial_Indexado(FILE *arquivo_Binario, int n_Metodo, int n_Registros, int n_Situacao, int n_Chave, char argv[5])
{
    int itens_Pagina = define_itensPagina(n_Registros);
    int tam_Tabela = (n_Registros / itens_Pagina) + 1;
    int tabela_Indice[tam_Tabela];
    int indice_Pagina = buscarIndice(tabela_Indice, tam_Tabela, n_Situacao, n_Chave);

    if (indice_Pagina == -1) //Caso toda a tabela de índice tenha sido percorrida e a chave seja maior que o último item.
        return 0;

    //Leitura da página referente ao indice encontrado na tabela.
    Registro aux[itens_Pagina];
    long int desloc_Ponteiro = indice_Pagina * sizeof(Registro);
    fseek(arquivo_Binario, desloc_Ponteiro, SEEK_SET);
    fread(&aux, sizeof(Registro), itens_Pagina, arquivo_Binario);

    //Pesquisa sequencial na página lida.
    for (int i = 0; i < itens_Pagina; i++)
    {
        if (aux[i].chave == n_Chave)
        {
            print_f("Registro encontrado!\n");
            imprimir_Registro(aux[i]);
            return 1;
        }
    }

    return 0;
}

int buscar_Indice(int *tabela_Indice, int tam_Tabela, int n_Situacao, int n_Chave)
{
    int aux;

    switch (n_Situacao)
    {
    case 1:
        for (aux = 0; aux < tam_Tabela; aux++)
        {
            if (tabela_Indice[aux] == n_Chave)
                return tabela_Indice[aux];
            if (tabela_Indice[aux] > n_Chave)
                return tabela_Indice[aux - 1];
        }
    case 2:
        for (aux = 0; aux < tam_Tabela; aux++)
        {
            if (tabela_Indice[aux] == n_Chave)
                return tabela_Indice[aux];
            if (tabela_Indice[aux] < n_Chave)
                return tabela_Indice[aux - 1];
        }
    }

    return -1;
}

void montar_Tabela(FILE *arquivo_Binario, int *tabela_Indice, int itens_Pagina)
{
    Registro aux[itens_Pagina];

    for (int i = 0; fread(&aux, sizeof(Registro), itens_Pagina, arquivo_Binario); i++)
        tabela_Indice[i] = aux[0].chave;
}

int define_itensPagina(int n_Registros)
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