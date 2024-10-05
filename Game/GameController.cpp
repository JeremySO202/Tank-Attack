//
// Created by mvasquezr on 10/4/24.
//
#include "GameController.h"
#include "../Pathfinding/Bfs.h"
#include "../Objetos/Suelo.h"
#include "../Pathfinding/Dijkstra.h"
#include <QTimer>
#include <iostream>

/**
 * Constructor: Inicializa mapa, jugador y ventana principal, conecta señales.
 * @param parent Puntero al objeto padre.
 */
GameController::GameController(QObject* parent) : QObject(parent) {
    mapa = new Mapa();
    jugador = new Jugador(1, true);
    mainWindow = new MainWindow(mapa, nullptr);

    Tanque* tanqueRojo = new Tanque(1, 1, Tanque::Color::ROJO);
    jugador->agregarTanque(tanqueRojo);
    mapa->matrizMapa[1][1] = tanqueRojo;

    connect(mainWindow, &MainWindow::tanqueSeleccionadoSignal, this, &GameController::onTanqueSeleccionado);
    connect(mainWindow, &MainWindow::destinoSeleccionadoSignal, this, &GameController::onDestinoSeleccionado);
}

/**
 * Inicia el juego mostrando la ventana principal.
 */
void GameController::iniciarJuego() {
    mainWindow->show();
    mainWindow->raise();
    mainWindow->activateWindow();

    std::cout << "Mapa inicial con tanque añadido:" << std::endl;
    mapa->printMapa();
    mainWindow->actualizarTanque(1, 1);
}

/**
 * Maneja la selección de un tanque.
 * @param x Coordenada x.
 * @param y Coordenada y.
 */
void GameController::onTanqueSeleccionado(int x, int y) {
    if (!mainWindow->enMovimiento) {
        jugador->seleccionarTanque(x, y);
    }
}

/**
 * Maneja la selección de un destino y mueve el tanque.
 * @param x Coordenada x del destino.
 * @param y Coordenada y del destino.
 */
void GameController::onDestinoSeleccionado(int x, int y) {
    if (!mainWindow->enMovimiento && jugador->getTanqueSeleccionado() != nullptr) {
        jugador->setDestino(x, y);
        Tanque* tanqueSeleccionado = jugador->getTanqueSeleccionado();
        if (tanqueSeleccionado) {
            Ruta* ruta = nullptr;

            // Selección del algoritmo según el color del tanque
            if (tanqueSeleccionado->getColor() == Tanque::Color::AZUL || tanqueSeleccionado->getColor() == Tanque::Color::CELESTE) {
                std::cout << "Utilizando BFS." << std::endl;
                Bfs bfs;
                ruta = bfs.obtenerRuta(tanqueSeleccionado->getX(), tanqueSeleccionado->getY(), x, y, mapa);
            } else {
                std::cout << "Utilizando Dijkstra." << std::endl;
                ruta = Dijkstra::shortestPath(mapa->matrizAdyacencia, GRAPHSIZE, mapa->coordenadaANodo(tanqueSeleccionado->getX(), tanqueSeleccionado->getY()), mapa->coordenadaANodo(x, y), mapa);
            }

            if (!ruta || !ruta->inicio) {
                std::cout << "No se pudo encontrar una ruta válida." << std::endl;
                return;
            }

            Nodo* nodoActual = ruta->inicio;
            mainWindow->enMovimiento = true;

            QTimer* timer = new QTimer(this);
            connect(timer, &QTimer::timeout, [=]() mutable {
                if (nodoActual) {
                    int nuevoX = nodoActual->x;
                    int nuevoY = nodoActual->y;

                    // Verificar límites
                    if (nuevoX < 0 || nuevoX >= SIZE || nuevoY < 0 || nuevoY >= SIZE) {
                        std::cout << "Coordenadas inválidas: (" << nuevoX << ", " << nuevoY << "). Deteniendo movimiento." << std::endl;
                        timer->stop();
                        mainWindow->enMovimiento = false;
                        return;
                    }

                    // Mover tanque y actualizar GUI
                    mapa->matrizMapa[tanqueSeleccionado->getY()][tanqueSeleccionado->getX()] = new Suelo();
                    tanqueSeleccionado->setX(nuevoX);
                    tanqueSeleccionado->setY(nuevoY);
                    mapa->matrizMapa[nuevoY][nuevoX] = tanqueSeleccionado;

                    mainWindow->actualizarTanque(nuevoX, nuevoY);
                    mainWindow->forzarActualizacion();

                    std::cout << "Moviendo tanque a: (" << nuevoX << ", " << nuevoY << ")" << std::endl;
                    nodoActual = nodoActual->next;
                } else {
                    timer->stop();
                    jugador->limpiarSeleccion();
                    mainWindow->enMovimiento = false;
                    std::cout << "Mapa después de mover tanque:" << std::endl;
                    mapa->printMapa();
                }
            });

            timer->start(500);
        }
    }
}
