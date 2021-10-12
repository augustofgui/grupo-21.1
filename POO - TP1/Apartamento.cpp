#include "Apartamento.h"

Apartamento::Apartamento(int id, float valor, string proprietario, string rua, string bairro, string cidade, int numero, int quartos, int banheiros, int andar, float taxa_condominio, bool elevador, bool sacada) : Imovel(id, valor, proprietario, rua, bairro, cidade, numero, quartos, banheiros), andar(andar), taxa_condominio(taxa_condominio), elevador(elevador), sacada(sacada) {}
Apartamento::~Apartamento() {}

void Apartamento::setAndar(int andar)
{
    this->andar = andar;
}

void Apartamento::setTaxaCondominio(float taxa_condominio)
{
    this->taxa_condominio = taxa_condominio;
}

void Apartamento::setElevador(bool elevador)
{
    this->elevador = elevador;
}

void Apartamento::setSacada(bool sacada)
{
    this->sacada = sacada;
}

int Apartamento::getAndar()
{
    return andar;
}

float Apartamento::getTaxaCondominio()
{
    return taxa_condominio;
}

bool Apartamento::getElevador()
{
    return elevador;
}

bool Apartamento::getSacada()
{
    return sacada;
}

ostream &operator<<(ostream &out, const Apartamento &apartamento)
{
    out << "\nElevador: " << apartamento.elevador;
    return out;
}