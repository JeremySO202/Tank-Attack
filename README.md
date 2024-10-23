# Tank Attack!

Este proyecto es sobre un juego de estrategia por turnos que estoy desarrollando en C++ llamado 'Tank Attack!'. En el juego, los jugadores controlan tanques en un mapa y usan diferentes algoritmos de pathfinding y power-ups para moverse, atacar, y vencer al oponente. También hice una interfaz gráfica usando la biblioteca Qt para que se vea más interactivo y fácil de jugar.

## Tabla de Contenidos
1. [Descripción del Proyecto](#descripción-del-proyecto)
2. [Funcionalidades](#funcionalidades)
3. [Instalación](#instalación)

## Descripción del Proyecto

'Tank Attack!' es un juego de estrategia por turnos donde cada jugador controla varios tanques. El objetivo es usar diferentes algoritmos de movimiento y power-ups estratégicos para derrotar a los tanques del oponente. Los tanques se mueven utilizando algoritmos como BFS, Dijkstra, o movimientos aleatorios, dependiendo de la situación, y hay power-ups que mejoran las habilidades de los tanques. El proyecto tiene una interfaz gráfica hecha con Qt para mostrar el mapa, los tanques y permitir que los jugadores interactúen fácilmente.

## Funcionalidades

- **Algoritmos de Pathfinding**: Implementación de algoritmos como Dijkstra, BFS y movimientos aleatorios para que los tanques puedan moverse por el mapa. Así como A* para los disparos.
- **Interfaz Gráfica**: Desarrollada con Qt, muestra el mapa, los tanques, los turnos, y permite que los jugadores interactúen fácilmente.
- **Power-Ups**: Los jugadores pueden recoger y usar power-ups que les dan ventajas, como movimientos más precisos, turnos adicionales, o ataques más fuertes.
- **Gestión de Turnos**: Un sistema de turnos que controla cuándo le toca jugar a cada jugador y asegura que se sigan las reglas del juego.

## Instalación

> **Nota**: Este proyecto se desarrolló en Linux, utilizado Clion.

Para instalar y ejecutar el juego, sigue estos pasos:

1. Clona el repositorio en tu máquina:

    ```bash
    git clone https://github.com/melivasr/TankAttack.git
    ```

2. Asegúrate de tener instalado CMake, Qt, y un compilador compatible con C++.

    - En Linux, puedes instalar CMake y Qt con:

    ```bash
    sudo apt-get install cmake qt5-default g++
    ```

    - En Windows, puedes descargar CMake y Qt desde [CMake](https://cmake.org/download/) y [Qt](https://www.qt.io/download). Instálalos junto con un compilador como MinGW.

3. Genera los archivos de compilación con CMake:

    ```bash
    cd TankAttack
    mkdir build
    cd build
    cmake ..
    ```

4. Compila el proyecto:

    ```bash
    make
    ```
