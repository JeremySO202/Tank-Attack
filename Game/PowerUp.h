//
// Created by mvasquezr on 10/21/24.
//

#ifndef POWERUP_H
#define POWERUP_H
#include <string>

class Jugador;

class PowerUp {
public:
    enum Tipo { DOBLE_TURNO, PRECISION_MOVIMIENTO, PRECISION_ATAQUE, PODER_ATAQUE };
    Tipo tipo;

    PowerUp(Tipo tipo) : tipo(tipo) {}
    virtual void aplicar(Jugador* jugador) = 0;
    virtual ~PowerUp() = default;
    virtual std::string getTipoString() const;
};

class DobleTurno : public PowerUp {
public:
    DobleTurno() : PowerUp(DOBLE_TURNO) {}
    void aplicar(Jugador* jugador) override;
};

class PrecisionMovimiento : public PowerUp {
public:
    PrecisionMovimiento() : PowerUp(PRECISION_MOVIMIENTO) {}
    void aplicar(Jugador* jugador) override;
};

class PrecisionAtaque : public PowerUp {
public:
    PrecisionAtaque() : PowerUp(PRECISION_ATAQUE) {}
    void aplicar(Jugador* jugador) override;
};

class PoderAtaque : public PowerUp {
public:
    PoderAtaque() : PowerUp(PODER_ATAQUE) {}
    void aplicar(Jugador* jugador) override;
};

#endif // POWERUP_H
