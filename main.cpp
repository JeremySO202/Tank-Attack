#include <iostream>
#include <QApplication>
#include <QPushButton>

#include "Mapa/Mapa.h"
#include "Pathfinding/Bfs.h"
#include "Pathfinding/Dijkstra.h"
#include "Interfaz/MainWindow.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return a.exec();

    Bfs bfs;
    Mapa *mapa = new Mapa();
    Ruta *ruta = new Ruta();
    //ruta = bfs.obtenerRuta(1,1,8,8,mapa);
    //mapa->moverTanque(ruta);
    std::cout << "Dijkstra" << std::endl;
    Dijkstra dijkstra;
    Ruta* rutaDijkstra = dijkstra.shortestPath(mapa->matrizAdyacencia, GRAPHSIZE, mapa->coordenadaANodo(1, 1), mapa->coordenadaANodo(8, 8), mapa);
    mapa->moverTanque(rutaDijkstra);

}
