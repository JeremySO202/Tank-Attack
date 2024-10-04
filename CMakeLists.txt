cmake_minimum_required(VERSION 3.28.1)
project(Proyecto2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(Proyecto2 main.cpp
        Mapa/Mapa.cpp
        Objetos/Objeto.cpp
        Objetos/Objeto.h
        Objetos/Suelo.cpp
        Objetos/Suelo.h
        Objetos/Indestructible.cpp
        Objetos/Indestructible.h
        Objetos/Tanque.cpp
        Objetos/Tanque.h
        Pathfinding/Bfs.cpp
        Pathfinding/Bfs.h
        Pathfinding/Ruta.cpp
        Pathfinding/Ruta.h
        Pathfinding/Dijkstra.cpp
        Interfaz/MainWindow.cpp
        Interfaz/MainWindow.h
        Interfaz/MainWindow.h
        Interfaz/GameWindow.cpp
        Interfaz/GameWindow.h
        Interfaz/MapWidget.cpp
        Interfaz/MapWidget.h
        Interfaz/MapWidget.cpp
        Pathfinding/Astar.cpp
        Pathfinding/Astar.h
        Pathfinding/ListaPrioridad.cpp
        Pathfinding/ListaPrioridad.h)
target_link_libraries(Proyecto2
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)

