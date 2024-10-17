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

#include "../Pathfinding/LineaVista.h"

/**
 * @brief Constructor de GameController que inicializa los elementos del juego, como el mapa y los jugadores.
 * @param parent Puntero al objeto padre.
 */
GameController::GameController(QObject* parent) : QObject(parent)
{
    mapa = new Mapa();
    gameManager = new GameManager(mapa);

    // Inicializar los dos jugadores y sus tanques
    Jugador* jugador1 = new Jugador(1, true);
    Jugador* jugador2 = new Jugador(2, true);

    Tanque* tanqueRojo = new Tanque(1, 1, Tanque::Color::ROJO);
    Tanque* tanqueAzul = new Tanque(2, 1, Tanque::Color::AZUL);
    jugador1->agregarTanque(tanqueRojo);
    jugador1->agregarTanque(tanqueAzul);
    mapa->matrizMapa[1][1] = tanqueRojo;
    mapa->matrizMapa[1][2] = tanqueAzul;

    Tanque* tanqueAmarillo = new Tanque(8, 8, Tanque::Color::AMARILLO);
    Tanque* tanqueCeleste = new Tanque(7, 8, Tanque::Color::CELESTE);
    jugador2->agregarTanque(tanqueAmarillo);
    jugador2->agregarTanque(tanqueCeleste);
    mapa->matrizMapa[8][8] = tanqueAmarillo;
    mapa->matrizMapa[8][7] = tanqueCeleste;

    gameManager->agregarJugador(jugador1);
    gameManager->agregarJugador(jugador2);

    mainWindow = new MainWindow(mapa, gameManager);

    std::srand(static_cast<unsigned int>(std::time(0)));

    connect(mainWindow, &MainWindow::tanqueSeleccionadoSignal, this, &GameController::onTanqueSeleccionado);
    connect(mainWindow, &MainWindow::destinoSeleccionadoSignal, this, &GameController::onDestinoSeleccionado);
    connect(mainWindow, &MainWindow::disparoSeleccionadoSignal, this, &GameController::onDisparoSeleccionado);
}

/**
 * @brief Muestra la ventana principal y actualiza el estado inicial del mapa.
 */
void GameController::iniciarJuego()
{
    mainWindow->show();
    mainWindow->raise();
    mainWindow->activateWindow();

    // Inicializa el tiempo restante (en segundos)
    int tiempoRestante = 300; // 5 minutos

    // Iniciar un temporizador que cuenta hacia atrás
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=]() mutable
    {
        if (tiempoRestante > 0)
        {
            tiempoRestante--;
            mainWindow->actualizarInformacionJuego(gameManager->getJugadorActual(), tiempoRestante);
        }
        else
        {
            timer->stop();
            std::cout << "El tiempo se ha agotado. Fin del juego." << std::endl;
        }
    });
    timer->start(1000); // Cuenta regresiva cada segundo

    // Actualizar la interfaz al inicio del juego
    mainWindow->actualizarInformacionJuego(gameManager->getJugadorActual(), tiempoRestante);

    std::cout << "Mapa inicial con tanques añadidos:" << std::endl;
    mapa->printMapa();
}


/**
 * @brief Slot que maneja la selección de un tanque.
 * @param x Coordenada en el eje x del tanque seleccionado.
 * @param y Coordenada en el eje y del tanque seleccionado.
 */
void GameController::onTanqueSeleccionado(int x, int y)
{
    if (!mainWindow->enMovimiento)
    {
        gameManager->seleccionarTanque(x, y);
    }
}

/**
 * @brief Slot que maneja la selección de un destino para el tanque seleccionado.
 * @param x Coordenada en el eje x del destino.
 * @param y Coordenada en el eje y del destino.
 */
