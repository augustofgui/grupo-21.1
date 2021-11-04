#include "../headers/Geral.h"
#include <fstream>

void verifParametros (int argc, char *argv[]){
    if (argc < 2){
        cout << "Parâmetros insuficientes para a execução. Por favor, informe o arquivo database por argumento.\n";
        exit(1);
    }
}