#include "Imovel.h"
#include "Apartamento.h"
#include "Casa.h"
#include "Chacara.h"
#include "Geral.h"

#define nro_imoveis 16

int main (int argc, char *argv[]){

    verifParametros(argc, argv);

    FILE* data_base;

    data_base = fopen(argv[1], "rt");

    if (data_base != NULL)
        cout << "OK" << endl;
    else cout << "NÃO OK" << endl;
}
