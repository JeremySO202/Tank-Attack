# Tank Attack!

'Tank Attack!' es un juego de estrategia por turnos desarrollado en C++, donde los jugadores controlan tanques en un mapa. Usando algoritmos de pathfinding y power-ups, deben moverse, atacar y vencer al oponente. El juego incluye una interfaz gráfica creada con Qt para una experiencia más interactiva.

## Tabla de Contenidos
1. [Descripción del Proyecto](#descripción-del-proyecto)
2. [Funcionalidades](#funcionalidades)
3. [Instalación](#instalación)

## Descripción del Proyecto

'Tank Attack!' ofrece un entorno de estrategia por turnos en el que cada jugador controla múltiples tanques. El objetivo es emplear algoritmos de movimiento y power-ups para destruir los tanques enemigos. Los tanques se desplazan utilizando BFS, Dijkstra, o movimientos aleatorios según las circunstancias. Además, la interfaz gráfica permite una interacción fácil y visualmente atractiva, mostrando el mapa, los tanques y sus acciones.

## Funcionalidades

- **Algoritmos de Pathfinding**: Implementación de algoritmos como Dijkstra, BFS y movimientos aleatorios para navegar el mapa, además de A* para guiar los disparos.
- **Interfaz Gráfica**: Desarrollada con Qt, facilita la visualización del mapa, los tanques, y el sistema de turnos, permitiendo a los jugadores interactuar de forma intuitiva.
- **Power-Ups**: Los jugadores reciben power-ups de manera aleatoria que otorgan ventajas estratégicas, como movimientos más precisos, turnos extra, o mayor poder de ataque.
- **Gestión de Turnos**: Un sistema que coordina los turnos de cada jugador, asegurando el cumplimiento de las reglas del juego.

## Instalación

> **Nota**: Este proyecto se desarrolló en Linux, utilizando Clion.

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

    - En Windows, descarga e instala CMake y Qt desde [CMake](https://cmake.org/download/) y [Qt](https://www.qt.io/download), junto con un compilador como MinGW.

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

