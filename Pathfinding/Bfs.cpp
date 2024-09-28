//
// Created by jeremy on 28/09/24.
//

#include "Bfs.h"

#include <stddef.h>

/**
 * Transforma una coordenada a su indice para la matriz de adyacencia
 * @param x eje x
 * @param y eje y
 * @return
 */
int coordToIndex(int x, int y)
{
    return y * SIZE + x;
}

/**
 * Obtiene la ruta de una coordenada a otra
 * @param xi eje x de inicio
 * @param yi eje y de inicio
 * @param xd eje x de destino
 * @param yd eje y de destino
 * @param mapa mapa a navegar
 * @return ruta que se debe seguir
 */
Ruta* Bfs::obtenerRuta(int xi, int yi, int xd, int yd, Mapa* mapa)
{

    Ruta* rutaPorVisitar = new Ruta();
    Ruta* ruta = new Ruta();

    bool visited[SIZE][SIZE] = {false};

    rutaPorVisitar->queue(new Nodo (xi,yi));
    visited[yi][xi] = true;
    bool band = true;
    while (rutaPorVisitar->inicio!=nullptr && band)
    {
        Nodo* node = rutaPorVisitar->dequeue();

        int index = coordToIndex(node->x,node->y);
        for (int i = 0; i < GRAPHSIZE; i++)
        {
            if (mapa->matrizAdyacencia[index][i] != 0 && !visited[int(i/SIZE)][i%SIZE])
            {
                visited[int(i/SIZE)][i%SIZE] = true;
                rutaPorVisitar->queue(new Nodo (i%SIZE,int(i/SIZE), node));
                if (i%SIZE == xd && int(i/SIZE) == yd)
                {
                    band = false;
                    break;
                }

            }
        }
    }
    Nodo* node = rutaPorVisitar->final;
    while (node != nullptr)
    {
        ruta->add(node);
        node = node->padre;
    }

    return ruta;



}

