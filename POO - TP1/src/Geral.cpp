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

std::vector<Imovel*> buscar_por_preco_maximo(vector<Imovel*> imoveis_database, float preco){
    vector<Imovel*> imoveis_preco_maximo;
    for (int i = 0; i < (int)imoveis_database.size(); i++){
        if(imoveis_database[i]->getValor() <= preco)
            imoveis_preco_maximo.push_back(imoveis_database[i]);
    }
    return imoveis_preco_maximo;
}

std::vector<Imovel*> buscar_por_quartos(vector<Imovel*> imoveis_database, int nro_quartos){
    vector<Imovel*> imoveis_quartos;
    for (int i = 0; i < (int)imoveis_database.size(); i++){
        if(imoveis_database[i]->getQuartos() >= nro_quartos)
            imoveis_quartos.push_back(imoveis_database[i]);
    }
    return imoveis_quartos;
}

std::vector<Imovel*> buscar_por_cidade(vector<Imovel*> imoveis_database, string nome_cidade){
    vector<Imovel*> imoveis_cidade;
    for (int i = 0; i < (int)imoveis_database.size(); i++){
        if (imoveis_database[i]->getCidade() == nome_cidade)
            imoveis_cidade.push_back(imoveis_database[i]);
    }
    return imoveis_cidade;
}
