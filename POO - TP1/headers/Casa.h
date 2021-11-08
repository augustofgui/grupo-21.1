#ifndef CASA_H
#define CASA_H

#include "Imovel.h"

class Casa : public Imovel
{
    int andares;
    bool sala_jantar;

public:
    Casa(float = -1, string = "", string = "", string = "", string = "", int = -1, int = -1, int = -1, int = -1, bool = false);
    ~Casa();

    void setAndares(int andares);
    void setSalaJantar(bool sala_jantar);

    int getAndares();
    bool getSalaJantar();

    virtual void saida (ostream &out);
    friend ostream &operator <<(ostream & out, Casa &casa);
};

#endif