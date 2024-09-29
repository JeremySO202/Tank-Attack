// Created by mvasquezr on 9/28/24.
#include "Dijkstra.h"
#include <limits.h>
#include <iostream>

#define INF 0x3f3f3f3f

// Función auxiliar para encontrar el nodo con la menor distancia
int minDistance(int dist[], bool sptSet[], int numVertices) {
    int min = INF, min_index;

    for (int v = 0; v < numVertices; v++) {
        if (!sptSet[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

/**
 * @brief Calcula la ruta más corta desde un nodo fuente a un nodo destino.
 * @param matrizAdyacencia Matriz de adyacencia del grafo.
 * @param numVertices Número de nodos del grafo.
 * @param src Nodo de origen.
 * @param destino Nodo de destino.
 * @param mapa Puntero al objeto Mapa
 * @return Ruta desde el nodo origen hasta el nodo destino.
 */
Ruta* Dijkstra::shortestPath(int matrizAdyacencia[GRAPHSIZE][GRAPHSIZE], int numVertices, int src, int destino, Mapa* mapa) {
    int dist[GRAPHSIZE];
    bool sptSet[GRAPHSIZE] = {false};
    Nodo* prev[GRAPHSIZE] = {nullptr};

    // Inicializar todas las distancias como INFINITO y sptSet como falso
    for (int i = 0; i < numVertices; i++) {
        dist[i] = INF;
        sptSet[i] = false;
    }

    // La distancia del nodo fuente a sí mismo siempre es 0
    dist[src] = 0;

    for (int count = 0; count < numVertices - 1; count++) {
        int u = minDistance(dist, sptSet, numVertices);


        sptSet[u] = true;


        for (int v = 0; v < numVertices; v++) {
            if (!sptSet[v] && matrizAdyacencia[u][v] != 0 && dist[u] != INF &&
                dist[u] + matrizAdyacencia[u][v] < dist[v]) {
                dist[v] = dist[u] + matrizAdyacencia[u][v];
                prev[v] = new Nodo(u % SIZE, u / SIZE, prev[u]);
            }
        }
    }


    Ruta* ruta = new Ruta();
    int current = destino;

    while (current != src && prev[current] != nullptr) {
        ruta->add(new Nodo(current % SIZE, current / SIZE));
        current = mapa->coordenadaANodo(prev[current]->x, prev[current]->y);
    }

    ruta->add(new Nodo(src % SIZE, src / SIZE));

    std::cout << "Ruta más corta:" << std::endl;
    Nodo* temp = ruta->inicio;
    while (temp != nullptr) {
        temp = temp->next;
    }

    return ruta;
}
