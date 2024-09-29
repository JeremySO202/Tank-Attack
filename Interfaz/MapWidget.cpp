//
// Created by mvasquezr on 9/28/24.
//
#include "MapWidget.h"
#include <QPainter>
#include "../Objetos/Indestructible.h"
#include "../Objetos/Suelo.h"
#include "../Objetos/Tanque.h"

MapWidget::MapWidget(Mapa *mapa, QWidget *parent) : QWidget(parent), mapa(mapa) {
    setFixedSize(1024, 768);
}

MapWidget::~MapWidget() {}

void MapWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (dynamic_cast<Indestructible*>(mapa->matrizMapa[i][j])) {
                painter.setBrush(Qt::darkGray);
                painter.drawRect(j * 50, i * 50, 50, 50);
            } else if (dynamic_cast<Suelo*>(mapa->matrizMapa[i][j])) {
                painter.setBrush(Qt::lightGray);
                painter.drawRect(j * 50, i * 50, 50, 50);
            } else if (dynamic_cast<Tanque*>(mapa->matrizMapa[i][j])) {
                painter.setBrush(Qt::red);
                painter.drawRect(j * 50, i * 50, 50, 50);
            }
        }
    }
}
