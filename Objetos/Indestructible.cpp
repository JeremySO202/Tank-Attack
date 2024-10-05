//
// Created by jeremy on 21/09/24.
//

#include "Indestructible.h"

#include <iostream>
#include <ostream>

void Indestructible::interaccion()
{
    std::cout << "Interaccion con indestructible" << std::endl;
}

const char* Indestructible::recurso()
{
    return "#";
}