#include "Chacara.h"

Chacara::Chacara(int id, float valor, string proprietario, string rua, string bairro, string cidade, int numero, int quartos, int banheiros, bool salao_festa, bool salao_jogos, bool campo_futebol, bool churrasqueira, bool piscina) : Imovel(id, valor, proprietario, rua, bairro, cidade, numero, quartos, banheiros), salao_festa(salao_festa), salao_jogos(salao_jogos), campo_futebol(campo_futebol), churrasqueira(churrasqueira), piscina(piscina) {}
Chacara::~Chacara() {}

void Chacara::setSalaoFesta(bool salao_festa)
{
    this->salao_festa = salao_festa;
}

void Chacara::setSalaoJogos(bool salao_jogos)
{
    this->salao_jogos = salao_jogos;
}

void Chacara::setCampoFutebol(bool campo_futebol)
{
    this->campo_futebol = campo_futebol;
}

void Chacara::setChurrasqueira(bool churrasqueira)
{
    this->churrasqueira = churrasqueira;
}

void Chacara::setPiscina(bool piscina)
{
    this->piscina = piscina;
}

bool Chacara::getSalaoFesta()
{
    return salao_festa;
}

bool Chacara::getSalaoJogos()
{
    return salao_jogos;
}

bool Chacara::getCampoFutebol()
{
    return campo_futebol;
}

bool Chacara::getChurrasqueira()
{
    return churrasqueira;
}

bool Chacara::getPiscina()
{
    return piscina;
}

ostream &operator<<(ostream &out, const Chacara &chacara)
{
    out << "\nPiscina: " << chacara.piscina;
    return out;
}