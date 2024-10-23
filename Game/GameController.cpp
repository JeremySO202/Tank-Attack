//
// Created by mvasquezr on 10/4/24.
//

#include "GameController.h"
#include "../Pathfinding/Bfs.h"
#include "../Pathfinding/Astar.h"
#include "../Pathfinding/Dijkstra.h"
#include "../Pathfinding/RandomMovement.h"
#include "../Objetos/Suelo.h"
#include <QTimer>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <QMessageBox>

#include "../Interfaz/StartWindow.h"
#include "../Pathfinding/LineaVista.h"

/**
 * @brief Constructor de GameController que inicializa los elementos del juego, como el mapa y los jugadores.
 * @param parent Puntero al objeto padre.
 */
GameController::GameController(QObject* parent) : QObject(parent)
{
    mapa = new Mapa();
    gameManager = new GameManager(mapa, this);

    // Inicializar los dos jugadores y sus tanques
    Jugador* jugador1 = new Jugador(1, true);
    Jugador* jugador2 = new Jugador(2, true);

    Tanque* tanqueRojo1 = new Tanque(1, 1, Tanque::Color::ROJO);
    Tanque* tanqueRojo2 = new Tanque(2, 1, Tanque::Color::ROJO);
    Tanque* tanqueAzul1 = new Tanque(3, 1, Tanque::Color::AZUL);
    Tanque* tanqueAzul2 = new Tanque(4, 1, Tanque::Color::AZUL);
    jugador1->agregarTanque(tanqueRojo1);
    jugador1->agregarTanque(tanqueRojo2);
    jugador1->agregarTanque(tanqueAzul1);
    jugador1->agregarTanque(tanqueAzul2);
    mapa->matrizMapa[1][1] = tanqueRojo1;
    mapa->matrizMapa[1][2] = tanqueRojo2;
    mapa->matrizMapa[1][3] = tanqueAzul1;
    mapa->matrizMapa[1][4] = tanqueAzul2;

    mapa->inicializaMatrizAdyacencia();

    Tanque* tanqueAmarillo1 = new Tanque(13, 13, Tanque::Color::AMARILLO);
    Tanque* tanqueAmarillo2 = new Tanque(12, 13, Tanque::Color::AMARILLO);
    Tanque* tanqueCeleste1 = new Tanque(11, 13, Tanque::Color::CELESTE);
    Tanque* tanqueCeleste2 = new Tanque(10, 13, Tanque::Color::CELESTE);

    jugador2->agregarTanque(tanqueAmarillo1);
    jugador2->agregarTanque(tanqueAmarillo2);
    jugador2->agregarTanque(tanqueCeleste1);
    jugador2->agregarTanque(tanqueCeleste2);
    mapa->matrizMapa[13][13] = tanqueAmarillo1;
    mapa->matrizMapa[13][12] = tanqueAmarillo2;
    mapa->matrizMapa[13][11] = tanqueCeleste1;
    mapa->matrizMapa[13][10] = tanqueCeleste2;

    gameManager->agregarJugador(jugador1);
    gameManager->agregarJugador(jugador2);

    mainWindow = new MainWindow(mapa, gameManager);

    std::srand(static_cast<unsigned int>(std::time(0)));

    connect(mainWindow, &MainWindow::tanqueSeleccionadoSignal, this, &GameController::onTanqueSeleccionado);
    connect(mainWindow, &MainWindow::destinoSeleccionadoSignal, this, &GameController::onDestinoSeleccionado);
    connect(mainWindow, &MainWindow::disparoSeleccionadoSignal, this, &GameController::onDisparoSeleccionado);
    connect(mainWindow, &MainWindow::usarPowerUpSignal, this, &GameController::onUsarPowerUp);
}

