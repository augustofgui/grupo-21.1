#include "../headers/Geral.h"

void verifParametros (int argc){
    if (argc < 2){
        cout << "Parâmetros insuficientes para a execução. Por favor, informe o arquivo database por argumento.\n";
        exit(1);
    }
}