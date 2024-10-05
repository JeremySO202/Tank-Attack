//
// Created by mvasquezr on 10/4/24.
//
#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include "../Mapa/Mapa.h"
#include "../Game/Jugador.h"
#include "../Interfaz/MainWindow.h"

class GameController : public QObject {
    Q_OBJECT

private:
    Mapa* mapa;
    MainWindow* mainWindow;
    Jugador* jugador;

public:
    GameController(QObject* parent = nullptr);
    void iniciarJuego();

private slots:
    void onTanqueSeleccionado(int x, int y);
    void onDestinoSeleccionado(int x, int y);
};

#endif // GAMECONTROLLER_H

