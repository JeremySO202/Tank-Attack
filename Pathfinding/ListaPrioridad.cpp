//
// Created by jeremy on 4/10/24.
//

#include "ListaPrioridad.h"


ListaPrioridad::ListaPrioridad()
{
    inicio = nullptr;
    final = nullptr;
}

/**
 * Ingresa una celda segun la prioridad
 * @param celda celda a ingresar
 */
void ListaPrioridad::queue(Celda *celda) {
    if (inicio == nullptr) {
        inicio = celda;
        final = celda;
        return;
    }

    if (celda->fCost() < inicio->fCost()) {
        celda->next = inicio;
        inicio = celda;
        return;
    }

    Celda* actual = inicio;
    while (actual->next != nullptr && actual->next->fCost() <= celda->fCost()) {
        actual = actual->next;
    }

    celda->next = actual->next;
    actual->next = celda;

    if (celda->next == nullptr) {
        final = celda;
    }
}
/**
 * Elimina el primer nodo de la lista
 * @return primer nodo de la lista
 */
Celda* ListaPrioridad::dequeue()
{
    if (inicio == nullptr)
    {
        return nullptr;
    }
    if(inicio == final)
    {
        Celda* temp = inicio;
        inicio = nullptr;
        final = nullptr;
        return temp;
    }
    Celda * aux = inicio;
    inicio = inicio->next;
    return aux;
}
/**
 * Busca una celda en la lista con las coordenadas especificadas
 * @param x coordenada x
 * @param y coordenada y
 * @return puntero a la celda si la encuentra, nullptr si no
 */
Celda* ListaPrioridad::buscar(int x, int y) {
    Celda* actual = inicio;
    while (actual != nullptr) {
        if (actual->x == x && actual->y == y) {
            return actual;
        }
        actual = actual->next;
    }
    return nullptr;
}

/**
 * Elimina una celda con las coordenadas especificadas
 * @param x coordenada x
 * @param y coordenada y
 * @return true si la celda fue eliminada, false si no se encontró
 */
void ListaPrioridad::eliminar(int x, int y) {
    if (inicio == nullptr) {
        return;
    }

    if (inicio->x == x && inicio->y == y) {
        Celda* temp = inicio;
        inicio = inicio->next;
        if (inicio == nullptr) {
            final = nullptr;
        }
        delete temp;
        return;
    }

    Celda* actual = inicio;
    while (actual->next != nullptr) {
        if (actual->next->x == x && actual->next->y == y) {
            Celda* temp = actual->next;
            actual->next = temp->next;
            if (temp == final) {
                final = actual;
            }
            delete temp;
            return;
        }
        actual = actual->next;
    }
}




