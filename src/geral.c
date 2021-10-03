#include "geral.h"

//argv[1] = Método
//argv[2] = Quantidade
//argv[3] = Situação
//argv[4] = Chave
//argv[5] = [-P] -> printf chaves dos registros

void verif_Parametros(int argc)
{
    if (argc < 5)
    {
        printf("Parâmetros insuficientes para a execução.\n");
        exit(1);
    }
}

//argv[] continuará sendo um array de char, utilizaremos os valores inteiros da tabela ASCII
void array_ToInteger(int argc, char *argv[])
{
    for (int i = 1; i < 6; i++)
        argv[i] -= 48;
}

void imprimirRegistro(Registro x)
{
    printf("Chave do registro: %d\n", x.chave);
    printf("dado1: %ld\n", x.dado1);
    printf("dado2: %s\n", x.dado2);
    printf("dado3: %s\n", x.dado3);
}

FILE *criarArquivo(int metodo_Pesquisa, int nro_Registros, int tipo_Ordenacao)
{
    FILE *arquivo_Binario;
    Registro aux;

    arquivo_Binario = fopen("arquivo_binario.bin", "wb");
    if (!arquivo_Binario)
    {
        printf("Erro ao criar o arquivo binário de registros.\n");
        exit(1);
    }

    if (metodo_Pesquisa == 1 && tipo_Ordenacao > 2)
    {
        printf("O método de acesso sequencial indexado não admite arquivos desordenados. Por favor, corrija os parâmetros de execução.\n");
        exit(1);
    }

    printf("Arquivo binário em criação, aguarde...\n");

    switch (tipo_Ordenacao)
    {
    case 1: //Ordem Crescente.
        for (int i = 0; i < nro_Registros; i++)
        {
            aux.chave = i + 1;
            fwrite(&aux, sizeof(Registro), 1, arquivo_Binario);
        }
        break;
    case 2: //Ordem Decrescente.
        for (int i = nro_Registros; i > 0; i++)
        {
            aux.chave = i;
            fwrite(&aux, sizeof(Registro), 1, arquivo_Binario);
        }
        break;
    case 3:; //Desordenado.
        Registro *array = (Registro *)malloc(nro_Registros * sizeof(Registro));
        srand(time(NULL));

        for (int i = 0; i < nro_Registros; i++)
            array[i].chave = i + 1;

        for (int i = 0; i < nro_Registros; i++)
        {
            int j = rand() % (nro_Registros - 1);
            aux = array[i];
            array[i] = array[j];
            array[j] = aux;
        }

        fwrite(array, sizeof(Registro), nro_Registros, arquivo_Binario);
        free(array);
        break;
    }

    printf("Arquivo binário criado com sucesso! Configurações: %d (método), %d (número de registros), %d (tipo de ordenação).\n", metodo_Pesquisa, nro_Registros, tipo_Ordenacao);
    return arquivo_Binario;
}
