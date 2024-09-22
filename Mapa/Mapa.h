//
// Created by jeremy on 21/09/24.
//

#ifndef MAPA_H
#define MAPA_H
#include "../Objetos/Objeto.h"

const int SIZE = 10;
const int GRAPHSIZE = SIZE * SIZE;
const int DESP_VERT_HORI = 10;
const int DESP_DIAGO = 14;


class Mapa {
private:
    int matrizAdyacencia[GRAPHSIZE][GRAPHSIZE] = {0};
    Objeto *matrizMapa[SIZE][SIZE];
    void inicializaMatrizAdyacencia();
    int coordenadaANodo(int x, int y);
    void cargaMapaAleatorio();
    void printMapa();

public:
    Mapa();


};



#endif //MAPA_H
