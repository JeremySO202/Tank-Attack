//
// Created by mvasquezr on 9/28/24.
//
#include "GameWindow.h"

GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent) {
    mapa = new Mapa();
    mapWidget = new MapWidget(mapa, this);
    setCentralWidget(mapWidget);

    setWindowTitle("Juego - Tank Attack!");
    resize(1024, 768);
}
