#ifndef CHACARA_H
#define CHACARA_H

#include "Imovel.h"

class Chacara : public Imovel
{
    bool salao_festa;
    bool salao_jogos;
    bool campo_futebol;
    bool churrasqueira;
    bool piscina;

public:
    Chacara(int = -1, float = -1, string = "", string = "", string = "", string = "", int = -1, int = -1, int = -1, bool = false, bool = false, bool = false, bool = false, bool = false);
    ~Chacara();

    void setSalaoFesta(bool salao_festa);
    void setSalaoJogos(bool salao_jogos);
    void setCampoFutebol(bool campo_futebol);
    void setChurrasqueira(bool churrasqueira);
    void setPiscina(bool piscina);

    bool getSalaoFesta();
    bool getSalaoJogos();
    bool getCampoFutebol();
    bool getChurrasqueira();
    bool getPiscina();

    friend ostream &operator<<(ostream &, Chacara &);
};

#endif