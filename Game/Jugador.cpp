//
// Created by mvasquezr on 10/4/24.
//

#include "Jugador.h"
#include <iostream>

/**
 * Constructor de Jugador.
 * @param id Identificador del jugador.
 * @param usaMouse Indica si usa mouse.
 */
Jugador::Jugador(int id, bool usaMouse)
    : id(id), tanqueSeleccionado(nullptr), numTanques(0) {}

/**
 * Agrega un tanque al jugador.
 * @param tanque Puntero al tanque.
 */
void Jugador::agregarTanque(Tanque* tanque) {
    if (numTanques < MAX_TANQUES) {
        tanques[numTanques++] = tanque;
    }
}

/**
 * Selecciona un tanque en la posición dada.
 * @param x Coordenada x.
 * @param y Coordenada y.
 */
void Jugador::seleccionarTanque(int x, int y) {
    for (int i = 0; i < numTanques; ++i) {
        if (tanques[i]->getX() == x && tanques[i]->getY() == y) {
            tanqueSeleccionado = tanques[i];
            std::cout << "Tanque seleccionado en (" << x << ", " << y << ")" << std::endl;
            return;
        }
    }
    std::cout << "No hay tanque en la posición seleccionada." << std::endl;
}

/**
 * Establece el destino del tanque seleccionado.
 * @param x Coordenada x del destino.
 * @param y Coordenada y del destino.
 */
void Jugador::setDestino(int x, int y) {
    if (!tanqueSeleccionado) {
        std::cout << "No hay un tanque seleccionado." << std::endl;
        return;
    }
    std::cout << "Destino establecido en (" << x << ", " << y << ")" << std::endl;
}

/**
 * Obtiene el tanque seleccionado.
 * @return Puntero al tanque seleccionado.
 */
Tanque* Jugador::getTanqueSeleccionado() const {
    return tanqueSeleccionado;
}

/**
 * Obtiene el ID del jugador.
 * @return ID del jugador.
 */
int Jugador::getId() const {
    return id;
}

/**
 * Limpia la selección del tanque.
 */
void Jugador::limpiarSeleccion() {
    tanqueSeleccionado = nullptr;
}
