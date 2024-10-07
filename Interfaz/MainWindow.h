//
// Created by mvasquezr on 9/28/24.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "../Mapa/Mapa.h"
#include "../Game/GameManager.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    QGraphicsScene* scene;
    QGraphicsView* view;
    QGraphicsRectItem* tanqueItem = nullptr;
    GameManager* gameManager;

public:
    Mapa* mapa;
    bool enMovimiento;

    explicit MainWindow(Mapa* mapa, GameManager* gameManager, QWidget* parent = nullptr);
    void inicializarMapa(Mapa* mapa);
    void actualizarTanque(int x, int y);
    void forzarActualizacion();

protected:
    void mousePressEvent(QMouseEvent* event) override;

    signals:
        void tanqueSeleccionadoSignal(int x, int y);
    void destinoSeleccionadoSignal(int x, int y);
    void movimientoFinalizado();
};

#endif // MAINWINDOW_H
