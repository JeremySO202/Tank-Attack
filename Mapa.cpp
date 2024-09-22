//
// Created by jeremy on 21/09/24.
//

#include "Mapa.h"

#include <iostream>
#include <ostream>

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
 * Constructor de mapa
 */
Mapa::Mapa()
{
    inicializaMatrizAdyacencia();
    std::cout << "Inicializando matriz adyacencia" << std::endl;
}


