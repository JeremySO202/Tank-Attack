//
// Created by jeremy on 21/09/24.
//

#ifndef MAPA_H
#define MAPA_H
#include "../Objetos/Objeto.h"
#include "../Pathfinding/Ruta.h"

const int SIZE = 10;
const int GRAPHSIZE = SIZE * SIZE;
const int DESP_VERT_HORI = 10;
const int DESP_DIAGO = 14;


class Mapa {
private:
    void inicializaMatrizAdyacencia();
    void cargaMapaAleatorio();

public:
    int matrizAdyacencia[GRAPHSIZE][GRAPHSIZE] = {0};
    Objeto *matrizMapa[SIZE][SIZE];

    Mapa();

    void moverTanque(Ruta *ruta);
    int coordenadaANodo(int x, int y);
    void printMapa();
    bool isValid(int x, int y);


};



#endif //MAPA_H
