#include "../headers/geral.h"

void verificar_parametros(int argc, char *argv[])
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

void imprimir_registro(Registro x)
{
    printf("Chave do registro: %d\n", x.chave);
    printf("dado1: %ld\n", x.dado1);
    printf("dado2: %s\n", x.dado2);
    printf("dado3: %s\n", x.dado3);
}

void imprimir_nao_encontrado(int nro_chave)
{
    printf("Chave buscada ( %d ) não encontrada no arquivo binário.\n", nro_chave);
}

FILE *criar_arquivo(int nro_metodo, int nro_registros, int nro_situacao)
{
    FILE *arquivo_binario;
    Registro aux;

    arquivo_binario = fopen("arquivo_binario", "w+b");
    if (!arquivo_binario)
    {
        printf("Erro ao criar o arquivo binário de registros.\n");
        exit(1);
    }

    printf("Arquivo binário em criação, aguarde...\n");

    switch (nro_situacao)
    {
    case 1: //Ordem Crescente.
        for (int i = 0; i < nro_registros; i++)
        {
            aux.chave = i + 1;
            fwrite(&aux, sizeof(Registro), 1, arquivo_binario);
        }
        break;
    case 2: //Ordem Decrescente.
        for (int i = nro_registros; i > 0; i--)
        {
            aux.chave = i;
            fwrite(&aux, sizeof(Registro), 1, arquivo_binario);
        }
        break;
    case 3: //Desordenado.
        for (int i = 0; i < nro_registros; i++)
        {
            aux.chave = i + 1;
            fwrite(&aux, sizeof(Registro), 1, arquivo_binario);
        }

        rewind(arquivo_binario);

        int tam_bloco = 0;
        int max_bloco = nro_registros / 2;
        int max_end;
        int num_trocas = rand() % max_bloco;

        for (int i = 0; i < num_trocas; i++)
        {
            tam_bloco = (rand() % nro_registros) + 1;
            max_end = nro_registros - tam_bloco;
            int end = (max_end != 0) ? rand() % max_end : 1;
            fseek(arquivo_binario, end, SEEK_SET);
            Registro *bloco = (Registro *)calloc(nro_registros, sizeof(Registro));

            fread(bloco, sizeof(Registro), tam_bloco, arquivo_binario);

            for (int j = 0; j < tam_bloco; j++)
            {
                int troca = rand() % tam_bloco;
                Registro aux = bloco[j];
                bloco[j] = bloco[troca];
                bloco[troca] = aux;
            }
            fseek(arquivo_binario, end, SEEK_SET);
            fwrite(bloco, sizeof(Registro), tam_bloco, arquivo_binario);
            rewind(arquivo_binario);
            free(bloco);
        }

        break;
    }
    printf("Arquivo binário criado com sucesso! Configurações: %d (método), %d (número de registros), %d (tipo de ordenação).\n", nro_metodo, nro_registros, nro_situacao);
    rewind(arquivo_binario);
    return arquivo_binario;
}
