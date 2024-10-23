//
// Created by mvasquezr on 10/4/24.
//

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include "../Mapa/Mapa.h"
#include "../Game/Jugador.h"
#include "../Interfaz/MainWindow.h"
#include "../Game/GameManager.h"

class GameController : public QObject {
    Q_OBJECT

private:
    Mapa* mapa;
    MainWindow* mainWindow;
    GameManager* gameManager;
    int tiempoRestante;


public:
    GameController(QObject* parent = nullptr);

    void mostrarMensaje(int ganador);

    void generarPowerUpAleatorio(Jugador* jugador);
    void iniciarJuego();

private slots:
    void onTanqueSeleccionado(int x, int y);
    void onDestinoSeleccionado(int x, int y);
    void onDisparoSeleccionado(int x, int y);
    void onUsarPowerUp();
};

#endif // GAMECONTROLLER_H
