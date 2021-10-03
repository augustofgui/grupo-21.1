#include "geral.h"

int main(int argc, char *argv[])
{
    verif_Parametros(argc);
    array_ToInteger(argc, argv);

    switch (argv[1])
    {
    case 1:
        if (!sequencial_Indexado(argc, argv))
            imprimir_NaoEncontrado();
        break;
    case 2:
        if (!arvore_Externa(argc, argv))
            imprimir_NaoEncontrado();
        break;
    case 3:
        if (!arvore_B(argc, argv))
            imprimir_NaoEncontrado();
        break;
    case 4:
        if (!arvore_Bx(argc, argv))
            imprimir_NaoEncontrado();
        break;
    default:
        printf("Método de pesquisa externa inválido.\n");
        exit(1);
    }

    return 0;
}