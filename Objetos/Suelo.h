//
// Created by jeremy on 21/09/24.
//

#ifndef SUELO_H
#define SUELO_H
#include "Objeto.h"


class Suelo: public Objeto {
public:
    void interaccion() override;
    const char* recurso() override;
};



#endif //SUELO_H
