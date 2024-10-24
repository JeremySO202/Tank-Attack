//
// Created by mvasquezr on 10/4/24.
//

#include "GameManager.h"
#include <iostream>

#include "GameController.h"
#include "../Objetos/Suelo.h"

/**
 * Constructor de GameManager.
 * Inicializa con el mapa proporcionado.
 * @param mapa Puntero al objeto Mapa.
 */
GameManager::GameManager(Mapa* mapa, GameController* controller) : mapa(mapa), numJugadores(0), jugadorActual(0), gameController(controller){}

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
 * Elimina los tanques que no tengan vida
 */
void GameManager::actualizarTanques()
{
    for (int i = 0; i < numJugadores; i++)
    {
        Jugador* jugador = jugadores[i];

        for (int j = 0; j < jugador->getCantidadTanques(); j++)
        {
            if (jugador->tanques[j]->getVida()==0)
            {
                mapa->matrizMapa[jugador->tanques[j]->getY()][jugador->tanques[j]->getX()] = new Suelo();
            }
        }
    }

}

int GameManager::obtenerGanador(){
    int min = jugadores[0]->getTanquesVivos();
    int minIndice = 0;
    for (int i = 1; i < numJugadores; i++)
    {
        if (jugadores[i]->getTanquesVivos() < min)
        {
            min = jugadores[i]->getTanquesVivos();
            minIndice = i;
        }
    }
    return minIndice;
}


/**
 * Cambia el turno al siguiente jugador y genera un power-up.
 */

void GameManager::cambiarTurno() {
    if (jugadores[jugadorActual]->numTurnosExtra > 0) {
        jugadores[jugadorActual]->numTurnosExtra--;
        std::cout << "Turno extra para el jugador " << (jugadorActual + 1) << std::endl;
        return; // El jugador actual sigue jugando
    }

    jugadorActual = (jugadorActual + 1) % numJugadores;

    if (jugadores[jugadorActual]->getProximoTurnoDoble()) {
        jugadores[jugadorActual]->setNumTurnosExtra(1);
        jugadores[jugadorActual]->setProximoTurnoDoble(false);
        std::cout << "El jugador " << (jugadorActual + 2) << " ha activado el Doble Turno para esta ronda." << std::endl;
    }

    std::cout << "Es el turno del jugador: " << (jugadorActual + 1) << std::endl;

    gameController->generarPowerUpAleatorio(jugadores[jugadorActual]);
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
/**
 * Aplica un power-up si el jugador actual tiene alguno.
 */
void GameManager::usarPowerUp() {
    if (puedeUsarPowerUp()) {
        jugadores[jugadorActual]->aplicarPowerUp();
    }
}

/**
 * Verifica si el jugador actual tiene power-ups disponibles.
 * @return true si tiene power-ups, false de lo contrario.
 */
bool GameManager::puedeUsarPowerUp() const {
    return jugadores[jugadorActual]->tienePowerUps();
}