//
// Created by mvasquezr on 10/4/24.
//

#ifndef RANDOMMOVEMENT_H
#define RANDOMMOVEMENT_H

#include "../Mapa/Mapa.h"
#include "../Pathfinding/Ruta.h"
#include <cstdlib> // Para rand()
#include <ctime>   // Para time()

/**
 * @class RandomMovement
 * @brief Clase para determinar una ruta de movimiento aleatorio.
 */
class RandomMovement {
public:
    RandomMovement();
    Ruta* obtenerMovimientoAleatorio(int xi, int yi, Mapa* mapa, int radio = 2);
};

#endif // RANDOMMOVEMENT_H
