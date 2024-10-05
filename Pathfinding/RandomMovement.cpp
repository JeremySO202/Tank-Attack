//
// Created by mvasquezr on 10/4/24.
//

// RandomMovement.cpp
#include "RandomMovement.h"

/**
 * Constructor que inicializa el generador de números aleatorios.
 */
RandomMovement::RandomMovement() {
    std::srand(static_cast<unsigned int>(std::time(0)));
}

/**
 * Obtiene una ruta de movimiento aleatorio desde la posición inicial.
 * @param xi Coordenada x inicial.
 * @param yi Coordenada y inicial.
 * @param mapa Puntero al mapa.
 * @param radio Radio dentro del cual se puede mover.
 * @return Ruta de movimiento aleatorio.
 */
Ruta* RandomMovement::obtenerMovimientoAleatorio(int xi, int yi, Mapa* mapa, int radio) {
    Ruta* ruta = new Ruta();

    // Generar un movimiento aleatorio en el radio definido
    for (int intento = 0; intento < 2; intento++) {
        int newX = xi + (std::rand() % (2 * radio + 1)) - radio;
        int newY = yi + (std::rand() % (2 * radio + 1)) - radio;

        // Verificar que las coordenadas estén dentro de los límites del mapa y sean navegables
        if (mapa->isValid(newX, newY)) {
            ruta->add(new Nodo(newX, newY));
            return ruta;
        }
    }

    // Si no encontró una posición válida, se mueve hacia la línea de vista hasta donde sea posible
    int stepX = (xi < radio) ? 1 : (xi > radio) ? -1 : 0;
    int stepY = (yi < radio) ? 1 : (yi > radio) ? -1 : 0;

    // Avanzar en la dirección hasta donde sea posible
    int currentX = xi + stepX;
    int currentY = yi + stepY;
    while (mapa->isValid(currentX, currentY)) {
        ruta->add(new Nodo(currentX, currentY));
        currentX += stepX;
        currentY += stepY;
    }

    return ruta;
}
