//
// Created by mvasquezr on 10/4/24.
//

#include "GameManager.h"
#include <iostream>

/**
 * Constructor de GameManager.
 * Inicializa con el mapa proporcionado.
 * @param mapa Puntero al objeto Mapa.
 */
GameManager::GameManager(Mapa* mapa) : mapa(mapa), numJugadores(0), jugadorActual(0) {}

/**
 * Agrega un jugador al juego.
 * @param jugador Puntero al jugador.
 */
void GameManager::agregarJugador(Jugador* jugador) {
    if (numJugadores < MAX_JUGADORES) {
        jugadores[numJugadores++] = jugador;
    }
}

/**
 * Obtiene el jugador actual.
 * @return Puntero al jugador actual.
 */
Jugador* GameManager::getJugadorActual() {
    return jugadores[jugadorActual];
}

/**
 * Cambia el turno al siguiente jugador.
 */
void GameManager::cambiarTurno() {
    jugadorActual = (jugadorActual + 1) % numJugadores;
    std::cout << "Es el turno del jugador: " << (jugadorActual + 1) << std::endl;
}

/**
 * Selecciona un tanque del jugador actual.
 * @param x Coordenada x del tanque.
 * @param y Coordenada y del tanque.
 */
void GameManager::seleccionarTanque(int x, int y) {
    jugadores[jugadorActual]->seleccionarTanque(x, y);
}

/**
 * Establece un destino para un tanque del jugador actual.
 * @param x Coordenada x del destino.
 * @param y Coordenada y del destino.
 */
void GameManager::setDestino(int x, int y) {
    jugadores[jugadorActual]->setDestino(x, y);
}
