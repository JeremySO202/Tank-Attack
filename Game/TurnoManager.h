//
// Created by mvasquezr on 10/7/24.
//

#ifndef TURNOMANAGER_H
#define TURNOMANAGER_H

#include <QObject>
#include <QTimer>
#include "Jugador.h"

class TurnoManager : public QObject {
    Q_OBJECT

private:
    Jugador* jugadores[2]; // Referencia a los dos jugadores
    int jugadorActual; // Índice del jugador actual (0 o 1)
    QTimer* timer; // Timer para el tiempo del turno
    const int tiempoMaximo = 300000; // Tiempo total de juego (5 minutos)
    const int tiempoPorTurno = 30000; // 30 segundos por turno

public:
    explicit TurnoManager(Jugador* jugador1, Jugador* jugador2, QObject* parent = nullptr);
    void iniciarTurno();
    void siguienteTurno();
    Jugador* getJugadorActual() const;

    signals:
        void turnoTerminado();
    void juegoTerminado();

    private slots:
        void onTurnoTerminado();
};

#endif // TURNOMANAGER_H
