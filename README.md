# Galaga C++ - Proyecto de Programación Orientada a Objetos

Un clon simplificado del clásico juego arcade **Galaga**, desarrollado en C++ utilizando la librería gráfica multimedia **SFML**. 

Este proyecto fue construido con un enfoque estricto en la **Programación Orientada a Objetos (POO)**, aplicando conceptos fundamentales como la encapsulación, herencia, y el uso de máquinas de estado para el flujo del programa.

## Características

* **Arquitectura basada en Clases:** Diseño modular que separa la lógica del juego, la renderización y la gestión de eventos.
* **Herencia y Polimorfismo:** Enemigos estándar y un `jefeFinal` que heredan de una clase base `enemigo`, permitiendo comportamientos únicos y almacenamiento en un vector de punteros unificados.
* **Sistema de Niveles Dinámicos:** 5 niveles de dificultad progresiva con distintas formaciones geométricas y un combate contra un Jefe Final en el útlimo nivel.
* **Audio y Multimedia:** Renderizado optimizado a 60 FPS con texturas reales y efectos de sonidos espaciales (`sf::SoundBuffer` y `sf::Sound`)


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

    ./Galapoo

## Estructura del Proyecto

El código fuente está organizado de la siguiente manera para mantener una separación clara de responsabilidades:
Plaintext
```text
Galapoo/
├── assets/               # Recursos multimedia (.png, .ttf, .wav)
├── include/              # Cabeceras (.hpp) - Declaración de clases
│   ├── bala.hpp
│   ├── balaEnemiga.hpp
│   ├── enemigo.hpp
│   ├── explosion.hpp
│   ├── jefeFinal.hpp
│   └── jugador.hpp
├── src/                  # Código fuente (.cpp) - Implementación
│   ├── main.cpp          # Punto de entrada, gestor de niveles y Máquina de Estados
│   ├── ... (Archivos .cpp correspondientes a cada clase)
├── CMakeLists.txt        # Configuración de compilación para CMake
└── README.md             # Documentación del proyecto
```

## Controles del Juego

    Moverse: Flecha izquierda / Flecha Derecha

    Disparar: X

    Iniciar el Juego: ENTER

    Pausar: ESC (Durante la partida)

    Continuar: C (Durante el menu de pausa)

    Volver al Menú / Reiniciar: M (Desde la pausa o la pantalla de Game Over
    
## Link de video de presentación:
https://usmcl-my.sharepoint.com/:v:/g/personal/bsolisl_usm_cl/IQA4rsdwZrjVQ7GPyLj94M2nAWn70A_QNIAplofVcytNvRA?nav=eyJyZWZlcnJhbEluZm8iOnsicmVmZXJyYWxBcHAiOiJPbmVEcml2ZUZvckJ1c2luZXNzIiwicmVmZXJyYWxBcHBQbGF0Zm9ybSI6IldlYiIsInJlZmVycmFsTW9kZSI6InZpZXciLCJyZWZlcnJhbFZpZXciOiJNeUZpbGVzTGlua0NvcHkifX0&e=FtRWhl




    
