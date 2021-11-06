#include "Imovel.h"
#include "Apartamento.h"
#include "Casa.h"
#include "Chacara.h"

void verifParametros (int argc);
std::vector<std::string> explode(std::string const & s, char delim);
bool buscar_por_proprietario(vector<Imovel*> imoveis_database);
std::vector<Imovel*> buscar_por_valor_maximo(vector<Imovel*> imoveis_database);
std::vector<Imovel*> buscar_por_quartos(vector<Imovel*> imoveis_database);
std::vector<Imovel*> buscar_por_tipo_imovel(vector<Imovel*> imoveis_database);
std::vector<Imovel*> buscar_por_cidade(vector<Imovel*> imoveis_database);
std::vector<Imovel*> buscar_e_exibe_por_proprietario(vector<Imovel*> imoveis_database);
vector<Imovel *> buscar_por_tipo(vector<Imovel *> imoveis_database, const char * tipo_busca);
bool operator<(const Imovel &s1, const Imovel &s2);
void print_menu_opcoes();
void print_colecao_imoveis(vector<Imovel*> imoveis_database);