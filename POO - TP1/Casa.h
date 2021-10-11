#ifndef CASA_H
#define CASA_H

#include "Imovel.h"

class Casa : public Imovel
{
    int andares;
    bool sala_jantar;

public:
    Casa(int = -1, float = -1, string = "", string = "", string = "", string = "", int = -1, int = -1, int = -1, int = -1, bool = false);
    ~Casa();

    void setAndares(int andares);
    void setSalaJantar(bool sala_jantar);

    int getAndares();
    bool getSalaJantar();
};

#endif