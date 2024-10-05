//
// Created by mvasquezr on 10/4/24.
//
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "../Mapa/Mapa.h"
#include "../Game/Jugador.h"

#define MAX_JUGADORES 4

class GameManager {
private:
    Mapa* mapa;
    Jugador* jugadores[MAX_JUGADORES];
    int numJugadores;

public:
    GameManager(Mapa* mapa);
    void agregarJugador(Jugador* jugador);
    void seleccionarTanque(int jugadorId, int x, int y);
    void setDestino(int jugadorId, int x, int y);
};

#endif // GAMEMANAGER_H
