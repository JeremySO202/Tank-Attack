//
// Created by mvasquezr on 9/28/24.
//
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QPushButton>
#include "../Mapa/Mapa.h"
#include "../Game/GameManager.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QGraphicsScene* scene;
    QGraphicsView* view;
    QLabel* informacionLabel; // Label para mostrar la información del juego
    GameManager* gameManager;
    QString powerUpActivo;

public:
    Mapa* mapa;
    bool enMovimiento;

    explicit MainWindow(Mapa* mapa, GameManager* gameManager, QWidget* parent = nullptr);
    void inicializarMapa(Mapa* mapa);
    void pintarBala(int x, int y, int oldX, int oldY);
    void actualizarTanque(int x, int y);
    void forzarActualizacion();
    void actualizarInformacionJuego(Jugador* jugadorActual, int tiempoRestante);
    void setPowerUpActivo(const QString& powerUp);
    void limpiarPowerUpActivo();



protected:
    void mousePressEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

signals:
    void tanqueSeleccionadoSignal(int x, int y);
    void destinoSeleccionadoSignal(int x, int y);
    void disparoSeleccionadoSignal(int x, int y);
    void usarPowerUpSignal();
    void movimientoFinalizado();
};

#endif // MAINWINDOW_H
