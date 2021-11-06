#include "../headers/Geral.h"

// Verifica os parametros do programa
void verifParametros (int argc){
    if (argc < 2){
        cout << "Parâmetros insuficientes para a execução. Por favor, informe o arquivo database por argumento.\n";
        exit(1);
    }
}

// Separa uma string em substrings dividindo por um caractere
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

bool buscar_por_proprietario(vector<Imovel*> imoveis_database)
{
    char nome [100];
    
    getchar();
    cout << "\nInsira o nome do proprietário: ";
    cin.getline(nome, sizeof(nome));

    for (int i = 0; i < (int)imoveis_database.size(); i++){
        if (imoveis_database[i]->getProprietario() == nome)
            return true;
    }
    return false;
}

std::vector<Imovel*> buscar_por_valor_maximo(vector<Imovel*> imoveis_database)
{
    float preco;
    
    cout << "\nInsira o valor máximo: ";
    cin >> preco;
    cout << endl;

    vector<Imovel*> imoveis_preco_maximo;
    for (int i = 0; i < (int)imoveis_database.size(); i++){
        if(imoveis_database[i]->getValor() <= preco)
            imoveis_preco_maximo.push_back(imoveis_database[i]);
    }
    return imoveis_preco_maximo;
}

std::vector<Imovel*> buscar_por_quartos(vector<Imovel*> imoveis_database)
{
    int nro_quartos;
    
    cout << "\nInsira o número de quartos: ";
    cin >> nro_quartos;

    vector<Imovel*> imoveis_quartos;
    for (int i = 0; i < (int)imoveis_database.size(); i++){
        if(imoveis_database[i]->getQuartos() >= nro_quartos)
            imoveis_quartos.push_back(imoveis_database[i]);
    }
    return imoveis_quartos;
}

std::vector<Imovel*> buscar_por_cidade(vector<Imovel*> imoveis_database)
{
    char nome_cidade [100];
    
    getchar();
    cout << "\nInsira o nome da cidade: ";
    cin.getline(nome_cidade, sizeof(nome_cidade));
    cout << endl;

    vector<Imovel*> imoveis_cidade;
    for (int i = 0; i < (int)imoveis_database.size(); i++){
        if (imoveis_database[i]->getCidade() == nome_cidade)
            imoveis_cidade.push_back(imoveis_database[i]);
    }
    return imoveis_cidade;
}

void print_menu_opcoes()
{
    cout << "\n - Menu de Opções -" << endl
         << "\n0 - Sair" << endl
         << "1 - Buscar por proprietário" << endl
         << "2 - Buscar por valor máximo" << endl
         << "3 - Buscar por número de quartos" << endl
         << "4 - Buscar por tipo do imóvel" << endl
         << "5 - Buscar por cidade" << endl
         << "6 - Criar iterador para um proprietário" << endl
         << "7 - Exibir ou salvar coleção de imóveis" << endl
         << "8 - Imprimir menu de opções" << endl << endl;
}

void print_colecao_imoveis(vector<Imovel*> imoveis_database){
    for (int i = 0; i < (int)imoveis_database.size(); i++){
        cout << *imoveis_database[i] << endl;
        cout << "- - - - -\n" << endl;
    }
}

bool operator<(const Imovel &s1, const Imovel &s2){
    return s1.getValor() < s2.getValor();
}

vector<Imovel*> buscar_por_tipo_imovel(vector<Imovel*> imoveis_database){
    char tipo_imovel [100];
    vector<Imovel*> vetor_imoveis;
    
    getchar();
    cout << "\nInsira o tipo do imóvel: ";
    cin.getline(tipo_imovel, sizeof(tipo_imovel));
    cout << endl;

    if (strcmp(tipo_imovel, "casa") == 0){
        for (int i = 0; i < (int)imoveis_database.size(); i++){
            if (typeid(*imoveis_database[i]).name() == typeid(class Casa).name())
                vetor_imoveis.push_back(imoveis_database[i]);
        }
    }
    else if (strcmp(tipo_imovel, "apartamento") == 0){
        for (int i = 0; i < (int)imoveis_database.size(); i++){
            if (typeid(*imoveis_database[i]).name() == typeid(class Apartamento).name())
                vetor_imoveis.push_back(imoveis_database[i]);
        }
    }
    else if (strcmp(tipo_imovel, "chacara") == 0){
        for (int i = 0; i < (int)imoveis_database.size(); i++){
            if (typeid(*imoveis_database[i]).name() == typeid(class Chacara).name())
                vetor_imoveis.push_back(imoveis_database[i]);
        }
    }

    for (int i = 0; i < (int)vetor_imoveis.size();i++){
        for (int j = 0; j < (int)vetor_imoveis.size() - (i + 1); j++){
            if (vetor_imoveis[j]->getValor() < vetor_imoveis[j+1]->getValor()){
                Imovel* aux = vetor_imoveis[j];
                vetor_imoveis[j] = vetor_imoveis[j+1];
                vetor_imoveis[j+1] = aux;
            }
        }
    }

    return vetor_imoveis;
}