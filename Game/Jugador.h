//
// Created by mvasquezr on 10/4/24.
//

#ifndef JUGADOR_H
#define JUGADOR_H

#include "../Objetos/Tanque.h"

const int MAX_TANQUES = 2;

class Jugador {
private:
    int id;
    Tanque* tanques[MAX_TANQUES];
    int numTanques;
    Tanque* tanqueSeleccionado;

public:
    Jugador(int id, bool usaMouse);

    void agregarTanque(Tanque* tanque);
    void seleccionarTanque(int x, int y);
    void setDestino(int x, int y);
    void setDisparo(int x, int y);
    Tanque* getTanqueSeleccionado() const;
    int getId() const;
    void limpiarSeleccion();
};

#endif // JUGADOR_H
