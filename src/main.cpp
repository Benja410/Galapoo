#include <SFML/Graphics.hpp>
#include <iostream>
#include "jugador.hpp"

enum EstadoJuego{ //Definimos los estados del juego
    MENU,
    JUGANDO,
    PAUSA,
    GAMEOVER
};

int main(){

    sf::RenderWindow window(sf::VideoMode(1080, 720), "Galapoo - Proyecto ELO329"); //Definimos el tamaño de la ventana y el titulo de esta
    window.setFramerateLimit(60); // Fijamos los fps a 60

    EstadoJuego estadoActual = MENU; // Inicializamos el estado del juego en el menú
    sf::Font font; //Cargamos la fuente para el texto del menú

    if(!font.loadFromFile("../assets/ARCADE_I.TTF")){ //Debugger para verificar que la fuente se cargue
        std::cout << "Error al cargar la fuente" << std::endl;
        return -1;
    }

    sf::Text textoTitulo("GALAPOO", font, 80); //Definimos el titulo del menu, junto a su fuente y tamaño
    textoTitulo.setFillColor(sf::Color::White); // Definimos el color del texto del titulo
    textoTitulo.setPosition(275, 100); // Posicionamos el texto del titulo en la ventana, para que quede centrado

    sf::Text textoInstruccion("Presiona ENTER para jugar", font, 30); //Definimos el texto de instruccion para el menu, junto a su fuente y tamaño
    textoInstruccion.setFillColor(sf::Color::Green); //Color del texto de instruccion
    textoInstruccion.setPosition(190, 200); // Posicionamos el texto de instruccion debajo del titulo, para que quede centrado

    Jugador miNave(375.f, 500.f); //Creamos una instancia de la clase Jugador para representar la nave del jugador, posicionada inicialmente en el centro inferior de la ventana

    while(window.isOpen()){ // Bucle principal del juego
        sf::Event event; // Variable para almacenar los eventos de la ventana

        while(window.pollEvent(event)){ // Bucle para manejar los eventos de la ventana
            if(event.type == sf::Event::Closed){ //Debugger para verificar que la ventana se cierre correctamente
                window.close();
            }
            
            if(event.type == sf::Event::KeyPressed){ // Manejamos los eventos de teclado para cambiar entre estados del juego
                if(estadoActual == MENU && event.key.code == sf::Keyboard::Enter){ //Debugger para verificar que se presione la tecla correcta
                    estadoActual = JUGANDO;
                }
                else if(estadoActual == JUGANDO && event.key.code == sf::Keyboard::Escape){ //Boton "emergencia" para volver al menu desde el juego
                    estadoActual = MENU;
                }
            }
        }

        if(estadoActual == JUGANDO){ // Actualizamos la lógica del juego solo si estamos en el estado de JUGANDO
            miNave.actualizar(); // Actualizamos la posición del jugador según las teclas presionadas
        }

        window.clear(sf::Color::Black); // Limpiamos la ventana con un color de fondo
        
        if (estadoActual == MENU){ // Aquí se pueden agregar animaciones o efectos para el menú
            window.draw(textoTitulo);
            window.draw(textoInstruccion); 
        }
        else if (estadoActual == JUGANDO){ // Aquí se pueden agregar los elementos gráficos del juego.
            sf::RectangleShape naveTemporal(sf::Vector2f(50, 50)); //Nave temporal para el testeo incial
            naveTemporal.setFillColor(sf::Color::Cyan); //Color de la nave temporal
            naveTemporal.setPosition(100, 100); //Posicionamos la nave temporal en la ventana, para que quede visible y podamos verificar que se dibuje correctamente
            window.draw(naveTemporal); //Dibujamos la nave temporal en la ventana
            miNave.dibujar(window); // Dibujamos al jugador en la ventana
        }

        window.display(); // Mostramos el contenido de la ventana después de dibujar los elementos correspondientes al estado actual del juego
        
    }
    return 0;
    
}