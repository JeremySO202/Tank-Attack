//
// Created by mvasquezr on 10/4/24.
//

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H


#include "../Mapa/Mapa.h"
#include "Jugador.h"

#define MAX_JUGADORES 2

class GameController;

class GameManager {
private:
    Mapa* mapa;
    Jugador* jugadores[MAX_JUGADORES];
    int numJugadores;
    int jugadorActual; // Índice del jugador actual
    GameController* gameController;

public:
    GameManager(Mapa* mapa, GameController* controller);
    void agregarJugador(Jugador* jugador);
    Jugador* getJugadorActual(); // Obtener el jugador actual
    void actualizarTanques();
    int obtenerGanador();
    void cambiarTurno(); // Cambiar de turno
    void seleccionarTanque(int x, int y);
    void setDestino(int x, int y);
    void usarPowerUp();
    bool puedeUsarPowerUp() const;
};

#endif // GAMEMANAGER_H
