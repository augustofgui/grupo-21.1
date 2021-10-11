#include "../headers/geral.h"

int main(int argc, char *argv[])
{
    verif_Parametros(argc, argv);

    int n_Metodo = atoi(argv[1]);
    int n_Registros = atoi(argv[2]);
    int n_Situacao = atoi(argv[3]);
    int n_Chave = atoi(argv[4]);

    FILE *arquivo_Binario = criar_Arquivo(n_Metodo, n_Registros, n_Situacao);

    switch (n_Metodo)
    {
    case 1:
        if (!sequencial_Indexado(arquivo_Binario, n_Metodo, n_Registros, n_Situacao, n_Chave, argv[5]))
            imprimir_NaoEncontrado(n_Chave);
        break;
    case 2:
        if (!arvore_Externa(arquivo_Binario, n_Metodo, n_Registros, n_Situacao, n_Chave, argv[5]))
            imprimir_NaoEncontrado(n_Chave);
        break;
    case 3:
        if (!arvore_B(arquivo_Binario, n_Metodo, n_Registros, n_Situacao, n_Chave, argv[5]))
            imprimir_NaoEncontrado(n_Chave);
        break;
    case 4:
        if (!arvore_Bx(arquivo_Binario, n_Metodo, n_Registros, n_Situacao, n_Chave, argv[5]))
            imprimir_NaoEncontrado(n_Chave);
        break;
    }

    return 0;
}