void GameController::onDestinoSeleccionado(int x, int y)
{
    if (!mainWindow->enMovimiento)
    {
        Jugador* jugadorActual = gameManager->getJugadorActual();

        if (jugadorActual->getTanqueSeleccionado() != nullptr)
        {
            jugadorActual->setDestino(x, y);

            Tanque* tanqueSeleccionado = jugadorActual->getTanqueSeleccionado();
            if (tanqueSeleccionado)
            {
                Ruta* ruta = nullptr;

                int randomValue = std::rand() % 100;

                // Selección de algoritmo según el color del tanque
                if (tanqueSeleccionado->getColor() == Tanque::Color::AZUL || tanqueSeleccionado->getColor() ==
                    Tanque::Color::CELESTE)
                {
                    if (randomValue < 50)
                    {
                        std::cout << "Utilizando BFS." << std::endl;
                        Bfs bfs;
                        ruta = bfs.obtenerRuta(tanqueSeleccionado->getX(), tanqueSeleccionado->getY(), x, y, mapa);
                    }
                    else
                    {
                        std::cout << "Utilizando movimiento aleatorio." << std::endl;
                        RandomMovement randomMovement;
                        ruta = randomMovement.obtenerMovimientoAleatorio(
                            tanqueSeleccionado->getX(), tanqueSeleccionado->getY(), mapa);
                    }
                }
                else if (tanqueSeleccionado->getColor() == Tanque::Color::ROJO || tanqueSeleccionado->getColor() ==
                    Tanque::Color::AMARILLO)
                {
                    if (randomValue < 80)
                    {
                        std::cout << "Utilizando Dijkstra." << std::endl;
                        ruta = Dijkstra::shortestPath(mapa->matrizAdyacencia, GRAPHSIZE,
                                                      mapa->coordenadaANodo(
                                                          tanqueSeleccionado->getX(), tanqueSeleccionado->getY()),
                                                      mapa->coordenadaANodo(x, y), mapa);
                    }
                    else
                    {
                        std::cout << "Utilizando movimiento aleatorio." << std::endl;
                        RandomMovement randomMovement;
                        ruta = randomMovement.obtenerMovimientoAleatorio(
                            tanqueSeleccionado->getX(), tanqueSeleccionado->getY(), mapa);
                    }
                }

                if (ruta == nullptr || ruta->inicio == nullptr)
                {
                    std::cout << "No se pudo encontrar una ruta válida al destino." << std::endl;
                    return;
                }

                // Mover el tanque usando la ruta seleccionada
                Nodo* nodoActual = ruta->inicio;
                mainWindow->enMovimiento = true;

                QTimer* timer = new QTimer(this);
                connect(timer, &QTimer::timeout, [=]() mutable
                {
                    if (nodoActual != nullptr)
                    {
                        int nuevoX = nodoActual->x;
                        int nuevoY = nodoActual->y;

                        if (nuevoX < 0 || nuevoX >= SIZE || nuevoY < 0 || nuevoY >= SIZE)
                        {
                            std::cout << "Coordenadas inválidas detectadas: (" << nuevoX << ", " << nuevoY <<
                                "). Deteniendo movimiento." << std::endl;
                            timer->stop();
                            mainWindow->enMovimiento = false;
                            return;
                        }

                        // Setear la posición anterior del tanque como suelo
                        mapa->matrizMapa[tanqueSeleccionado->getY()][tanqueSeleccionado->getX()] = new Suelo();

                        // Actualizar posición del tanque
                        tanqueSeleccionado->setX(nuevoX);
                        tanqueSeleccionado->setY(nuevoY);
                        mapa->matrizMapa[nuevoY][nuevoX] = tanqueSeleccionado;

                        mainWindow->actualizarTanque(nuevoX, nuevoY);
                        mainWindow->forzarActualizacion();

                        std::cout << "Moviendo tanque a: (" << nuevoX << ", " << nuevoY << ")" << std::endl;

                        nodoActual = nodoActual->next;
                    }
                    else
                    {
                        timer->stop();
                        jugadorActual->limpiarSeleccion();
                        mainWindow->enMovimiento = false;

                        // Cambiar al siguiente jugador después de que termine el movimiento
                        gameManager->cambiarTurno();
                        std::cout << "Mapa después de mover tanque usando algoritmo de pathfinding:" << std::endl;
                        mapa->printMapa();
                    }
                });

                timer->start(500);
            }
        }
    }
}

void GameController::onDisparoSeleccionado(int x, int y)
{
    if (!mainWindow->enMovimiento)
    {
        Jugador* jugadorActual = gameManager->getJugadorActual();

        if (jugadorActual->getTanqueSeleccionado() != nullptr)
        {
            jugadorActual->setDisparo(x, y);
            Tanque* tanqueSeleccionado = jugadorActual->getTanqueSeleccionado();


            if (tanqueSeleccionado)
            {
                Ruta* ruta = nullptr;

                LineaVista linea_vista;
                ruta = linea_vista.obtenerRuta(tanqueSeleccionado->getX(), tanqueSeleccionado->getY(), x, y, mapa, 3);

                Nodo* nodoActual = ruta->inicio;
                mainWindow->enMovimiento = true;

                QTimer* timer = new QTimer(this);
                connect(timer, &QTimer::timeout, [=]() mutable
                {
                    if (nodoActual != nullptr)
                    {
                        if (typeid(*mapa->matrizMapa[nodoActual->y][nodoActual->x]) == typeid(Tanque))
                        {
                            Tanque* tanqueGolpeado = dynamic_cast<Tanque*>(mapa->matrizMapa[nodoActual->y][nodoActual->
                                x]);
                            if (tanqueGolpeado->getColor() == Tanque::Color::AZUL || tanqueGolpeado->getColor() ==
                                Tanque::Color::CELESTE)
                            {
                                tanqueGolpeado->setVida(tanqueSeleccionado->getVida()-25);
                            }
                            else if (tanqueGolpeado->getColor() == Tanque::Color::ROJO || tanqueGolpeado->getColor() ==
                                Tanque::Color::AMARILLO)
                            {
                                tanqueGolpeado->setVida(tanqueSeleccionado->getVida()-50);
                            }
                            if (tanqueGolpeado->getVida() <= 0)
                            {
                                std::cout << "Tanque Golpeado se ha quedado sin vida" << std::endl;
                            }
                        }
                        int nuevoX = nodoActual->x;
                        int nuevoY = nodoActual->y;

                        if (nuevoX < 0 || nuevoX >= SIZE || nuevoY < 0 || nuevoY >= SIZE)
                        {
                            std::cout << "Coordenadas inválidas detectadas: (" << nuevoX << ", " << nuevoY <<
                                "). Deteniendo movimiento." << std::endl;
                            timer->stop();
                            mainWindow->enMovimiento = false;
                            return;
                        }


                        mainWindow->pintarBala(nuevoX, nuevoY);

                        std::cout << "Moviendo bala a: (" << nuevoX << ", " << nuevoY << ")" << std::endl;

                        nodoActual = nodoActual->next;
                    }
                    else
                    {
                        timer->stop();
                        jugadorActual->limpiarSeleccion();
                        mainWindow->enMovimiento = false;

                        // Cambiar al siguiente jugador después de que termine el movimiento
                        gameManager->cambiarTurno();
                        std::cout << "Mapa después de mover tanque usando algoritmo de pathfinding:" << std::endl;
                        mapa->printMapa();
                    }
                });

                timer->start(500);
            }
        }
    }
}
