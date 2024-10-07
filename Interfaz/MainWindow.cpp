//
// Created by mvasquezr on 9/28/24.
//
#include "MainWindow.h"
#include <QGraphicsRectItem>
#include <QBrush>
#include <QMouseEvent>
#include <QTimer>
#include <QVBoxLayout>
#include "../Objetos/Indestructible.h"
#include "../Objetos/Suelo.h"
#include "../Objetos/Tanque.h"

/**
 * Constructor de MainWindow.
 * Inicializa la interfaz gráfica, la escena y el mapa.
 * @param mapa Puntero al objeto Mapa.
 * @param gameManager Puntero al administrador del juego.
 * @param parent Puntero al objeto padre.
 */
MainWindow::MainWindow(Mapa* mapa, GameManager* gameManager, QWidget* parent)
    : QMainWindow(parent), mapa(mapa), gameManager(gameManager), enMovimiento(false) {
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    informacionLabel = new QLabel(this); // Inicializamos el label para mostrar información del juego

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(view);
    layout->addWidget(informacionLabel);

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    inicializarMapa(mapa);
    resize(570, 570);
}

/**
 * Actualiza la información del turno del jugador y el tiempo restante.
 * @param jugadorActual Puntero al jugador actual.
 * @param tiempoRestante Tiempo restante en segundos.
 */
void MainWindow::actualizarInformacionJuego(Jugador* jugadorActual, int tiempoRestante) {
    QString info = QString("Turno: jugador %1\nTiempo restante: %2 segundos")
                   .arg(jugadorActual->getId())
                   .arg(tiempoRestante);
    informacionLabel->setText(info);
}

/**
 * Inicializa el mapa dibujando cada celda.
 * @param mapa Puntero al objeto Mapa.
 */
void MainWindow::inicializarMapa(Mapa* mapa) {
    int cellSize = 50;

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            QGraphicsRectItem* cell = scene->addRect(j * cellSize, i * cellSize, cellSize, cellSize);
            if (typeid(*mapa->matrizMapa[i][j]) == typeid(Indestructible)) {
                cell->setBrush(Qt::darkGray);
            } else if (typeid(*mapa->matrizMapa[i][j]) == typeid(Suelo)) {
                cell->setBrush(Qt::green);
            } else if (typeid(*mapa->matrizMapa[i][j]) == typeid(Tanque)) {
                Tanque* tanque = dynamic_cast<Tanque*>(mapa->matrizMapa[i][j]);
                if (tanque != nullptr) {
                    switch (tanque->getColor()) {
                        case Tanque::Color::ROJO:
                            cell->setBrush(Qt::red);
                            break;
                        case Tanque::Color::AZUL:
                            cell->setBrush(Qt::blue);
                            break;
                        case Tanque::Color::AMARILLO:
                            cell->setBrush(Qt::yellow);
                            break;
                        case Tanque::Color::CELESTE:
                            cell->setBrush(Qt::cyan);
                            break;
                    }
                }
            }
        }
    }
}

/**
 * Actualiza la posición del tanque en el mapa.
 * @param x Coordenada x.
 * @param y Coordenada y.
 */
void MainWindow::actualizarTanque(int nuevoX, int nuevoY) {
    int cellSize = 50;

    // Actualizar toda la cuadrícula de nuevo para reflejar el estado actual
    scene->clear(); // Limpiamos toda la escena para asegurarnos de redibujarla correctamente

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            QGraphicsRectItem* cell = scene->addRect(j * cellSize, i * cellSize, cellSize, cellSize);

            if (typeid(*mapa->matrizMapa[i][j]) == typeid(Indestructible)) {
                cell->setBrush(Qt::darkGray);
            } else if (typeid(*mapa->matrizMapa[i][j]) == typeid(Suelo)) {
                cell->setBrush(Qt::green);
            } else if (typeid(*mapa->matrizMapa[i][j]) == typeid(Tanque)) {
                Tanque* tanque = dynamic_cast<Tanque*>(mapa->matrizMapa[i][j]);
                if (tanque != nullptr) {
                    QColor color = Qt::blue;  // Color por defecto

                    // Selecciona el color del tanque según su tipo
                    switch (tanque->getColor()) {
                        case Tanque::Color::ROJO:
                            color = Qt::red;
                        break;
                        case Tanque::Color::AZUL:
                            color = Qt::blue;
                        break;
                        case Tanque::Color::AMARILLO:
                            color = Qt::yellow;
                        break;
                        case Tanque::Color::CELESTE:
                            color = Qt::cyan;
                        break;
                    }

                    // Dibujar el tanque con el color correspondiente
                    cell->setBrush(color);
                }
            }
        }
    }

    // Forzar la actualización de la vista para reflejar los cambios
    view->update();
    scene->update();
}

/**
 * Fuerza la actualización de la vista y la escena.
 */
void MainWindow::forzarActualizacion() {
    view->update();
    scene->update();
}

/**
 * Maneja los eventos de clic del ratón para seleccionar tanques o destinos.
 * @param event Evento del clic del ratón.
 */
void MainWindow::mousePressEvent(QMouseEvent* event) {
    if (enMovimiento) return;

    int cellSize = 50;
    QPointF scenePos = view->mapToScene(event->pos());
    int x = static_cast<int>(scenePos.x()) / cellSize;
    int y = static_cast<int>(scenePos.y()) / cellSize;

    if (x >= 0 && x < SIZE && y >= 0 && y < SIZE) {
        if (typeid(*mapa->matrizMapa[y][x]) == typeid(Tanque)) {
            emit tanqueSeleccionadoSignal(x, y);
        } else if (typeid(*mapa->matrizMapa[y][x]) == typeid(Suelo)) {
            emit destinoSeleccionadoSignal(x, y);
        }
    }
}
