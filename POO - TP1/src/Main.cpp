#include "../headers/Imovel.h"
#include "../headers/Apartamento.h"
#include "../headers/Casa.h"
#include "../headers/Chacara.h"
#include "../headers/Geral.h"

#define nro_imoveis 16

int main (int argc, char *argv[]){

    verifParametros(argc);

    vector<Imovel*> imoveis_database;
    Casa* casas_database;
    Apartamento* apartamentos_database;
    Chacara* chacaras_database;
    string linha_imovel;


    ifstream input_file(argv[1]);
    if (!input_file.is_open()) {
        cerr << "Não foi possível abrir o arquivo - '"
             << argv[1] << "'" << endl;
        return EXIT_FAILURE;
    }

    while(getline(input_file, linha_imovel)){
        vector<string> v = explode(linha_imovel, ';');
            if (v[0] == "casa"){
                casas_database = new Casa(stof(v[1]), v[2], v[3], v[4], v[5], stoi(v[6]), stoi(v[7]), stoi(v[8]), stoi(v[9]), stoi(v[10]));
                imoveis_database.push_back(casas_database);
            }
            else if (v[0] == "apartamento"){
                apartamentos_database = new Apartamento(stof(v[1]), v[2], v[3], v[4], v[5], stoi(v[6]), stoi(v[7]), stoi(v[8]), stoi(v[9]), stof(v[10]), stoi(v[11]), stoi(v[12]));
                imoveis_database.push_back(apartamentos_database);
            }
            else if (v[0] == "chacara"){
                chacaras_database = new Chacara(stof(v[1]), v[2], v[3], v[4], v[5], stoi(v[6]), stoi(v[7]), stoi(v[8]), stoi(v[9]), stoi(v[10]), stoi(v[11]), stoi(v[12]), stoi(v[13]));
                imoveis_database.push_back(chacaras_database);
            }
    }

    string nome = "Pedrão kkkk";
    cout << buscar_por_proprietario(imoveis_database, nome) << endl;

}
