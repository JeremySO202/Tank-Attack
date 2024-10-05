//
// Created by mvasquezr on 10/4/24.
//
#include "StartWindow.h"

/**
 * Constructor de StartWindow.
 * Crea la interfaz de inicio con botones para jugar y salir.
 * @param parent Puntero al widget padre.
 */
StartWindow::StartWindow(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);
    jugarButton = new QPushButton("Jugar", this);
    salirButton = new QPushButton("Salir", this);
    resize(400, 300);

    layout->addWidget(jugarButton);
    layout->addWidget(salirButton);
    setLayout(layout);

    connect(jugarButton, &QPushButton::clicked, this, &StartWindow::onJugarClicked);
    connect(salirButton, &QPushButton::clicked, this, &StartWindow::onSalirClicked);
}

/**
 * Maneja el clic en el botón "Jugar".
 * Inicia el juego.
 */
void StartWindow::onJugarClicked() {
    GameController* gameController = new GameController();
    gameController->iniciarJuego();
    close();
}

/**
 * Maneja el clic en el botón "Salir".
 * Cierra la aplicación.
 */
void StartWindow::onSalirClicked() {
    close();
    QApplication::quit();
}
