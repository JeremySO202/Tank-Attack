#include <iostream>
#include <QApplication>
#include <QPushButton>

#include "Mapa.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    QPushButton button("Pruebas!", nullptr);
    Mapa *mapa = new Mapa();
    button.resize(200, 100);
    button.show();
    return QApplication::exec();

}
