//
// Created by jeremy on 9/10/24.
//

#ifndef LINEAVISTA_H
#define LINEAVISTA_H
#include "Ruta.h"
#include "../Mapa/Mapa.h"


class LineaVista {

public:

    static Ruta* obtenerRuta(int xi, int yi, int xd, int yd, Mapa* mapa, int rebotes);

};



#endif //LINEAVISTA_H
