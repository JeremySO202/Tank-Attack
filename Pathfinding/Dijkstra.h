//
// Created by mvasquezr on 9/28/24.
//
#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include "../Mapa/Mapa.h"
#include "../Pathfinding/Ruta.h"

/**
 * @class Dijkstra
 * @brief Implementa el algoritmo de Dijkstra para rutas más cortas.
 */
class Dijkstra {
public:
    /**
     * @brief Calcula la ruta más corta desde un nodo fuente hasta un destino.
     * @param matrizAdyacencia Matriz de adyacencia del grafo.
     * @param numVertices Número de nodos del grafo.
     * @param src Nodo de origen.
     * @param destino Nodo de destino.
     */
    static Ruta* shortestPath(int matrizAdyacencia[GRAPHSIZE][GRAPHSIZE], int numVertices, int src, int destino, Mapa* mapa);
};

#endif // DIJKSTRA_H
