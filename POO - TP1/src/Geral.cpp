#include "../headers/Geral.h"

void verifParametros (int argc){
    if (argc < 2){
        cout << "Parâmetros insuficientes para a execução. Por favor, informe o arquivo database por argumento.\n";
        exit(1);
    }
}

std::vector<std::string> explode(std::string const & s, char delim)
{
    std::vector<std::string> result;
    std::istringstream iss(s);

    for (std::string token; std::getline(iss, token, delim); )
    {
        result.push_back(std::move(token));
    }

    return result;
}

bool buscar_por_proprietario(vector<Imovel*> imoveis_database, string nome)
{
    for (int i = 0; i < (int)imoveis_database.size(); i++){
        if (imoveis_database[i]->getProprietario() == nome)
            return true;
    }
    return false;
}