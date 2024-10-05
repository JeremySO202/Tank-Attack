
#include <QApplication>
#include "Game/GameController.h"
#include "Interfaz/StartWindow.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    StartWindow startWindow;
    startWindow.show();

    return a.exec();
}
