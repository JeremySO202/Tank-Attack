#include <iostream>
#include <QApplication>
#include <QPushButton>

#include "Mapa/Mapa.h"
#include "Pathfinding/Bfs.h"
#include "Pathfinding/Dijkstra.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    QPushButton button("Pruebas!", nullptr);
    Bfs bfs;
    Mapa *mapa = new Mapa();
    Ruta *ruta = new Ruta();
    //ruta = bfs.obtenerRuta(1,1,8,8,mapa);
    //mapa->moverTanque(ruta);
    button.resize(200, 100);
    button.show();
    std::cout << "Dijkstra" << std::endl;
    Dijkstra dijkstra;
    Ruta* rutaDijkstra = dijkstra.shortestPath(mapa->matrizAdyacencia, GRAPHSIZE, mapa->coordenadaANodo(1, 1), mapa->coordenadaANodo(8, 8), mapa);
    mapa->moverTanque(rutaDijkstra);

}
