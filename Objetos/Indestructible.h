//
// Created by jeremy on 21/09/24.
//

#ifndef INDESTRUCTIBLE_H
#define INDESTRUCTIBLE_H
#include "Objeto.h"


class Indestructible: public Objeto {
public:
    void interaccion() override;
    const char* recurso() override;
};



#endif //INDESTRUCTIBLE_H
