#include "../headers/Imovel.h"

Imovel::Imovel(float valor, string proprietario, string rua, string bairro, string cidade, int numero, int quartos, int banheiros) : valor(valor), proprietario(proprietario), rua(rua), bairro(bairro), cidade(cidade), numero(numero), quartos(quartos), banheiros(banheiros) {}
Imovel::~Imovel() {}

void Imovel::setValor(float valor)
{
    this->valor = valor;
}

void Imovel::setProprietario(string proprietario)
{
    this->proprietario = proprietario;
}

void Imovel::setRua(string rua)
{
    this->rua = rua;
}

void Imovel::setBairro(string bairro)
{
    this->bairro = bairro;
}

void Imovel::setCidade(string cidade)
{
    this->cidade = cidade;
}

void Imovel::setNumero(int numero)
{
    this->numero = numero;
}

void Imovel::setQuartos(int quartos)
{
    this->quartos = quartos;
}

void Imovel::setBanheiros(int banheiros)
{
    this->banheiros = banheiros;
}

float Imovel::getValor()
{
    return valor;
}

string Imovel::getProprietario()
{
    return proprietario;
}

string Imovel::getRua()
{
    return rua;
}

string Imovel::getBairro()
{
    return bairro;
}

string Imovel::getCidade()
{
    return cidade;
}

int Imovel::getNumero()
{
    return numero;
}

int Imovel::getQuartos()
{
    return quartos;
}

int Imovel::getBanheiros()
{
    return banheiros;
}

ostream &operator<<(ostream &out, Imovel &imovel)
{
    out << setprecision(2);
    out << "\nProprietario: " << imovel.getProprietario()
        << "\nValor: " << fixed << imovel.getValor()
        << "\nQuartos: " << imovel.getQuartos()
        << "\nRua: " << imovel.getRua()
        << "\nBairro: " << imovel.getBairro()
        << "\nCidade: " << imovel.getCidade();
    return out;
}