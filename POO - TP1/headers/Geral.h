#include "Imovel.h"
#include "Apartamento.h"
#include "Casa.h"
#include "Chacara.h"

void verifParametros (int argc);
std::vector<std::string> explode(std::string const & s, char delim);
bool buscar_por_proprietario(vector<Imovel*> imoveis_database, string nome);
std::vector<Imovel*> buscar_por_preco_maximo(vector<Imovel*> imoveis_database, float preco);
std::vector<Imovel*> buscar_por_quartos(vector<Imovel*> imoveis_database, int nro_quartos);
