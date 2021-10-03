#include "geral.h"

int main(int argc, char *argv[])
{
    verif_Parametros(argc);
    array_ToInteger(argc, argv);

    switch (argv[1])
    {
    case 1:
        if (!sequencial_Indexado(argc, argv))
        {
            printf("Chave buscada não encontrada.\n");
            exit(1);
        }
        break;
    case 2:
        if (!arvore_Externa(argc, argv))
        {
            printf("Chave buscada não encontrada.\n");
            exit(1);
        }
        break;
    case 3:
        if (!arvore_B(argc, argv))
        {
            printf("Chave buscada não encontrada.\n");
            exit(1);
        }
        break;
    case 4:
        if (!arvore_Bx(argc, argv))
        {
            printf("Chave buscada não encontrada.\n");
            exit(1);
        }
        break;
    default:
        printf("Método de pesquisa externa inválido.\n");
        exit(1);
    }

    return 0;
}