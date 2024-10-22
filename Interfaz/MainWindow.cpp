//
// Created by mvasquezr on 9/28/24.
//
#include "MainWindow.h"
#include"../Game/PowerUp.h"
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QBrush>
#include <QMouseEvent>
#include <QTimer>
#include <QVBoxLayout>
#include <QKeyEvent>
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
    : QMainWindow(parent), mapa(mapa), gameManager(gameManager), enMovimiento(false)
{
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
    resize(870, 870);
}

/**
 * Actualiza la información del turno del jugador y el tiempo restante.
 * @param jugadorActual Puntero al jugador actual.
 * @param tiempoRestante Tiempo restante en segundos.
 */
void MainWindow::actualizarInformacionJuego(Jugador* jugadorActual, int tiempoRestante)
{
    QString info = QString("Turno: jugador %1\nTiempo restante: %2 segundos")
                   .arg(jugadorActual->getId())
                   .arg(tiempoRestante);

    // Información de los power-ups
    QString powerUpsInfo = "\nPower-Ups: ";
    int powerUpCount = 0;
    PowerUp* const* powerUps = jugadorActual->getPowerUps(powerUpCount); // Obtener la lista y el número de power-ups

    for (int i = 0; i < powerUpCount; ++i) {
        if (powerUps[i]) {
            powerUpsInfo += QString::fromStdString(powerUps[i]->getTipoString()) + ", " + " ";
        }
    }

    // Concatenar la información general y de power-ups
    info += powerUpsInfo;
    informacionLabel->setText(info);
}

/**
 * Inicializa el mapa dibujando cada celda.
 * @param mapa Puntero al objeto Mapa.
 */
void MainWindow::inicializarMapa(Mapa* mapa)
{
    int cellSize = 50;

    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            // Verifica si la celda es un tanque
            if (typeid(*mapa->matrizMapa[i][j]) == typeid(Tanque))
            {
                Tanque* tanque = dynamic_cast<Tanque*>(mapa->matrizMapa[i][j]);
                if (tanque != nullptr)
                {
                    QPixmap pixmap;
                    switch (tanque->getColor())
                    {
                    case Tanque::Color::ROJO:
                        pixmap = QPixmap(":/resources/red.png");
                        break;
                    case Tanque::Color::AZUL:
                        pixmap = QPixmap(":/resources/blue.png");
                        break;
                    case Tanque::Color::AMARILLO:
                        pixmap = QPixmap(":/resources/yellow.png");
                        break;
                    case Tanque::Color::CELESTE:
                        pixmap = QPixmap(":/resources/lightBlue.png");
                        break;
                    }
                    // Crear un fondo verde detrás del tanque
                    QGraphicsRectItem* background = scene->addRect(j * cellSize, i * cellSize, cellSize, cellSize);
                    background->setBrush(Qt::green);
                    background->setPen(Qt::NoPen);

                    // Crear un item gráfico para la imagen del tanque y colocarlo encima del fondo
                    QGraphicsPixmapItem* tanqueItem = new QGraphicsPixmapItem(pixmap.scaled(cellSize, cellSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
                    tanqueItem->setPos(j * cellSize, i * cellSize);
                    tanqueItem->setOpacity(1.0);
                    scene->addItem(tanqueItem);
                }
            }
            else
            {
                // Crear una celda normal usando QGraphicsRectItem
                QGraphicsRectItem* cell = scene->addRect(j * cellSize, i * cellSize, cellSize, cellSize);
                cell->setPen(Qt::NoPen); // Remover bordes para las celdas normales

                if (typeid(*mapa->matrizMapa[i][j]) == typeid(Indestructible))
                {
                    cell->setBrush(Qt::darkGray);
                }
                else if (typeid(*mapa->matrizMapa[i][j]) == typeid(Suelo))
                {
                    cell->setBrush(Qt::green);
                }
            }
        }
    }
}

