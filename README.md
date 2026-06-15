# Galaga C++ - Proyecto de Programación Orientada a Objetos

Un clon simplificado del clásico juego arcade **Galaga**, desarrollado en C++ utilizando la librería gráfica multimedia **SFML**. 

Este proyecto fue construido con un enfoque estricto en la **Programación Orientada a Objetos (POO)**, aplicando conceptos fundamentales como la encapsulación, herencia, y el uso de máquinas de estado para el flujo del programa.

## Características

* **Arquitectura basada en Clases:** Diseño modular que separa la lógica del juego, la renderización y la gestión de eventos.
* **Máquina de Estados:** Gestión fluida entre la Pantalla de Inicio, el Bucle de Juego y (próximamente) la pantalla de Game Over.
* **Gráficos en 2D:** Renderizado optimizado a 60 FPS mediante aceleración por hardware con SFML.
* **Gestión de Recursos:** Carga segura de fuentes y texturas mediante rutas relativas.

## Tecnologías y Requisitos

Para compilar y ejecutar este proyecto, necesitas tener instalados los siguientes componentes:

* **Compilador C++**: Con soporte para el estándar C++17 o superior.
* **CMake**: Versión 3.10 o superior (Sistema de construcción multiplataforma).
* **SFML**: Versión 2.5 o superior (Simple and Fast Multimedia Library).

### Instalación de dependencias (Linux / Fedora)

Si estás utilizando un entorno basado en RPM como Fedora, puedes instalar todas las herramientas necesarias ejecutando:

```bash
sudo dnf install gcc-c++ cmake SFML-devel
```

(Para Windows o macOS, asegúrate de tener configurado MinGW o el compilador correspondiente y las variables de entorno de SFML).

## Compilación y Ejecución

El proyecto utiliza CMake para generar los archivos de construcción (Makefiles). Sigue estos pasos desde la raíz del proyecto para compilarlo de forma limpia sin ensuciar el código fuente:

    Crea un directorio para la compilación:
    Bash

    mkdir build
    cd build

    Genera los archivos de construcción con CMake:
    Bash

    cmake ..

    Compila el ejecutable:
    Bash

    make

    Ejecuta el juego:
    Bash

    ./Galaga

## Estructura del Proyecto

El código fuente está organizado de la siguiente manera para mantener una separación clara de responsabilidades:
Plaintext

GalagaOOP/
├── assets/           # Recursos multimedia (fuentes .ttf, sprites .png)
├── include/          # Archivos de cabecera (.hpp / .h) - Declaración de clases
├── src/              # Archivos de código fuente (.cpp) - Implementación
│   └── main.cpp      # Punto de entrada y Máquina de Estados principal
├── CMakeLists.txt    # Configuración de compilación para CMake
└── README.md         # Documentación del proyecto

## Controles del Juego

    ENTER: Iniciar el juego desde el menú principal.

    ESC: Volver al menú de inicio.

    (Próximamente) Flechas Direccionales: Mover la nave del jugador.

    (Próximamente) Espacio: Disparar láseres.

## Autores

    [Tu Nombre/Usuario]

    [Nombre de tu Compañero/Usuario]

Desarrollado para el ramo de programación y diseño de software.