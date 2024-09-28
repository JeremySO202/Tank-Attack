#include <iostream>
#include <QApplication>
#include <QPushButton>

#include "Mapa/Mapa.h"


int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    QPushButton button("Pruebas!", nullptr);

    // Crear el objeto del mapa e inicializar
    Mapa *mapa = new Mapa();

    // Probar el algoritmo de Dijkstra desde un nodo de origen (por ejemplo, nodo 0)
    mapa->probarDijkstra(0);
    mapa->probarDijkstra(5);
    mapa->probarDijkstra(10);

    button.resize(200, 100);
    button.show();
    return QApplication::exec();
}