void MainWindow::pintarBala(int x, int y, int oldX, int oldY){
    int cellSize = 50;
    QGraphicsRectItem* cell2 = scene->addRect(oldX * cellSize + cellSize/4, oldY * cellSize + cellSize/4, cellSize/4, cellSize/4);
    cell2->setBrush(Qt::magenta);
    QGraphicsRectItem* cell = scene->addRect(x * cellSize + cellSize/4, y * cellSize + cellSize/4, cellSize/4, cellSize/4);
    cell->setBrush(Qt::black);

    forzarActualizacion();
}

/**
 * Actualiza la posición del tanque en el mapa.
 * @param x Coordenada x.
 * @param y Coordenada y.
 */
void MainWindow::actualizarTanque(int nuevoX, int nuevoY)
{
    int cellSize = 50;

    // Actualizar toda la cuadrícula de nuevo para reflejar el estado actual
    scene->clear(); // Limpiamos toda la escena para asegurarnos de redibujarla correctamente

    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            // Verificar si es un tanque y agregar imagen
            if (typeid(*mapa->matrizMapa[i][j]) == typeid(Tanque))
            {
                Tanque* tanque = dynamic_cast<Tanque*>(mapa->matrizMapa[i][j]);
                if (tanque != nullptr)
                {
                    QPixmap pixmap;
                    switch (tanque->getColor())
                    {
                    case Tanque::Color::ROJO:
                        pixmap = QPixmap(":/resources/red.png");
                        break;
                    case Tanque::Color::AZUL:
                        pixmap = QPixmap(":/resources/blue.png");
                        break;
                    case Tanque::Color::AMARILLO:
                        pixmap = QPixmap(":/resources/yellow.png");
                        break;
                    case Tanque::Color::CELESTE:
                        pixmap = QPixmap(":/resources/lightBlue.png");
                        break;
                    }

                    // Crear un fondo verde detrás del tanque
                    QGraphicsRectItem* background = scene->addRect(j * cellSize, i * cellSize, cellSize, cellSize);
                    background->setBrush(Qt::green);
                    background->setPen(Qt::NoPen);

                    // Crear un item gráfico para la imagen del tanque y colocarlo encima del fondo
                    QGraphicsPixmapItem* tanqueItem = new QGraphicsPixmapItem(pixmap.scaled(cellSize, cellSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
                    tanqueItem->setPos(j * cellSize, i * cellSize);
                    tanqueItem->setOpacity(1.0);
                    scene->addItem(tanqueItem);
                }
            }
            else
            {
                // Dibujar las celdas normales
                QGraphicsRectItem* cell = scene->addRect(j * cellSize, i * cellSize, cellSize, cellSize);
                cell->setPen(Qt::NoPen);

                if (typeid(*mapa->matrizMapa[i][j]) == typeid(Indestructible))
                {
                    cell->setBrush(Qt::darkGray);
                }
                else if (typeid(*mapa->matrizMapa[i][j]) == typeid(Suelo))
                {
                    cell->setBrush(Qt::green);
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
void MainWindow::forzarActualizacion()
{
    view->update();
    scene->update();
}

/**
 * Maneja los eventos de clic del ratón para seleccionar tanques o destinos.
 * @param event Evento del clic del ratón.
 */
void MainWindow::mousePressEvent(QMouseEvent* event)
{
    if (enMovimiento) return;

    int cellSize = 50;
    QPointF scenePos = view->mapToScene(event->pos());
    int x = static_cast<int>(scenePos.x()) / cellSize;
    int y = static_cast<int>(scenePos.y()) / cellSize;

    if (x >= 0 && x < SIZE && y >= 0 && y < SIZE)
    {
        if (Qt::LeftButton == event->button() && typeid(*mapa->matrizMapa[y][x]) == typeid(Suelo))
        {
            emit destinoSeleccionadoSignal(x, y);
            return;
        }
        if (Qt::RightButton == event->button())
        {
            emit disparoSeleccionadoSignal(x, y);
            return;
        }
        if (typeid(*mapa->matrizMapa[y][x]) == typeid(Tanque))
        {
            emit tanqueSeleccionadoSignal(x, y);
        }
    }
}
/**
 * Maneja los eventos de teclas para activar power-ups.
 * @param event Evento de la tecla presionada.
 */
void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Shift) // Detectar la tecla "Shift"
    {
        emit usarPowerUpSignal(); // Emitir la señal para usar el power-up
    }
}