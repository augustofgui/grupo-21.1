#include "../headers/sequencial_indexado.h"

int sequencial_indexado(FILE *arquivo_binario, int nro_metodo, int nro_registros, int nro_situacao, int nro_chave, char argv[5])
{
    //Definição do tamanho das páginas e da tabela.
    int itens_pagina = definir_itens_por_pagina(nro_registros);
    Registro aux[itens_pagina];
    int tam_tabela = nro_registros / itens_pagina;
    int tabela_indice[tam_tabela];

    //Leitura dos índices da tabela.
    montar_tabela(arquivo_binario, tabela_indice, itens_pagina);

    //Busca sequencial na tabela pela página que pode conter a chave buscada.
    int indice_pagina = buscar_indice(tabela_indice, tam_tabela, nro_situacao, nro_chave);

    //Chave buscada menor ou maior (em caso de arquivo decrescente) do que o primeiro índice da tabela.
    if (indice_pagina == -1)
        return 0;

    //Cálculo do deslocamento para leitura da página correspondente ao índice da tabela.
    long int deslocamento_ponteiro = itens_pagina * indice_pagina * sizeof(Registro);
    fseek(arquivo_binario, deslocamento_ponteiro, SEEK_SET);
    fread(aux, sizeof(Registro), itens_pagina, arquivo_binario);

    //Pesquisa sequencial na página lida.
    for (int i = 0; i < itens_pagina; i++)
    {
        if (aux[i].chave == nro_chave)
        {
            printf("Registro encontrado!\n");
            imprimir_registro(aux[i]);
            return 1;
        }
    }

    return 0;
}

int buscar_indice(int *tabela_indice, int tam_tabela, int nro_situacao, int nro_chave)
{
    int aux;

    switch (nro_situacao)
    {
    case 1:
        if (tabela_indice[0] > nro_chave)
            return -1;
        for (aux = 0; aux < tam_tabela; aux++)
        {
            if (tabela_indice[aux] == nro_chave)
                return aux;
            if (tabela_indice[aux] > nro_chave)
                return aux - 1;
        }
        return aux - 1;
        break;
    case 2:
        if (tabela_indice[0] < nro_chave)
            return -1;
        for (aux = 0; aux < tam_tabela; aux++)
        {
            if (tabela_indice[aux] == nro_chave)
                return aux;
            if (tabela_indice[aux] < nro_chave)
                return aux - 1;
        }
        return aux - 1;
        break;
    }

    return -1;
}

void montar_tabela(FILE *arquivo_binario, int *tabela_indice, int itens_pagina)
{
    int aux;

    for (int i = 0; fread(&aux, sizeof(int), 1, arquivo_binario); i++)
    {
        tabela_indice[i] = aux;
        //Leitura apenas da chave do primeiro registro de cada página.
        fseek(arquivo_binario, (itens_pagina * sizeof(Registro)) - sizeof(int), SEEK_CUR);
    }

    rewind(arquivo_binario);
}

int definir_itens_por_pagina(int nro_registros)
{
    switch (nro_registros)
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