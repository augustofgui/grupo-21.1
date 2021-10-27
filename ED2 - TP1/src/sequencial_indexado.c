#include "geral.h"

int sequencial_Indexado(FILE *arquivo_Binario, int n_Metodo, int n_Registros, int n_Situacao, int n_Chave, char argv[5])
{
    //Definição do tamanho das páginas e da tabela.
    int itens_Pagina = SI_defineItensPagina(n_Registros);
    Registro aux[itens_Pagina];
    int tam_Tabela = n_Registros / itens_Pagina;
    int tabela_Indice[tam_Tabela];

    //Leitura dos índices da tabela.
    SI_montar_Tabela(arquivo_Binario, tabela_Indice, itens_Pagina);

    //Busca sequencial na tabela pela página que pode conter a chave buscada.
    int indice_Pagina = SI_buscar_Indice(tabela_Indice, tam_Tabela, n_Situacao, n_Chave);

    //Chave buscada menor ou maior (em caso de arquivo decrescente) do que o primeiro índice da tabela.
    if (indice_Pagina == -1)
        return 0;

    //Cálculo do deslocamento para leitura da página correspondente ao índice da tabela.
    long int desloc_Ponteiro = itens_Pagina * indice_Pagina * sizeof(Registro);
    fseek(arquivo_Binario, desloc_Ponteiro, SEEK_SET);
    fread(aux, sizeof(Registro), itens_Pagina, arquivo_Binario);

    //Pesquisa sequencial na página lida.
    for (int i = 0; i < itens_Pagina; i++)
    {
        if (aux[i].chave == n_Chave)
        {
            printf("Registro encontrado!\n");
            imprimir_Registro(aux[i]);
            return 1;
        }
    }

    return 0;
}

int SI_buscar_Indice(int *tabela_Indice, int tam_Tabela, int n_Situacao, int n_Chave)
{
    int aux;

    switch (n_Situacao)
    {
    case 1:
        if (tabela_Indice[0] > n_Chave)
            return -1;
        for (aux = 0; aux < tam_Tabela; aux++)
        {
            if (tabela_Indice[aux] == n_Chave)
                return aux;
            if (tabela_Indice[aux] > n_Chave)
                return aux - 1;
        }
        return aux - 1;
        break;
    case 2:
        if (tabela_Indice[0] < n_Chave)
            return -1;
        for (aux = 0; aux < tam_Tabela; aux++)
        {
            if (tabela_Indice[aux] == n_Chave)
                return aux;
            if (tabela_Indice[aux] < n_Chave)
                return aux - 1;
        }
        return aux - 1;
        break;
    }

    return -1;
}

void SI_montar_Tabela(FILE *arquivo_Binario, int *tabela_Indice, int itens_Pagina)
{
    int aux;

    for (int i = 0; fread(&aux, sizeof(int), 1, arquivo_Binario); i++)
    {
        tabela_Indice[i] = aux;
        //Leitura apenas da chave do primeiro registro de cada página.
        fseek(arquivo_Binario, (itens_Pagina * sizeof(Registro)) - sizeof(int), SEEK_CUR);
    }

    rewind(arquivo_Binario);
}

int SI_defineItensPagina(int n_Registros)
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
        return 500;
    }

    return -1;
}