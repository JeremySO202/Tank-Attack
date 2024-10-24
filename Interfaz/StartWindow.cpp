#include "StartWindow.h"
#include <QLabel>
#include <QPixmap>
#include <QFont>
#include <QStyle>

/**
 * Constructor de StartWindow.
 * Crea la interfaz de inicio con botones para jugar y salir.
 * @param parent Puntero al widget padre.
 */
StartWindow::StartWindow(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);

    // Crear un contenedor para la imagen de fondo
    QLabel* backgroundLabel = new QLabel(this);
    backgroundLabel->setPixmap(QPixmap(":/resources/start_background.png").scaled(600, 400, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
    backgroundLabel->setFixedSize(600, 400);
    backgroundLabel->setAlignment(Qt::AlignCenter);
    backgroundLabel->lower(); // Asegurarse de que la imagen esté detrás de otros widgets

    // Crear un título estilizado
    QLabel* titleLabel = new QLabel("Tank Attack", this);
    QFont titleFont("OCR A Extended", 28, QFont::Bold);
    titleLabel->setFont(titleFont);
    titleLabel->setStyleSheet("color: #ffffff; background-color: #4a4a4a; padding: 10px; border-radius: 15px;");
    titleLabel->setAlignment(Qt::AlignCenter);

    // Crear botones estilizados
    jugarButton = new QPushButton("Jugar", this);
    salirButton = new QPushButton("Salir", this);

    // Aplicar estilo CSS a los botones
    QString buttonStyle = R"(
        QPushButton {
            background-color: #4a4a4a;
            color: white;
            border-radius: 15px;
            font-size: 18px;
            padding: 10px 20px;
        }
        QPushButton:hover {
            background-color: #6e6e6e;
        }
        QPushButton:pressed {
            background-color: #2b2b2b;
        }
    )";
    jugarButton->setStyleSheet(buttonStyle);
    salirButton->setStyleSheet(buttonStyle);

    // Ajustar tamaño de la ventana
    setFixedSize(600, 400);

    // Espaciado y alineación
    layout->addStretch();
    layout->addWidget(titleLabel); // Agregar el título arriba
    layout->addStretch();
    layout->addWidget(jugarButton, 0, Qt::AlignCenter);
    layout->addSpacing(20);
    layout->addWidget(salirButton, 0, Qt::AlignCenter);
    layout->addStretch();

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
