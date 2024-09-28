//
// Created by jeremy on 21/09/24.
//

#include "Mapa.h"
#include "../Pathfinding/Dijkstra.h"
#include <iostream>
#include <ostream>

#include "../Objetos/Indestructible.h"
#include "../Objetos/Suelo.h"
#include "../Objetos/Tanque.h"


/**
 * @brief Calcula la ruta más corta desde un nodo origen usando Dijkstra.
 * @param origen Nodo de origen desde el cual se calculará la ruta.
 */
void Mapa::probarDijkstra(int origen) {
    std::cout << "Probando Dijkstra desde el nodo origen " << origen << "..." << std::endl;
    Dijkstra::shortestPath(matrizAdyacencia, GRAPHSIZE, origen);
}
/**
 * Inicia y calcula las distancias de la matriz de adyacencia
 */
void Mapa::inicializaMatrizAdyacencia()
{
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            int nodoActual = coordenadaANodo(j, i);
            if (i > 0)
            {
                matrizAdyacencia[nodoActual][coordenadaANodo(j, i - 1)] = DESP_VERT_HORI; //Desplazamiento vertical
                if (j > 0)
                {
                    matrizAdyacencia[nodoActual][coordenadaANodo(j - 1, i - 1)] = DESP_DIAGO; //Desplazamiento diagonal
                }
                if (j < SIZE - 1)
                {
                    matrizAdyacencia[nodoActual][coordenadaANodo(j + 1, i - 1)] = DESP_DIAGO; //Desplazamiento diagonal
                }
            }
            if (j > 0)
            {
                matrizAdyacencia[nodoActual][coordenadaANodo(j - 1, i)] = DESP_VERT_HORI; //Desplazamiento horizontal
            }
            if (j < SIZE - 1)
            {
                matrizAdyacencia[nodoActual][coordenadaANodo(j + 1, i)] = DESP_VERT_HORI; //Desplazamiento horizontal
            }
            if (i < SIZE - 1)
            {
                matrizAdyacencia[nodoActual][coordenadaANodo(j, i + 1)] = DESP_VERT_HORI; //Desplazamiento vertical
                if (j > 0)
                {
                    matrizAdyacencia[nodoActual][coordenadaANodo(j - 1, i + 1)] = DESP_DIAGO; //Desplazamiento diagonal
                }
                if (j < SIZE - 1)
                {
                    matrizAdyacencia[nodoActual][coordenadaANodo(j + 1, i + 1)] = DESP_DIAGO; //Desplazamiento diagonal
                }
            }
        }
    }
}

/**
 * Transforma de una coordenada a el nodo donde esta almacenada
 * @param x coordenada X
 * @param y coordenada Y
 * @return numero de nodo de la coordenada dada.
 */
int Mapa::coordenadaANodo(int x, int y)
{
    return x * SIZE + y;
}

/**
 * Carga el mapa de manera aleatoria
 */
void Mapa::cargaMapaAleatorio()
{
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            if (i == 0 || i == SIZE - 1 || j == 0 || j == SIZE - 1)
            {
                matrizMapa[i][j] = new Indestructible();
            }
            else
            {
                matrizMapa[i][j] = new Suelo();
            }
        }
    }
    matrizMapa[1][1] = new Tanque();
    matrizMapa[SIZE - 2][SIZE - 2] = new Tanque();
}

void Mapa::printMapa()
{
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            std::cout << matrizMapa[i][j]->recurso();
        }
        std::cout << std::endl;
    }
}

/**
 * Constructor de mapa
 */
Mapa::Mapa()
{
    inicializaMatrizAdyacencia();
    cargaMapaAleatorio();
    printMapa();
    std::cout << "Inicializando matriz adyacencia" << std::endl;
}
