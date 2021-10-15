#include "Imovel.h"
#include "Apartamento.h"
#include "Casa.h"
#include "Chacara.h"
#include "Geral.h"

#define nro_imoveis 16

int main (int argc, char *argv[]){

    verifParametros(argc, argv);

    Imovel *imoveis[nro_imoveis];

    for (int i = 0; i < nro_imoveis; i++){
            //Implementar leitura do arquivo e comparador para criação de cada objeto do vetor de referência.
            imoveis[i] = new Apartamento();
            imoveis[i] = new Casa();
            imoveis[i] = new Chacara();
    }
}