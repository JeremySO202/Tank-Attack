//
// Created by jeremy on 21/09/24.
//

#include "Mapa.h"
#include "../Pathfinding/Dijkstra.h"
#include <iostream>
#include <ostream>
#include <typeinfo>

#include "../Objetos/Indestructible.h"
#include "../Objetos/Suelo.h"
#include "../Objetos/Tanque.h"


/**
 * Comprueba que una coordenada sea navegable, es decir, que se pueda pasar sobre ella
 * @param x eje x
 * @param y eje y
 * @return true si es navegable, false si no
 */
bool Mapa::isValid(int x, int y)
{
    if (x >= 0 && y >= 0 && x<SIZE && y<SIZE)
        return typeid(*matrizMapa[y][x]) != typeid(Indestructible);
    return x >= 0 && y >= 0 && x<SIZE && y<SIZE;
}

/**
 * Inicia y calcula las distancias de la matriz de adyacencia
 */
void Mapa::inicializaMatrizAdyacencia()
{
    int dirY[] = {-1,-1,-1,0,0,1,1,1};
    int dirX[] = {-1,0,1,-1,1,-1,0,1};
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            for (int d = 0; d < 8; ++d)
            {
                if (isValid(j,i))
                {
                    int newX = j + dirX[d];
                    int newy = i + dirY[d];
                    if (isValid(newX, newy))
                    {
                        if (d == 0 || d== 2 || d == 5 || d == 7)
                            matrizAdyacencia[coordenadaANodo(j,i)][coordenadaANodo(newX, newy)] = DESP_DIAGO; //Desplazamiento diagonal
                        else
                            matrizAdyacencia[coordenadaANodo(j,i)][coordenadaANodo(newX, newy)] = DESP_VERT_HORI;
                    }
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
    return y * SIZE + x;
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
    // Línea 1
    matrizMapa[1][1] = new Tanque();            // T
    matrizMapa[1][2] = new Indestructible();    // S

    // Línea 2
    matrizMapa[2][2] = new Indestructible();    // S
    matrizMapa[2][4] = new Indestructible();    // S

    // Línea 3

    matrizMapa[3][4] = new Indestructible();    // S

    // Línea 4
    matrizMapa[4][1] = new Indestructible();    // S
    matrizMapa[4][2] = new Indestructible();    // S
    matrizMapa[4][3] = new Indestructible();    // S
    matrizMapa[4][4] = new Indestructible();    // S

    // Línea 6
    matrizMapa[6][3] = new Indestructible();    // #
    matrizMapa[6][4] = new Indestructible();    // #
    matrizMapa[6][5] = new Indestructible();    // #
    matrizMapa[6][6] = new Indestructible();    // #
    matrizMapa[6][7] = new Indestructible();    // #

    matrizMapa[7][3] = new Indestructible();    // #
    matrizMapa[7][4] = new Indestructible();    // #
    matrizMapa[7][5] = new Indestructible();    // #
    matrizMapa[7][6] = new Indestructible();    // #
    matrizMapa[7][7] = new Indestructible();    // #

    matrizMapa[8][1] = new Indestructible();    // #
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
    cargaMapaAleatorio();
    inicializaMatrizAdyacencia();
    printMapa();
    std::cout << "Inicializando matriz adyacencia" << std::endl;
}

/**
 * Mueve un tanque siguiendo un ruta
 * @param ruta ruta a seguir
 */
void Mapa::moverTanque(Ruta* ruta) {
    if (ruta->inicio == nullptr) {
        std::cout << "Ruta vacía, no se puede mover el tanque" << std::endl;
        return;
    }

    Nodo* nodoActual = ruta->inicio;
    if (typeid(*matrizMapa[nodoActual->y][nodoActual->x]) != typeid(Tanque)) {
        std::cout << "No hay un tanque en la posición inicial de la ruta" << std::endl;
        return;
    }
    Nodo* nodoAnterior = nodoActual;
    nodoActual = nodoActual->next;

    while (nodoActual != nullptr) {
        matrizMapa[nodoActual->y][nodoActual->x] = matrizMapa[nodoAnterior->y][nodoAnterior->x];
        matrizMapa[nodoAnterior->y][nodoAnterior->x] = new Suelo();
        printMapa();
        std::cout << "Moviendo tanque a: (" << nodoActual->x << ", " << nodoActual->y << ")" << std::endl;
        nodoAnterior = nodoActual;
        nodoActual = nodoActual->next;
    }
}


