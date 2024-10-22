//
// Created by mvasquezr on 10/4/24.
//

#ifndef JUGADOR_H
#define JUGADOR_H

#include <queue>
#include "PowerUp.h"
#include "../Objetos/Tanque.h"

const int MAX_TANQUES = 4;
const int MAX_POWERUPS = 10;

class Jugador {
private:
    int id;
    int numTanques;
    Tanque* tanqueSeleccionado;
    PowerUp* powerUpList[MAX_POWERUPS];
    int powerUpCount;
    bool precisionMovimiento = false;
    bool precisionAtaque = false;
    bool poderAtaque = false;

public:
    Tanque* tanques[MAX_TANQUES];
    int numTurnosExtra = 0;

    Jugador(int id, bool usaMouse);

    void agregarTanque(Tanque* tanque);
    void seleccionarTanque(int x, int y);
    void setDestino(int x, int y);
    void setDisparo(int x, int y);
    Tanque* getTanqueSeleccionado() const;
    int getCantidadTanques();
    int getTanquesVivos();
    void setNumTanques(int n);
    int getId() const;
    void limpiarSeleccion();

    void agregarPowerUp(PowerUp* powerUp);
    void usarPowerUp();
    bool tienePowerUps() const;
    PowerUp* const* getPowerUps(int& count) const;
    void aplicarPowerUp();

    void setPrecisionMovimiento(bool valor);
    void setPrecisionAtaque(bool valor);
    void setPoderAtaque(bool valor);
    void setNumTurnosExtra(int turnos);
    bool getPrecisionMovimiento() const;
    bool getPrecisionAtaque() const;
    bool getPoderAtaque() const;
};

#endif // JUGADOR_H
