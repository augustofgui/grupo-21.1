#include "geral.h"

int main(int argc, char argv[])
{
    int array_Parametros[5];
    arrayToInteger(array_Parametros, argc, argv);
    FILE *arquivo_Binario = criarArquivo(array_Parametros[1], array_Parametros[2], array_Parametros[3]);
    int itens_Pagina = defineItensPagina(array_Parametros[2]);
    int tam_Tabela = itens_Pagina / array_Parametros[2] + 1;
    int tabela_Indice[tam_Tabela];

    int indice_Pagina = buscarPagina(tabela_Indice, tam_Tabela, array_Parametros[3], array_Parametros[4]);
}

int buscarPagina(int *tabela_Indice, int tam_Tabela, int tipo_Ordenacao, int chave_Buscada)
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
    }

    return -1;
}

void montarTabela(FILE *arquivo, int *tabela_Indice, int itens_Pagina)
{
    Registro aux[itens_Pagina];

    for (int i = 0; fread(&aux, sizeof(Registro), itens_Pagina, arquivo); i++)
        tabela_Indice[i] = aux[0].chave;
}

int defineItensPagina(int nro_Registros)
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
    }
}