//
// Created by jeremy on 4/10/24.
//

#include "Astar.h"

#include "ListaPrioridad.h"


#include <cmath>
/**
     * Calcula la heuristica de un punto a A a un punto B
     * @param x1 cordenada x de origen
     * @param y1 cordenada y de origen
     * @param x2 cordenada x de destino
     * @param y2 cordenada y de destino
     * @return
     */


float heuristica(int x1, int y1, int x2, int y2)
{
    int deltaX = abs(x2 - x1);
    int deltaY = abs(y2 - y1);

    int diagonales = std::min(deltaX, deltaY);
    int rectos = abs(deltaX - deltaY);

    return diagonales * 14 + rectos * 10;
}

/**
 * Transforma una coordenada a su indice para la matriz de adyacencia
 * @param x eje x
 * @param y eje y
 * @return
 */
int coordToIndexx(int x, int y)
{
    return y * SIZE + x;
}


Ruta* Astar::obtenerRuta(int xi, int yi, int xd, int yd, Mapa* mapa)
{
    Ruta* ruta = new Ruta();

    ListaPrioridad* queue = new ListaPrioridad(); //Lista abierta
    bool visited[SIZE][SIZE]; //Lista cerrada
    Celda * inicio = new Celda(xi, yi,nullptr);
    inicio->g = 0;
    inicio->h = heuristica(xi,yi,xd,yd);
    queue->queue(inicio);

    Celda* fin = nullptr;

    while (queue->inicio!=nullptr)
    {
        Celda* node = queue->dequeue();
        visited[node->y][node->x] = true;

        if (node->y == yd && node->x == xd)
        {
            fin = node;
            break;
        }

        int index = coordToIndexx(node->x,node->y);

        for (int i = 0; i < GRAPHSIZE; i++)
        {
            if (mapa->matrizAdyacencia[index][i] != 0 && !visited[int(i/SIZE)][i%SIZE])
            {
                int auxX = i%SIZE;
                int auxY = int(i/SIZE);



                Celda* vecino = new Celda(auxX,auxY,node);

                vecino->g = node->g + mapa->matrizAdyacencia[index][i];
                vecino->h = heuristica(auxX,auxY,xd,yd);

                Celda* aux = queue->buscar(auxX,auxY);

                if (aux!=nullptr)
                {
                    if (aux->g > vecino->g && aux->h > vecino->h )
                    {
                        queue->eliminar(auxX,auxY);
                        queue->queue(vecino);
                    }
                }
                else
                {
                    queue->queue(vecino);
                }
            }
        }




    }
    while (fin != nullptr)
    {
        ruta->add(new Nodo(fin->x, fin->y));
        fin = fin->padre;
    }

    return ruta;

}
