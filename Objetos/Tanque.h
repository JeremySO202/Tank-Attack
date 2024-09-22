//
// Created by jeremy on 21/09/24.
//

#ifndef TANQUE_H
#define TANQUE_H
#include "Objeto.h"


class Tanque : public Objeto {
public:
    void interaccion() override;
    char* recurso() override;
};



#endif //TANQUE_H
