//
// Created by jeremy on 9/10/24.
//

#include "LineaVista.h"

#include "../Objetos/Tanque.h"
#include <typeinfo>

/**
 *
 * @param xi Eje x de inicio
 * @param yi Eje y de inicio
 * @param xd Eje x de destino
 * @param yd Eje y de destino
 * @param mapa Mapa a recorrer
 * @param rebotes Cantidad de rebotes
 * @return
 */
Ruta* LineaVista::obtenerRuta(int xi, int yi, int xd, int yd, Mapa* mapa, int rebotes)
{
    Ruta* ruta = new Ruta;

    int dirX = 0;
    int dirY = 0;


    if (xd - xi > 0)
    {
        dirX = 1;
    }
    if (xd - xi < 0)
    {
        dirX = -1;
    }
    if (yd - yi > 0)
    {
        dirY = 1;
    }
    if (yd - yi < 0)
    {
        dirY = -1;
    }

    int auxX = xi + dirX;
    int auxY = yi + dirY;

    bool rebote = false;


    while (rebotes >= 0)
    {
        if (!rebote && !mapa->isValid(auxX, auxY) && (auxX != xi || auxY - dirY != yi))
        {
            try
            {
                if (typeid(*mapa->matrizMapa[auxY][auxX]) == typeid(Tanque))
                {
                    ruta->queue(new Nodo(auxX, auxY));
                    break;
                }
            }
            catch (...)
            {
            }
            dirX = -dirX;
            dirY = -dirY;
            rebote = true;
        }
        if (!rebote)
        {
            ruta->queue(new Nodo(auxX, auxY));
        }
        else
        {
            xi = -1;
            yi = -1;
            if (rebotes == 0)
            {
                break;
            }
            auxX = auxX + dirX;
            auxY = auxY + dirY;
            ruta->queue(new Nodo(auxX, auxY));
            rebote = false;
            rebotes--;
        }
        auxX = auxX + dirX;
        auxY = auxY + dirY;
    }

    return ruta;
}
