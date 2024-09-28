//
// Created by jeremy on 28/09/24.
//

#include "Ruta.h"


/**
 * Metodo constructor de nodo
 * @param _x
 * @param _y
 * @param _p
 */
Nodo::Nodo(int _x, int _y, Nodo *_p)
{
    x = _x;
    y = _y;
    next = nullptr;
    padre = _p;
}

/**
 * Metodo constructor de nodo
 * @param _x
 * @param _y
 */
Nodo::Nodo(int _x, int _y)
{
    x = _x;
    y = _y;
    next = nullptr;
    padre = nullptr;
}

/**
 * Metodo constructor de ruta
 */
Ruta::Ruta()
{
    inicio = nullptr;
    final = nullptr;
}

/**
 * Ingresa un nodo al final de la cola
 * @param nodo
 */
void Ruta::queue(Nodo* nodo)
{
    if (inicio == nullptr)
    {
        inicio = nodo;
        final = nodo;
    }
    else
    {
        final->next = nodo;
        final = nodo;
    }

}

/**
 * Ingresa un nodo al final de la cola
 * @param nodo
 */
void Ruta::add(Nodo* nodo)
{
    if (inicio == nullptr)
    {
        inicio = nodo;
        final = nodo;
    }
    else
    {
        nodo->next = inicio;
        inicio = nodo;
    }
}

/**
 * Elimina el primer nodo de la lista
 * @return primer nodo de la lista
 */
Nodo* Ruta::dequeue()
{
    if (inicio == nullptr)
    {
        return nullptr;
    }
    if(inicio == final)
    {
        Nodo* temp = inicio;
        inicio = nullptr;
        final = nullptr;
        return temp;
    }
    Nodo * aux = inicio;
    inicio = inicio->next;
    return aux;
}
