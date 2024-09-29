//
// Created by mvasquezr on 9/28/24.
//

#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include "MapWidget.h"
#include "../Mapa/Mapa.h"

class GameWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);

private:
    MapWidget *mapWidget;
    Mapa *mapa;
};

#endif // GAMEWINDOW_H

