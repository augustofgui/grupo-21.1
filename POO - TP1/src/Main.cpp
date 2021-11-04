#include "../headers/Imovel.h"
#include "../headers/Apartamento.h"
#include "../headers/Casa.h"
#include "../headers/Chacara.h"
#include "../headers/Geral.h"

#define nro_imoveis 16

int main (int argc, char *argv[]){

    verifParametros(argc);

    string linha_imovel;
    vector<string> linhas;

    ifstream input_file(argv[1]);
    if (!input_file.is_open()) {
        cerr << "Não foi possível abrir o arquivo - '"
             << argv[1] << "'" << endl;
        return EXIT_FAILURE;
    }

    while(getline(input_file, linha_imovel)){
        cout << linha_imovel << endl;
        vector<string> v = explode(linha_imovel, ';');
        for (int i = 0; i < (int)v.size(); i++)
            cout << v[i] << endl;
    }
}
