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

    // Coordenadas actuales del tanque
    int currentX = xi;
    int currentY = yi;

    // Generar una secuencia de movimientos dentro del radio definido
    for (int i = 0; i < radio; ++i) {
        // Seleccionar una dirección aleatoria de las 8 posibles
        int stepX = (std::rand() % 3) - 1;
        int stepY = (std::rand() % 3) - 1;

        // Asegurarse de que haya un movimiento
        while (stepX == 0 && stepY == 0) {
            stepX = (std::rand() % 3) - 1;
            stepY = (std::rand() % 3) - 1;
        }

        // Calcular la nueva posición
        int newX = currentX + stepX;
        int newY = currentY + stepY;

        // Verificar que las coordenadas estén dentro de los límites del mapa y sean navegables
        if (mapa->isValid(newX, newY)) {
            ruta->add(new Nodo(newX, newY));
            currentX = newX;
            currentY = newY;
        } else {
            i--;
        }
    }

    return ruta;
}

