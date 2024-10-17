//
// Created by jeremy on 21/09/24.
//
#ifndef TANQUE_H
#define TANQUE_H

#include "Objeto.h"

class Tanque : public Objeto {
public:
    enum class Color { ROJO, AMARILLO, AZUL, CELESTE };

private:
    int x;
    int y;
    Color color;
    int vida = 100;

public:
    Tanque(int x, int y, Color color);

    void interaccion() override;
    const char* recurso() override;

    int getX() const;
    int getY() const;
    Color getColor() const;
    int getVida() const;


    void setX(int x);
    void setY(int y);
    void setVida(int vida);
};

#endif // TANQUE_H

