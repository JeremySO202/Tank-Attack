//
// Created by mvasquezr on 10/4/24.
//

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "../Mapa/Mapa.h"
#include "Jugador.h"

#define MAX_JUGADORES 2

class GameManager {
private:
    Mapa* mapa;
    Jugador* jugadores[MAX_JUGADORES];
    int numJugadores;
    int jugadorActual; // Índice del jugador actual

public:
    GameManager(Mapa* mapa);
    void agregarJugador(Jugador* jugador);
    Jugador* getJugadorActual(); // Obtener el jugador actual
    void cambiarTurno(); // Cambiar de turno
    void seleccionarTanque(int x, int y);
    void setDestino(int x, int y);
};

#endif // GAMEMANAGER_H
