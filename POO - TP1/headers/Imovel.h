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
    float valor;
    string proprietario;
    string rua;
    string bairro;
    string cidade;
    int numero;
    int quartos;
    int banheiros;

public:
    Imovel(float valor = -1, string proprietario = "", string rua = "", string bairro = "", string cidade = "", int numero = -1, int quartos = -1, int banheiros = -1);
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

    virtual void saida (ostream &out){
        out << "Proprietario: " << proprietario << endl
            << "    Valor: " << fixed << valor << endl
            << "    Quartos: " << quartos << endl
            << "    Rua: " << rua << endl
            << "    Bairro: " << bairro << endl
            << "    Cidade: " << cidade << endl;
    }
    
    friend ostream &operator<<(ostream &out, Imovel &imovel)
    {
        imovel.saida(out);
        return out;
    }
};

#endif