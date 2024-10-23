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
    informacionLabel->setWordWrap(true);


    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(view);
    layout->addWidget(informacionLabel);

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    inicializarMapa(mapa);
    resize(900, 900);
}

/**
 * Actualiza la información del turno del jugador y el tiempo restante.
 * @param jugadorActual Puntero al jugador actual.
 * @param tiempoRestante Tiempo restante en segundos.
 */
void MainWindow::actualizarInformacionJuego(Jugador* jugadorActual, int tiempoRestante)
{
    // Crear el contenedor de información estilizado
    QString info = QString(
        "<div style='background-color:#2B2B2B; color: #FFFFFF; border-radius: 10px; padding: 15px; font-family: Arial, sans-serif;'>"
        "<h2 style='font-size: 18px; text-align: center;'>Turno: Jugador %1</h2>"
        "<p style='font-size: 18px; text-align: center;'>Tiempo restante: <span style='color: #FF5722;'>%2 segundos</span></p>"
    ).arg(jugadorActual->getId()).arg(tiempoRestante);

    // Información de los power-ups
    QString powerUpsInfo = "<p style='font-size: 16px; text-align: center;'>Power-Ups: ";
    int powerUpCount = 0;
    PowerUp* const* powerUps = jugadorActual->getPowerUps(powerUpCount);

    if (powerUpCount > 0) {
        for (int i = 0; i < powerUpCount; ++i) {
            if (powerUps[i]) {
                powerUpsInfo += QString("<span style='color: #4CAF50;'>%1</span>, ")
                    .arg(QString::fromStdString(powerUps[i]->getTipoString()));
            }
        }
        powerUpsInfo.chop(2); // Eliminar la última coma y espacio
    } else {
        powerUpsInfo += "<span style='color: #CCCCCC;'>Ninguno</span>";
    }
    powerUpsInfo += "</p>";

    // Agregar información sobre el Power-Up activo, si hay uno
    if (!powerUpActivo.isEmpty()) {
        powerUpsInfo += QString(
            "<p style='font-size: 16px; text-align: center;'><strong>Usando Power-Up:</strong> <span style='color: #00CED1;'>%1</span></p>"
        ).arg(powerUpActivo);
    }

    // Concatenar la información general y de power-ups
    info += powerUpsInfo + "</div>";

    // Aplicar estilo al QLabel
    informacionLabel->setText(info);
    informacionLabel->setStyleSheet("QLabel { background-color: #2B2B2B; color: #FFFFFF; border-radius: 10px; padding: 15px; }");
    informacionLabel->setAlignment(Qt::AlignCenter);
}
void MainWindow::setPowerUpActivo(const QString& powerUp) {
    powerUpActivo = powerUp;
    actualizarInformacionJuego(gameManager->getJugadorActual(), 300); // Asegurar que se actualice la interfaz
}

void MainWindow::limpiarPowerUpActivo() {
    powerUpActivo = ""; // Limpiar el power-up activo
    actualizarInformacionJuego(gameManager->getJugadorActual(), 300); // Actualizar la interfaz
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
                    background->setBrush(QColor(119, 178, 85));
                    background->setPen(Qt::NoPen);

                    // Crear un item gráfico para la imagen del tanque y colocarlo encima del fondo
                    QGraphicsPixmapItem* tanqueItem = new QGraphicsPixmapItem(pixmap.scaled(cellSize, cellSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
                    tanqueItem->setPos(j * cellSize, i * cellSize);
                    tanqueItem->setOpacity(1.0);
                    scene->addItem(tanqueItem);
                }
            }
            else if (typeid(*mapa->matrizMapa[i][j]) == typeid(Indestructible))
            {
                // Usar imagen para Indestructible
                QPixmap pixmap(":/resources/obstaculo.jpeg");
                QGraphicsPixmapItem* obstaculoItem = new QGraphicsPixmapItem(pixmap.scaled(cellSize, cellSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
                obstaculoItem->setPos(j * cellSize, i * cellSize);
                scene->addItem(obstaculoItem);
            }
            else
            {
                // Crear una celda normal usando QGraphicsRectItem
                QGraphicsRectItem* cell = scene->addRect(j * cellSize, i * cellSize, cellSize, cellSize);
                cell->setPen(Qt::NoPen); // Remover bordes para las celdas normales

                if (typeid(*mapa->matrizMapa[i][j]) == typeid(Suelo))
                {
                    cell->setBrush(QColor(119, 178, 85));
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

void MainWindow::pintarRuta(Ruta *ruta){
    int cellSize = 50;
    Nodo * nodo = ruta->inicio;

    while (nodo->next != nullptr)
    {
        QGraphicsRectItem* cell2 = scene->addRect(nodo->x * cellSize , nodo->y * cellSize, cellSize, cellSize);
        cell2->setBrush(Qt::magenta);
        nodo = nodo->next;
    }
    forzarActualizacion();
}

/**
 * Actualiza la posición del tanque en el mapa.
 * @param x Coordenada x.
 * @param y Coordenada y.
 */
void MainWindow::actualizarTanque()
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
                    background->setBrush(QColor(119, 178, 85));
                    background->setPen(Qt::NoPen);

                    // Crear un item gráfico para la imagen del tanque y colocarlo encima del fondo
                    QGraphicsPixmapItem* tanqueItem = new QGraphicsPixmapItem(pixmap.scaled(cellSize, cellSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
                    tanqueItem->setPos(j * cellSize, i * cellSize);
                    tanqueItem->setOpacity(1.0);
                    scene->addItem(tanqueItem);
                }
            }
            // Verificar si es un objeto Indestructible y agregar imagen
            else if (typeid(*mapa->matrizMapa[i][j]) == typeid(Indestructible))
            {
                QPixmap pixmap(":/resources/obstaculo.jpeg");
                QGraphicsPixmapItem* obstaculoItem = new QGraphicsPixmapItem(pixmap.scaled(cellSize, cellSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
                obstaculoItem->setPos(j * cellSize, i * cellSize);
                scene->addItem(obstaculoItem);
            }
            else
            {
                // Dibujar las celdas normales
                QGraphicsRectItem* cell = scene->addRect(j * cellSize, i * cellSize, cellSize, cellSize);
                cell->setPen(Qt::NoPen);

                if (typeid(*mapa->matrizMapa[i][j]) == typeid(Suelo))
                {
                    cell->setBrush(QColor(119, 178, 85));
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