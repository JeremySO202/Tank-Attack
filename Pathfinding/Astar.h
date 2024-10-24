//
// Created by jeremy on 4/10/24.
//

#ifndef ASTAR_H
#define ASTAR_H
#include "Ruta.h"
#include "../Mapa/Mapa.h"




class Astar
{
public:
    static Ruta* obtenerRuta(int xi, int yi, int xd, int yd, Mapa* mapa);
};


#endif //ASTAR_H
