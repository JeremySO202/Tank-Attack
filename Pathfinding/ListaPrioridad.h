//
// Created by jeremy on 4/10/24.
//

#ifndef LISTA_H
#define LISTA_H

class Celda
{
public:
    int x, y;
    Celda* padre;
    Celda* next;
    float g;
    float h;

    /**
     * Metodo constructor
     * @param _x
     * @param _y
     * @param _p celda padre
     */
    Celda(int _x, int _y, Celda* _p)
    {
        x = _x;
        y = _y;
        padre = _p;
        h = 0;
        g = 0;
        next = nullptr;
    }

    /**
     * Calcula el costo final de una celda
     * @return costo final
     */
    float fCost() const
    {
        return g + h;
    }

};

class ListaPrioridad {
public:
    Celda* inicio;
    Celda* final;

    ListaPrioridad();
    ~ListaPrioridad();

    void queue(Celda *celda);
    Celda* dequeue();
    Celda* buscar(int x, int y);
    void eliminar(int x, int y);
};



#endif //LISTA_H
