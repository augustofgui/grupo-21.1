#include "../headers/Geral.h"

// Verifica os parametros do programa
void verifParametros(int argc)
{
    if (argc < 2)
    {
        cout << "Parâmetros insuficientes para a execução. Por favor, informe o arquivo database por argumento.\n";
        exit(1);
    }
}

// Separa uma string em substrings dividindo por um caractere
std::vector<std::string> explode(std::string const &s, char delim)
{
    std::vector<std::string> result;
    std::istringstream iss(s);

    for (std::string token; std::getline(iss, token, delim);)
    {
        result.push_back(std::move(token));
    }

    return result;
}

bool buscar_por_proprietario(vector<Imovel *> imoveis_database)
{
    char nome[100];

    getchar();
    cout << "\nInsira o nome do proprietário: ";
    cin.getline(nome, sizeof(nome));

    for (int i = 0; i < (int)imoveis_database.size(); i++)
    {
        if (imoveis_database[i]->getProprietario() == nome)
            return true;
    }
    return false;
}

std::vector<Imovel *> buscar_por_valor_maximo(vector<Imovel *> imoveis_database)
{
    float preco;

    cout << "\nInsira o valor máximo: ";
    cin >> preco;
    cout << endl;

    vector<Imovel *> imoveis_preco_maximo;
    for (int i = 0; i < (int)imoveis_database.size(); i++)
    {
        if (imoveis_database[i]->getValor() <= preco)
            imoveis_preco_maximo.push_back(imoveis_database[i]);
    }
    return imoveis_preco_maximo;
}

std::vector<Imovel *> buscar_por_quartos(vector<Imovel *> imoveis_database)
{
    int nro_quartos;

    cout << "\nInsira o número de quartos: ";
    cin >> nro_quartos;

    vector<Imovel *> imoveis_quartos;
    for (int i = 0; i < (int)imoveis_database.size(); i++)
    {
        if (imoveis_database[i]->getQuartos() >= nro_quartos)
            imoveis_quartos.push_back(imoveis_database[i]);
    }
    return imoveis_quartos;
}

std::vector<Imovel *> buscar_por_cidade(vector<Imovel *> imoveis_database)
{
    char nome_cidade[100];

    getchar();
    cout << "\nInsira o nome da cidade: ";
    cin.getline(nome_cidade, sizeof(nome_cidade));
    cout << endl;

    vector<Imovel *> imoveis_cidade;
    for (int i = 0; i < (int)imoveis_database.size(); i++)
    {
        if (imoveis_database[i]->getCidade() == nome_cidade)
            imoveis_cidade.push_back(imoveis_database[i]);
    }
    return imoveis_cidade;
}

vector<int> fazer_iterador (vector<Imovel *> imoveis_database){
    char nome_proprietario[100];
    vector <int> iteradores;

    getchar();
    cout << "\nInsira o nome do proprietário: ";
    cin.getline(nome_proprietario, sizeof(nome_proprietario));
    cout << endl;

    for (int i = 0; i < (int) imoveis_database.size(); i++){
        if (imoveis_database[i]->getProprietario() == nome_proprietario)
            iteradores.push_back(i);
    }

    return iteradores;
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
         << "8 - Imprimir menu de opções" << endl
         << endl;
}

void print_colecao_imoveis(vector<Imovel *> imoveis_database)
{
    for (int i = 0; i < (int)imoveis_database.size(); i++)
    {
        cout << *imoveis_database[i] << endl;
        cout << "- - - - -\n" << endl;
    }
}

vector<Imovel *> buscar_por_tipo(vector<Imovel *> imoveis_database, const char * tipo_busca)
{
    vector<Imovel *> vetor_imoveis;
    
    if (strcmp(tipo_busca, "casa") == 0)
    {
        for (int i = 0; i < (int)imoveis_database.size(); i++)
        {
            if (typeid(*imoveis_database[i]).name() == typeid(class Casa).name())
                vetor_imoveis.push_back(imoveis_database[i]);
        }
    }
    else if (strcmp(tipo_busca, "apartamento") == 0)
    {
        for (int i = 0; i < (int)imoveis_database.size(); i++)
        {
            if (typeid(*imoveis_database[i]).name() == typeid(class Apartamento).name())
                vetor_imoveis.push_back(imoveis_database[i]);
        }
    }
    else if (strcmp(tipo_busca, "chacara") == 0)
    {
        for (int i = 0; i < (int)imoveis_database.size(); i++)
        {
            if (typeid(*imoveis_database[i]).name() == typeid(class Chacara).name())
                vetor_imoveis.push_back(imoveis_database[i]);
        }
    }

    return vetor_imoveis;
}

