#include "Casa.h"

Casa::Casa(int id, float valor, string proprietario, string rua, string bairro, string cidade, int numero, int quartos, int banheiros, int andares, bool sala_jantar) : Imovel(id, valor, proprietario, rua, bairro, cidade, numero, quartos, banheiros), andares(andares), sala_jantar(sala_jantar) {}
Casa::~Casa() {}

void Casa::setAndares(int andares)
{
    this->andares = andares;
}

void Casa::setSalaJantar(bool sala_jantar)
{
    this->sala_jantar = sala_jantar;
}

int Casa::getAndares()
{
    return andares;
}

bool Casa::getSalaJantar()
{
    return sala_jantar;
}

ostream &operator<<(ostream &out, const Casa &casa)
{
    out << "\nAndares: " << casa.andares;
    return out;
}