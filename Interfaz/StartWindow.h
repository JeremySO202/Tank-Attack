//
// Created by mvasquezr on 10/4/24.
//
#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QApplication>
#include "../Game/GameController.h"


class StartWindow : public QWidget {
    Q_OBJECT

public:
    explicit StartWindow(QWidget* parent = nullptr);

    private slots:
    void onJugarClicked();
    void onSalirClicked();

private:
    QPushButton* jugarButton;
    QPushButton* salirButton;
};

#endif // STARTWINDOW_H
