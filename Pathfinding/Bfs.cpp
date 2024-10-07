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
Ruta* Bfs::obtenerRuta(int xi, int yi, int xd, int yd, Mapa* mapa) {
    Ruta* rutaPorVisitar = new Ruta();
    Ruta* ruta = new Ruta();

    bool visited[SIZE][SIZE] = {false};

    rutaPorVisitar->queue(new Nodo(xi, yi));
    visited[yi][xi] = true;
    bool encontrado = false;

    while (rutaPorVisitar->inicio != nullptr && !encontrado) {
        Nodo* node = rutaPorVisitar->dequeue();

        int index = coordToIndex(node->x, node->y);
        for (int i = 0; i < GRAPHSIZE; i++) {
            int newX = i % SIZE;
            int newY = i / SIZE;

            if (mapa->matrizAdyacencia[index][i] != 0 && !visited[newY][newX] && mapa->isValid(newX, newY)) {
                visited[newY][newX] = true;
                rutaPorVisitar->queue(new Nodo(newX, newY, node));
                if (newX == xd && newY == yd) {
                    encontrado = true;
                    break;
                }
            }
        }
    }

    Nodo* node = rutaPorVisitar->final;
    while (node != nullptr) {
        ruta->add(node);
        node = node->padre;
    }

    return ruta;
}
