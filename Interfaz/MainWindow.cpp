//
// Created by mvasquezr on 9/28/24.
//
#include "MainWindow.h"
#include <QGraphicsRectItem>
#include <QBrush>
#include <QMouseEvent>
#include <QTimer>
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
    setCentralWidget(view);

    inicializarMapa(mapa);
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
void MainWindow::actualizarTanque(int x, int y) {
    // Eliminar el tanque gráfico anterior si existe
    if (tanqueItem != nullptr) {
        scene->removeItem(tanqueItem);
        delete tanqueItem;
        tanqueItem = nullptr;
    }

    int cellSize = 50;

    // Obtener el tanque de la matriz del mapa
    Tanque* tanque = dynamic_cast<Tanque*>(mapa->matrizMapa[y][x]);
    if (tanque != nullptr) {
        QColor color = Qt::blue;  // Valor por defecto

        // Seleccionar el color del tanque según su tipo
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

        // Crear el tanque gráfico con el color correspondiente
        tanqueItem = scene->addRect(x * cellSize, y * cellSize, cellSize, cellSize, QPen(Qt::black), QBrush(color));
    }
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
