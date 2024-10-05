//
// Created by jeremy on 21/09/24.
//

#include "Tanque.h"
#include <iostream>

Tanque::Tanque(int x, int y, Color color) : x(x), y(y), color(color) {}

void Tanque::interaccion() {
    std::cout << "Interacción con tanque" << std::endl;
}

const char* Tanque::recurso() {
    return "T";
}

int Tanque::getX() const {
    return x;
}

int Tanque::getY() const {
    return y;
}

Tanque::Color Tanque::getColor() const {
    return color;
}

void Tanque::setX(int x) {
    this->x = x;
}

void Tanque::setY(int y) {
    this->y = y;
}
