//
// Created by mvasquezr on 10/7/24.
//
#include "TurnoManager.h"

#include <iostream>

/**
 * Constructor de TurnoManager.
 * Inicializa los jugadores y el índice del jugador actual.
 */
TurnoManager::TurnoManager(Jugador* jugador1, Jugador* jugador2, QObject* parent)
    : QObject(parent), jugadorActual(0) {
    jugadores[0] = jugador1;
    jugadores[1] = jugador2;

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &TurnoManager::onTurnoTerminado);
}

/**
 * Inicia el turno del jugador actual.
 */
void TurnoManager::iniciarTurno() {
    timer->start(tiempoPorTurno);
    std::cout << "Turno del jugador " << jugadorActual + 1 << std::endl;
}

/**
 * Pasa al siguiente turno.
 */
void TurnoManager::siguienteTurno() {
    jugadorActual = (jugadorActual + 1) % 2;
    iniciarTurno();
}

/**
 * Obtiene el jugador actual.
 */
Jugador* TurnoManager::getJugadorActual() const {
    return jugadores[jugadorActual];
}

/**
 * Slot que se ejecuta cuando el tiempo del turno termina.
 */
void TurnoManager::onTurnoTerminado() {
    std::cout << "Turno terminado para el jugador " << jugadorActual + 1 << std::endl;
    siguienteTurno();
}
