//
// Created by mvasquezr on 9/28/24.
//

#include "MainWindow.h"
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), gameWindow(nullptr) {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    playButton = new QPushButton("Jugar", this);
    exitButton = new QPushButton("Salir", this);

    layout->addWidget(playButton);
    layout->addWidget(exitButton);

    connect(playButton, &QPushButton::clicked, this, &MainWindow::onPlayButtonClicked);
    connect(exitButton, &QPushButton::clicked, this, &MainWindow::onExitButtonClicked);

    setWindowTitle("Menú Principal");
    resize(300, 200);
}

void MainWindow::onPlayButtonClicked() {
    if (!gameWindow) {
        gameWindow = new GameWindow(this);
    }
    gameWindow->show();
    this->hide();
}

void MainWindow::onExitButtonClicked() {
    close();
}
