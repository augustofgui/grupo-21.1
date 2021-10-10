#include "../headers/geral.h"

void verif_Parametros(int argc, char *argv[])
{
    int aux1, aux2;

    if (argc < 5)
    {
        printf("Parâmetros insuficientes para a execução.\n");
        exit(1);
    }

    aux2 = atoi(argv[1]);

    if (aux2 != 1 && aux2 != 2 && aux2 != 3 && aux2 != 4)
    {
        printf("Método fornecido não corresponde ao enunciado do trabalho. Por favor, corrija os parâmetros de execução.\n");
        exit(1);
    }

    aux1 = atoi(argv[2]);

    if (aux1 != 100 && aux1 != 1000 && aux1 != 10000 && aux1 != 100000 && aux1 != 1000000)
    {
        printf("Número de registros fornecido não corresponde ao enunciado do trabalho. Por favor, corrija os parâmetros de execução.\n");
        exit(1);
    }

    aux1 = atoi(argv[3]);

    if (aux1 != 1 && aux1 != 2 && aux1 != 3)
    {
        printf("Situação fornecida não corresponde ao enunciado do trabalho. Por favor, corrija os parâmetros de execução.\n");
        exit(1);
    }

    if (aux1 == 3 && aux2 == 1)
    {
        printf("O método de acesso sequencial indexado não admite arquivos desordenados. Por favor, corrija os parâmetros de execução.\n");
        exit(1);
    }
}

void imprimir_Registro(Registro x)
{
    printf("Chave do registro: %d\n", x.chave);
    printf("dado1: %ld\n", x.dado1);
    printf("dado2: %s\n", x.dado2);
    printf("dado3: %s\n", x.dado3);
}

void imprimir_NaoEncontrado(int n_Chave)
{
    printf("Chave buscada ( %d ) não encontrada no arquivo binário.\n", n_Chave);
}

FILE *criar_Arquivo(int n_Metodo, int n_Registros, int n_Situacao)
{
    FILE *arquivo_Binario;
    Registro aux;

    arquivo_Binario = fopen("arquivo_binario.bin", "wb");
    if (!arquivo_Binario)
    {
        printf("Erro ao criar o arquivo binário de registros.\n");
        exit(1);
    }

    printf("Arquivo binário em criação, aguarde...\n");

    switch (n_Situacao)
    {
    case 1: //Ordem Crescente.
        for (int i = 0; i < n_Registros; i++)
        {
            aux.chave = i + 1;
            fwrite(&aux, sizeof(Registro), 1, arquivo_Binario);
        }
        break;
    case 2: //Ordem Decrescente.
        for (int i = n_Registros; i > 0; i++)
        {
            aux.chave = i;
            fwrite(&aux, sizeof(Registro), 1, arquivo_Binario);
        }
        break;
    case 3:; //Desordenado.
        Registro *array = (Registro *)malloc(n_Registros * sizeof(Registro));
        srand(time(NULL));

        for (int i = 0; i < n_Registros; i++)
            array[i].chave = i + 1;

        for (int i = 0; i < n_Registros; i++)
        {
            int j = rand() % (n_Registros - 1);
            aux = array[i];
            array[i] = array[j];
            array[j] = aux;
        }

        fwrite(array, sizeof(Registro), n_Registros, arquivo_Binario);
        free(array);
        break;
    }

    printf("Arquivo binário criado com sucesso! Configurações: %d (método), %d (número de registros), %d (tipo de ordenação).\n", n_Metodo, n_Registros, n_Situacao);
    return arquivo_Binario;
}
