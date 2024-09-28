//
// Created by mvasquezr on 9/28/24.
//
#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include "../Mapa/Mapa.h"

/**
 * @class Dijkstra
 * @brief Implementa el algoritmo de Dijkstra para rutas más cortas.
 */
class Dijkstra {
public:
    /**
     * @brief Calcula la ruta más corta desde un nodo fuente.
     * @param matrizAdyacencia Matriz de adyacencia del grafo.
     * @param numVertices Número de nodos del grafo.
     * @param src Nodo de origen.
     */
    static void shortestPath(int matrizAdyacencia[GRAPHSIZE][GRAPHSIZE], int numVertices, int src);
};

#endif // DIJKSTRA_H
