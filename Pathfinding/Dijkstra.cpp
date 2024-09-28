//
// Created by mvasquezr on 9/28/24.
//

#include "Dijkstra.h"
#include <limits.h>
#include <iostream>

#define INF 0x3f3f3f3f

// Función auxiliar para encontrar el nodo con la menor distancia
int minDistance(int dist[], bool sptSet[], int numVertices)
{
    int min = INF, min_index;

    for (int v = 0; v < numVertices; v++)
        if (!sptSet[v] && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

/**
 * @brief Calcula la ruta más corta desde un nodo fuente.
 * @param matrizAdyacencia Matriz de adyacencia del grafo.
 * @param numVertices Número de nodos del grafo.
 * @param src Nodo de origen.
 */
void Dijkstra::shortestPath(int matrizAdyacencia[GRAPHSIZE][GRAPHSIZE], int numVertices, int src) {
    int dist[GRAPHSIZE]; // Distancia más corta desde la fuente a cada nodo
    bool sptSet[GRAPHSIZE] = {false}; // Conjunto de nodos ya procesados

    // Inicializar todas las distancias como INFINITO y sptSet como falso
    for (int i = 0; i < numVertices; i++) {
        dist[i] = INF;
        sptSet[i] = false;
    }

    // La distancia del nodo fuente a sí mismo siempre es 0
    dist[src] = 0;

    // Encuentra la ruta más corta para todos los nodos
    for (int count = 0; count < numVertices - 1; count++) {
        // Selecciona el nodo con la distancia mínima del conjunto de nodos no procesados
        int u = minDistance(dist, sptSet, numVertices);

        // Marca el nodo como procesado
        sptSet[u] = true;

        // Actualiza la distancia de los nodos adyacentes al nodo seleccionado
        for (int v = 0; v < numVertices; v++) {
            // Actualiza dist[v] si no está en sptSet, si hay un borde de u a v,
            // si la distancia a u no es INFINITO, y si el nuevo camino es más corto
            if (!sptSet[v] && matrizAdyacencia[u][v] && dist[u] != INF
                && dist[u] + matrizAdyacencia[u][v] < dist[v]) {
                dist[v] = dist[u] + matrizAdyacencia[u][v];
            }
        }
    }

    // Imprimir las distancias más cortas desde el nodo fuente
    std::cout << "Distancia desde el nodo fuente:" << std::endl;
    for (int i = 0; i < numVertices; i++) {
        std::cout << "Nodo " << i << " \t Distancia: " << dist[i] << std::endl;
    }
}
