#ifndef APARTAMENTO_H
#define APARTAMENTO_H

#include "Imovel.h"

class Apartamento : public Imovel
{
    int andar;
    float taxa_condominio;
    bool elevador;
    bool sacada;

public:
    Apartamento(int = -1, float = -1, string = "", string = "", string = "", string = "", int = -1, int = -1, int = -1, int = -1, float = -1, bool = false, bool = false);
    ~Apartamento();

    void setAndar(int andar);
    void setTaxaCondominio(float taxa_condominio);
    void setElevador(bool elevador);
    void setSacada(bool sacada);

    int getAndar();
    float getTaxaCondominio();
    bool getElevador();
    bool getSacada();

    friend ostream &operator<<(ostream &, const Apartamento &);
};

#endif