bool compararImoveis(const Imovel *imovel1, const Imovel *imovel2){
    return imovel1->getValor() < imovel2->getValor();
}

vector<Imovel *> buscar_por_tipo_imovel(vector<Imovel *> imoveis_database)
{
    char tipo_imovel[100];
    vector<Imovel *> vetor_imoveis;

    getchar();
    cout << "\nInsira o tipo do imóvel: ";
    cin.getline(tipo_imovel, sizeof(tipo_imovel));
    cout << endl;

    for(auto& c : tipo_imovel)
        c = tolower(c);

    vetor_imoveis = buscar_por_tipo(imoveis_database, tipo_imovel);

    std::sort(vetor_imoveis.begin(), vetor_imoveis.end(), compararImoveis);

    return vetor_imoveis;
}

void imprimir_ou_salvar(vector <Imovel*> imoveis_database)
{
    char opcao[100];

    getchar();
    cout << "\nVocê gostaria de imprimir ou salvar? ";
    cin.getline(opcao, sizeof(opcao));
    cout << endl;

    for(auto& c : opcao)
        c = tolower(c);

    if (strcmp(opcao, "imprimir") == 0)
        print_colecao_imoveis(imoveis_database);
    else if (strcmp(opcao, "salvar") == 0){
        ofstream arquivo_saida;
        arquivo_saida.open("salvar_imoveis.txt");

        for (int i = 0; i < (int)imoveis_database.size(); i++){
            if (typeid(*imoveis_database[i]).name() == typeid(class Casa).name()){
                Casa* casa = dynamic_cast<Casa *> (imoveis_database[i]);
                arquivo_saida << "casa;" <<
                casa->getValor() << ";" <<
                casa->getProprietario() << ";" <<
                casa->getRua() << ";" <<
                casa->getBairro() << ";" <<
                casa->getCidade() << ";" <<
                casa->getNumero() << ";" <<
                casa->getQuartos() << ";" <<
                casa->getBanheiros() << ";" <<
                casa->getAndares() << ";" <<
                casa->getSalaJantar() << ";" << endl;
            }
            else if (typeid(*imoveis_database[i]).name() == typeid(class Apartamento).name()){
                Apartamento* apartamento = dynamic_cast<Apartamento* > (imoveis_database[i]);
                arquivo_saida << "apartamento;" <<
                apartamento->getValor() << ";" <<
                apartamento->getProprietario() << ";" <<
                apartamento->getRua() << ";" <<
                apartamento->getBairro() << ";" <<
                apartamento->getCidade() << ";" <<
                apartamento->getNumero() << ";" <<
                apartamento->getQuartos() << ";" <<
                apartamento->getBanheiros() << ";" <<
                apartamento->getAndar() << ";" <<
                apartamento->getTaxaCondominio() << ";" <<
                apartamento->getElevador() << ";" <<
                apartamento->getSacada() << ";" << endl;
            }
            else if (typeid(*imoveis_database[i]).name() == typeid(class Chacara).name()){
                Chacara* chacara = dynamic_cast<Chacara* > (imoveis_database[i]);
                arquivo_saida << "chacara;" <<
                chacara->getValor() << ";" <<
                chacara->getProprietario() << ";" <<
                chacara->getRua() << ";" <<
                chacara->getBairro() << ";" <<
                chacara->getCidade() << ";" <<
                chacara->getNumero() << ";" <<
                chacara->getQuartos() << ";" <<
                chacara->getBanheiros() << ";" <<
                chacara->getSalaoFesta() << ";" <<
                chacara->getSalaoJogos() << ";" <<
                chacara->getCampoFutebol() << ";" <<
                chacara->getChurrasqueira() << ";" <<
                chacara->getPiscina() << ";" << endl;
            }
        }
        arquivo_saida.close();
    }
    cout << "Coleção de imóveis salva no arquivo 'salvar_imoveis.txt'.\n" << endl;
}