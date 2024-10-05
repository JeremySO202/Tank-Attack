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

public:
    Tanque(int x, int y, Color color);

    void interaccion() override;
    const char* recurso() override;

    int getX() const;
    int getY() const;
    Color getColor() const;

    void setX(int x);
    void setY(int y);
};

#endif // TANQUE_H

