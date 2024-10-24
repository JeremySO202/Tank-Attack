//
// Created by jeremy on 28/09/24.
//

#ifndef BFS_H
#define BFS_H
#include "Ruta.h"
#include "../Mapa/Mapa.h"


class Bfs {

    public:

    static Ruta* obtenerRuta(int xi, int yi, int xd, int yd, Mapa* mapa);


};



#endif //BFS_H
