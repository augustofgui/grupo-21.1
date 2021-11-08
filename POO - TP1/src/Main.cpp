#include "../headers/Imovel.h"
#include "../headers/Apartamento.h"
#include "../headers/Casa.h"
#include "../headers/Chacara.h"
#include "../headers/Geral.h"

int main (int argc, char *argv[]){

    verifParametros(argc); // Verifica os parametros de entrada

    vector<Imovel*> imoveis_database; // Vetor de imoveis polimorfico
    
    // Variaveis auxiliares
    string linha_imovel;
    int opcao_menu = 1;

    // Abre o arquivo de entrada
    ifstream input_file(argv[1]);
    if (!input_file.is_open()) { // Verifica se o arquivo existe e se foi possivel ser aberto
        cerr << "Não foi possível abrir o arquivo - '"
             << argv[1] << "'" << endl;
        return EXIT_FAILURE; 
    }

    // Percorre e lê linha por linha do arquivo
    while(getline(input_file, linha_imovel)){

        // Separa cada linha do arquivo em substrings divididas pelo caractere ";"
        vector<string> v = explode(linha_imovel, ';');
        
        // Verifica qual tipo de imovel foi lido e cria uma nova instancia dele,
        // empurrando para dentro do vetor polimorfico
        if (v[0] == "casa"){
            imoveis_database.push_back(new Casa(stof(v[1]), v[2], v[3], v[4], v[5], stoi(v[6]), stoi(v[7]), stoi(v[8]), stoi(v[9]), stoi(v[10])));
        }
        else if (v[0] == "apartamento"){
            imoveis_database.push_back(new Apartamento(stof(v[1]), v[2], v[3], v[4], v[5], stoi(v[6]), stoi(v[7]), stoi(v[8]), stoi(v[9]), stof(v[10]), stoi(v[11]), stoi(v[12])));
        }
        else if (v[0] == "chacara"){
            imoveis_database.push_back(new Chacara(stof(v[1]), v[2], v[3], v[4], v[5], stoi(v[6]), stoi(v[7]), stoi(v[8]), stoi(v[9]), stoi(v[10]), stoi(v[11]), stoi(v[12]), stoi(v[13])));
        }
    }
    
    // Escreve na tela o menu de opções
    print_menu_opcoes();

    // Loop do menu de opções
    while (opcao_menu){
        // Recebe a entrada do usuário
        cout << "Digite qual opção deseja: ";
        cin >> opcao_menu;

        // Ordena o fluxo dependendo da escolha do usuario 
        switch(opcao_menu){
            case 0 : // Saída
                return 0;
                break;
            case 1 : { // Busca pelo nome do proprietario
                if (buscar_por_proprietario(imoveis_database))
                    cout << "\nO proprietário possui imóveis na coleção!\n" << endl;
                else
                    cout << "\nO proprietário não possui imóveis na coleção.\n" << endl;
                break;
            }
            case 2 : { // Busca pelo valor máximo
                vector <Imovel*> colecao_buscada;
                colecao_buscada = buscar_por_valor_maximo(imoveis_database);
                print_colecao_imoveis(colecao_buscada);
                break;
            }
            case 3 : { // Busca pelo número de quartos
                vector <Imovel*> colecao_buscada;
                colecao_buscada = buscar_por_quartos(imoveis_database);
                print_colecao_imoveis(colecao_buscada);
                break;
            }
            case 4 : { // Busca pelo tipo do imovel
                vector <Imovel*> colecao_buscada;
                colecao_buscada = buscar_por_tipo_imovel(imoveis_database);
                print_colecao_imoveis(colecao_buscada);
                break;
            }
            case 5 : {  // Busca pelo nome da cidade
                vector <Imovel*> colecao_buscada;
                colecao_buscada = buscar_por_cidade(imoveis_database);
                print_colecao_imoveis(colecao_buscada);
                break;
            }
            case 6 : {  // Busca pelo nome proprietario
                vector <int> iteradores;
                iteradores = fazer_iterador(imoveis_database);
                for (int i = 0; i < (int) iteradores.size(); i++){
                    cout << *imoveis_database[iteradores[i]] << endl;
                    cout << "- - - - -\n" << endl;
                }
                break;
            }
            case 7 : {  // Imprime ou salva a coleção de imóveis
                imprimir_ou_salvar(imoveis_database);
                break;
            }
            case 8 : {  // Escreve na tela o menu de opções
                print_menu_opcoes();
                break;
            }
            default : {  // Opção inválida
                cout << "Opção inválida!" << endl;
                break;
            }
        } 
    }
}
