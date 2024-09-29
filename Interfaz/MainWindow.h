//
// Created by mvasquezr on 9/28/24.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "GameWindow.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    private slots:
        void onPlayButtonClicked();
    void onExitButtonClicked();

private:
    QPushButton *playButton;
    QPushButton *exitButton;
    GameWindow *gameWindow;
};

#endif // MAINWINDOW_H
