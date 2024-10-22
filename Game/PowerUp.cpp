//
// Created by mvasquezr on 10/21/24.
//

#include "PowerUp.h"
#include "Jugador.h"

#include <iostream>
/**
 * Devuelve el nombre del tipo de power-up como string.
 * @return Nombre del tipo de power-up.
 */
std::string PowerUp::getTipoString() const {
    switch (tipo) {
        case DOBLE_TURNO:
            return "Doble Turno";
        case PRECISION_MOVIMIENTO:
            return "Precisión Movimiento";
        case PRECISION_ATAQUE:
            return "Precisión Ataque";
        case PODER_ATAQUE:
            return "Poder Ataque";
        default:
            return "Desconocido";
    }
}
/**
 * Aplica el power-up Doble Turno al jugador.
 */
void DobleTurno::aplicar(Jugador* jugador) {
    std::cout << "Aplicando Power-Up: Doble Turno" << std::endl;
    jugador->setNumTurnosExtra(2); // El jugador tiene dos turnos adicionales
}

/**
 * Aplica el power-up Precisión de Movimiento al jugador.
 */
void PrecisionMovimiento::aplicar(Jugador* jugador) {
    std::cout << "Aplicando Power-Up: Precisión de Movimiento" << std::endl;
    jugador->setPrecisionMovimiento(true);
}

/**
 * Aplica el power-up Precisión de Ataque al jugador.
 */
void PrecisionAtaque::aplicar(Jugador* jugador) {
    std::cout << "Aplicando Power-Up: Precisión de Ataque" << std::endl;
    jugador->setPrecisionAtaque(true);
}

/**
 * Aplica el power-up Poder de Ataque al jugador.
 */
void PoderAtaque::aplicar(Jugador* jugador) {
    std::cout << "Aplicando Power-Up: Poder de Ataque" << std::endl;
    jugador->setPoderAtaque(true);
}
