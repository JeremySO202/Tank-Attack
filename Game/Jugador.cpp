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
    : id(id), tanqueSeleccionado(nullptr), numTanques(0), powerUpCount(0) {}

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

void Jugador::setDisparo(int x, int y)
{
    if (!tanqueSeleccionado) {
        std::cout << "No hay un tanque seleccionado." << std::endl;
        return;
    }
    std::cout << "Disparo establecido en (" << x << ", " << y << ")" << std::endl;
}

/**
 * Obtiene el tanque seleccionado.
 * @return Puntero al tanque seleccionado.
 */
Tanque* Jugador::getTanqueSeleccionado() const {
    return tanqueSeleccionado;
}

int Jugador::getCantidadTanques()
{
    return numTanques;
}

int Jugador::getTanquesVivos()
{
    int cant = 0;
    for (int i = 0; i < numTanques; ++i)
    {
        if (tanques[i]->getVida()>0)
        {
            cant++;
        }

    }
    return cant;
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

void Jugador::agregarPowerUp(PowerUp* powerUp) {
    if (powerUpCount < MAX_POWERUPS) {
        powerUpList[powerUpCount++] = powerUp;
        std::cout << "Power-Up añadido: " << powerUp->getTipoString() << std::endl;
    } else {
        std::cout << "No se puede agregar más power-ups. Límite alcanzado." << std::endl;
    }
}

bool Jugador::tienePowerUps() const {
    return powerUpCount > 0;
}

PowerUp* const* Jugador::getPowerUps(int& count) const {
    count = powerUpCount;
    return powerUpList;
}

void Jugador::setPrecisionMovimiento(bool valor) {
    precisionMovimiento = valor;
}

void Jugador::setPrecisionAtaque(bool valor) {
    precisionAtaque = valor;
}

void Jugador::setPoderAtaque(bool valor) {
    poderAtaque = valor;
}

void Jugador::setNumTurnosExtra(int turnos) {
    numTurnosExtra = turnos;
}

bool Jugador::getPrecisionMovimiento() const {
    return precisionMovimiento;
}

bool Jugador::getPrecisionAtaque() const {
    return precisionAtaque;
}

void Jugador::aplicarPowerUp() {
    if (powerUpCount > 0) {
        PowerUp* powerUp = powerUpList[0]; // Aplicar el primer power-up de la lista
        powerUp->aplicar(this); // Aplicar los efectos del power-up
        std::cout << "Power-up aplicado: " << powerUp->getTipoString() << std::endl;

        // Eliminar el power-up utilizado de la lista y reordenar
        for (int i = 1; i < powerUpCount; ++i) {
            powerUpList[i - 1] = powerUpList[i];
        }
        powerUpList[powerUpCount - 1] = nullptr;
        powerUpCount--;
    } else {
        std::cout << "No hay power-ups para aplicar." << std::endl;
    }
}
