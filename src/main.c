#include "geral.h"

int main(int argc, char *argv[])
{
    switch (atoi(argv[1]))
    {
    case 1:
        sequencial_Indexado(argc, argv);
        break;
    case 2:
        arvore_Externa(argc, argv);
        break;
    case 3:
        arvore_B(argc, argv);
        break;
    case 4:
        arvore_Bx(argc, argv);
        break;
    default:
        printf("Método de pesquisa externa inválido.\n");
        exit(1);
    }

    return 0;
}