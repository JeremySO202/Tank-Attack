//
// Created by jeremy on 28/09/24.
//

#ifndef RUTA_H
#define RUTA_H


class Nodo
{
public:

    int x = -1;
    int y = -1;
    Nodo *next = nullptr;
    Nodo *padre = nullptr;

    Nodo(int _x, int _y, Nodo *_p);
    Nodo(int _x, int _y);
    ~Nodo();
};

class Ruta {
public:
    Nodo *inicio;
    Nodo *final;

    Ruta();
    ~Ruta();

    void queue(Nodo *nodo);
    void add(Nodo *nodo);
    Nodo* dequeue();

};



#endif //RUTA_H
