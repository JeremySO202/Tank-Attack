//
// Created by mvasquezr on 10/4/24.
//
#include "GameController.h"
#include "../Pathfinding/Bfs.h"
#include "../Pathfinding/Dijkstra.h"
#include "../Pathfinding/RandomMovement.h"
#include "../Objetos/Suelo.h"
#include <QTimer>
#include <iostream>
#include <cstdlib>
#include <ctime>

/**
 * @brief Constructor de GameController que inicializa los elementos del juego, como el mapa y el jugador.
 * @param parent Puntero al objeto padre.
 */
GameController::GameController(QObject* parent) : QObject(parent) {
    mapa = new Mapa();
    jugador = new Jugador(1, true);
    mainWindow = new MainWindow(mapa, nullptr);

    Tanque* tanqueRojo = new Tanque(1, 1, Tanque::Color::ROJO);
    jugador->agregarTanque(tanqueRojo);
    mapa->matrizMapa[1][1] = tanqueRojo;

    std::srand(static_cast<unsigned int>(std::time(0)));

    connect(mainWindow, &MainWindow::tanqueSeleccionadoSignal, this, &GameController::onTanqueSeleccionado);
    connect(mainWindow, &MainWindow::destinoSeleccionadoSignal, this, &GameController::onDestinoSeleccionado);
}

/**
 * @brief Muestra la ventana principal y actualiza el estado inicial del mapa.
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
 * @brief Slot que maneja la selección de un tanque.
 * @param x Coordenada en el eje x del tanque seleccionado.
 * @param y Coordenada en el eje y del tanque seleccionado.
 */
void GameController::onTanqueSeleccionado(int x, int y) {
    if (!mainWindow->enMovimiento) {
        jugador->seleccionarTanque(x, y);
    }
}

/**
 * @brief Slot que maneja la selección de un destino para el tanque seleccionado.
 * @param x Coordenada en el eje x del destino.
 * @param y Coordenada en el eje y del destino.
 */
void GameController::onDestinoSeleccionado(int x, int y) {
    if (!mainWindow->enMovimiento && jugador->getTanqueSeleccionado() != nullptr) {
        jugador->setDestino(x, y);

        Tanque* tanqueSeleccionado = jugador->getTanqueSeleccionado();
        if (tanqueSeleccionado) {
            Ruta* ruta = nullptr;

            int randomValue = std::rand() % 100;

            // Selección de algoritmo según el color del tanque
            if (tanqueSeleccionado->getColor() == Tanque::Color::AZUL || tanqueSeleccionado->getColor() == Tanque::Color::CELESTE) {
                if (randomValue < 50) {
                    std::cout << "Utilizando BFS." << std::endl;
                    Bfs bfs;
                    ruta = bfs.obtenerRuta(tanqueSeleccionado->getX(), tanqueSeleccionado->getY(), x, y, mapa);
                } else {
                    std::cout << "Utilizando movimiento aleatorio." << std::endl;
                    RandomMovement randomMovement;
                    ruta = randomMovement.obtenerMovimientoAleatorio(tanqueSeleccionado->getX(), tanqueSeleccionado->getY(), mapa);
                }
            } else if (tanqueSeleccionado->getColor() == Tanque::Color::ROJO || tanqueSeleccionado->getColor() == Tanque::Color::AMARILLO) {
                if (randomValue < 80) {
                    std::cout << "Utilizando Dijkstra." << std::endl;
                    ruta = Dijkstra::shortestPath(mapa->matrizAdyacencia, GRAPHSIZE, mapa->coordenadaANodo(tanqueSeleccionado->getX(), tanqueSeleccionado->getY()), mapa->coordenadaANodo(x, y), mapa);
                } else {
                    std::cout << "Utilizando movimiento aleatorio." << std::endl;
                    RandomMovement randomMovement;
                    ruta = randomMovement.obtenerMovimientoAleatorio(tanqueSeleccionado->getX(), tanqueSeleccionado->getY(), mapa);
                }
            }

            if (ruta == nullptr || ruta->inicio == nullptr) {
                std::cout << "No se pudo encontrar una ruta válida al destino." << std::endl;
                return;
            }

            // Mover el tanque usando la ruta seleccionada
            Nodo* nodoActual = ruta->inicio;
            mainWindow->enMovimiento = true;

            QTimer* timer = new QTimer(this);
            connect(timer, &QTimer::timeout, [=]() mutable {
                if (nodoActual != nullptr) {
                    int nuevoX = nodoActual->x;
                    int nuevoY = nodoActual->y;

                    if (nuevoX < 0 || nuevoX >= SIZE || nuevoY < 0 || nuevoY >= SIZE) {
                        std::cout << "Coordenadas inválidas detectadas: (" << nuevoX << ", " << nuevoY << "). Deteniendo movimiento." << std::endl;
                        timer->stop();
                        mainWindow->enMovimiento = false;
                        return;
                    }

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
                    std::cout << "Mapa después de mover tanque usando algoritmo de pathfinding:" << std::endl;
                    mapa->printMapa();
                }
            });

            timer->start(500);
        }
    }
}