void GameController::mostrarMensaje(int ganador)
{
    QMessageBox msgBox;
    msgBox.setText("Fin del juego.");
    msgBox.setInformativeText("El jugador " + QString::number(ganador) + " ha perdido.");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);

    int result = msgBox.exec();

    if (result == QMessageBox::Ok)
    {
        mainWindow->close();

        StartWindow* start_window = new StartWindow();
        start_window->show();
    }
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
            int ganador = gameManager->obtenerGanador();
            mostrarMensaje(ganador + 1);
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
        mainWindow->actualizarTanque();
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

                if (jugadorActual->getPrecisionMovimiento() && randomValue < 90)
                {
                    std::cout << "Power-Up Precisión de Movimiento activado con un 90% de probabilidad." << std::endl;
                    if (tanqueSeleccionado->getColor() == Tanque::Color::AZUL || tanqueSeleccionado->getColor() ==
                        Tanque::Color::CELESTE)
                    {
                        Bfs bfs;
                        ruta = bfs.obtenerRuta(tanqueSeleccionado->getX(), tanqueSeleccionado->getY(), x, y, mapa);
                    }
                    else
                    {
                        ruta = Dijkstra::shortestPath(mapa->matrizAdyacencia, GRAPHSIZE,
                                                      mapa->coordenadaANodo(
                                                          tanqueSeleccionado->getX(), tanqueSeleccionado->getY()),
                                                      mapa->coordenadaANodo(x, y), mapa);
                    }
                    jugadorActual->setPrecisionMovimiento(false); // Desactivar para el siguiente turno
                }
                else if (tanqueSeleccionado->getColor() == Tanque::Color::AZUL || tanqueSeleccionado->getColor() ==
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
                int oldX = nodoActual->x;
                int oldY = nodoActual->y;
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

                        mainWindow->actualizarTanque();
                        mainWindow->forzarActualizacion();

                        std::cout << "Moviendo tanque a: (" << nuevoX << ", " << nuevoY << ")" << std::endl;

                        nodoActual = nodoActual->next;
                    }
                    else
                    {
                        mainWindow->pintarRuta(ruta);
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

                // Verificar si el power-up de precisión de ataque está activo
                if (jugadorActual->getPrecisionAtaque())
                {
                    std::cout << "Power-Up Precisión de Ataque activado: utilizando algoritmo A*." << std::endl;
                    Astar aStar;
                    ruta = aStar.obtenerRuta(tanqueSeleccionado->getX(), tanqueSeleccionado->getY(), x, y, mapa);
                    jugadorActual->setPrecisionAtaque(false); // Desactivar para el siguiente turno
                }
                else
                {
                    // Usar el comportamiento normal sin power-up (linea de vista)
                    LineaVista linea_vista;
                    ruta = linea_vista.obtenerRuta(tanqueSeleccionado->getX(), tanqueSeleccionado->getY(), x, y, mapa,
                                                   3);
                }

                if (ruta == nullptr || ruta->inicio == nullptr)
                {
                    std::cout << "No se pudo encontrar una ruta válida para el disparo." << std::endl;
                    return;
                }

                Nodo* nodoActual = ruta->inicio;
                int oldX = nodoActual->x;
                int oldY = nodoActual->y;
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

                        mainWindow->pintarBala(nuevoX, nuevoY, oldX, oldY);

                        std::cout << "Moviendo bala a: (" << nuevoX << ", " << nuevoY << ")" << std::endl;

                        if (typeid(*mapa->matrizMapa[nodoActual->y][nodoActual->x]) == typeid(Tanque))
                        {
                            Tanque* tanqueGolpeado = dynamic_cast<Tanque*>(mapa->matrizMapa[nodoActual->y][nodoActual->
                                x]);
                            if (tanqueGolpeado->getColor() == Tanque::Color::AZUL || tanqueGolpeado->getColor() ==
                                Tanque::Color::CELESTE)
                            {
                                std::cout << "-25 de vida" << std::endl;
                                tanqueGolpeado->setVida(tanqueGolpeado->getVida() - 25);
                            }
                            else if (tanqueGolpeado->getColor() == Tanque::Color::ROJO || tanqueGolpeado->getColor() ==
                                Tanque::Color::AMARILLO)
                            {
                                std::cout << "-50 de vida" << std::endl;
                                tanqueGolpeado->setVida(tanqueGolpeado->getVida() - 50);
                            }
                            if (tanqueGolpeado->getVida() <= 0)
                            {
                                gameManager->actualizarTanques();
                                std::cout << "Tanque Golpeado se ha quedado sin vida" << std::endl;
                            }
                            nodoActual = nullptr;
                        }
                        else
                        {
                            oldX = nuevoX;
                            oldY = nuevoY;

                            nodoActual = nodoActual->next;
                        }
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

/**
 * @brief Slot que maneja el uso de power-ups.
 */
void GameController::onUsarPowerUp()
{
    Jugador* jugadorActual = gameManager->getJugadorActual();

    // Verificar si el jugador puede usar un Power-Up
    if (gameManager->puedeUsarPowerUp())
    {
        int powerUpCount = 0;
        PowerUp* const* powerUps = jugadorActual->getPowerUps(powerUpCount);
        // Obtener el array de PowerUps y su cantidad

        if (powerUpCount > 0)
        {
            // Activar el último Power-Up y almacenar el tipo para mostrarlo en la interfaz
            PowerUp* powerUp = powerUps[powerUpCount - 1];
            mainWindow->setPowerUpActivo(QString("Jugador %1: %2")
                                         .arg(jugadorActual->getId())
                                         .arg(QString::fromStdString(powerUp->getTipoString())));

            // Gasta el turno actual y cambia al siguiente jugador
            gameManager->usarPowerUp();
            gameManager->cambiarTurno();
            mainWindow->actualizarInformacionJuego(gameManager->getJugadorActual(), tiempoRestante);
        }
        else
        {
            std::cout << "No hay power-ups para usar." << std::endl;
        }
    }
    else
    {
        std::cout << "No hay power-ups disponibles para usar." << std::endl;
    }
}

/**
 * @brief Genera un power-up aleatorio para el jugador actual.
 */
void GameController::generarPowerUpAleatorio(Jugador* jugador)
{
    std::cout << "Generando Power-Up para el jugador " << jugador->getId() << std::endl;
    int randomValue = std::rand() % 4;
    PowerUp* nuevoPowerUp = nullptr;

    switch (randomValue)
    {
    case 0:
        nuevoPowerUp = new DobleTurno();
        break;
    case 1:
        nuevoPowerUp = new PrecisionMovimiento();
        break;
    case 2:
        nuevoPowerUp = new PrecisionAtaque();
        break;
    case 3:
        nuevoPowerUp = new PoderAtaque();
        break;
    default:
        std::cerr << "Error: valor de Power-Up inválido" << std::endl;
        return;
    }

    if (nuevoPowerUp)
    {
        std::cout << "Añadiendo Power-Up " << nuevoPowerUp->getTipoString() << " al jugador " << jugador->getId() <<
            std::endl;
        jugador->agregarPowerUp(nuevoPowerUp);
        mainWindow->actualizarInformacionJuego(jugador, tiempoRestante);
    }
}
