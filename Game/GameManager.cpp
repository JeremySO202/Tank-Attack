//
// Created by mvasquezr on 10/4/24.
//
#include "GameManager.h"

/**
 * Constructor de GameManager.
 * Inicializa con el mapa proporcionado.
 * @param mapa Puntero al objeto Mapa.
 */
GameManager::GameManager(Mapa* mapa) : mapa(mapa), numJugadores(0) {}

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
 * Selecciona un tanque del jugador.
 * @param jugadorId ID del jugador.
 * @param x Coordenada x del tanque.
 * @param y Coordenada y del tanque.
 */
void GameManager::seleccionarTanque(int jugadorId, int x, int y) {
    for (int i = 0; i < numJugadores; ++i) {
        if (jugadores[i]->getId() == jugadorId) {
            jugadores[i]->seleccionarTanque(x, y);
            break;
        }
    }
}

/**
 * Establece un destino para un tanque.
 * @param jugadorId ID del jugador.
 * @param x Coordenada x del destino.
 * @param y Coordenada y del destino.
 */
void GameManager::setDestino(int jugadorId, int x, int y) {
    for (int i = 0; i < numJugadores; ++i) {
        if (jugadores[i]->getId() == jugadorId) {
            jugadores[i]->setDestino(x, y);
            break;
        }
    }
}
