#ifndef IMOVEL_H
#define IMOVEL_H

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
#include <sstream>
#include <utility>

using namespace std;

class Imovel
{
    int id;
    float valor;
    string proprietario;
    string rua;
    string bairro;
    string cidade;
    int numero;
    int quartos;
    int banheiros;

public:
    Imovel(float = -1, string = "", string = "", string = "", string = "", int = -1, int = -1, int = -1);
    virtual ~Imovel();

    void setValor(float valor);
    void setProprietario(string proprietario);
    void setRua(string rua);
    void setBairro(string bairro);
    void setCidade(string bairro);
    void setNumero(int numero);
    void setQuartos(int quartos);
    void setBanheiros(int banheiros);

    float getValor();
    string getProprietario();
    string getRua();
    string getBairro();
    string getCidade();
    int getNumero();
    int getQuartos();
    int getBanheiros();

    friend ostream &operator<<(ostream &out, const Imovel &);
};

#endif