//
// Created by mvasquezr on 9/28/24.
//
#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>
#include "../Mapa/Mapa.h"

class MapWidget : public QWidget {
    Q_OBJECT

public:
    explicit MapWidget(Mapa *mapa, QWidget *parent = nullptr);
    ~MapWidget() override;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Mapa *mapa;
};

#endif // MAPWIDGET_H
