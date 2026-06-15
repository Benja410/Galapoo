#include <SFML/Graphics.hpp>
#include <iostream>

enum EstadoJuego{
    MENU,
    JUGANDO,
    PAUSA,
    GAMEOVER
};

int main(){

    sf::RenderWindow window(sf::VideoMode(1080, 720), "Galapoo - Proyecto ELO329");
    window.setFramerateLimit(60);

    EstadoJuego estadoActual = MENU;
    sf::Font font;

    if(!font.loadFromFile("../assets/ARCADE_I.TTF")){
        std::cout << "Error al cargar la fuente" << std::endl;
        return -1;
    }

    sf::Text textoTitulo("GALAPOO", font, 80);
    textoTitulo.setFillColor(sf::Color::White);
    textoTitulo.setPosition(275, 100);

    sf::Text textoInstruccion("Presiona ENTER para jugar", font, 30);
    textoInstruccion.setFillColor(sf::Color::Green);

    textoInstruccion.setPosition(190, 200);

    while(window.isOpen()){
        sf::Event event;

        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
            
            if(event.type == sf::Event::KeyPressed){
                if(estadoActual == MENU && event.key.code == sf::Keyboard::Enter){
                    estadoActual = JUGANDO;
                }
                else if(estadoActual == JUGANDO && event.key.code == sf::Keyboard::Escape){
                    estadoActual = MENU;
                }
            }
        }
        if(estadoActual == JUGANDO){
            // Aquí se pueden agregar las actualizaciones del juego, como movimiento de personajes, colisiones, etc.
        }

        window.clear(sf::Color::Black);
        
        if (estadoActual == MENU){ // Aquí se pueden agregar animaciones o efectos para el menú
            window.draw(textoTitulo);
            window.draw(textoInstruccion); 
        }
        else if (estadoActual == JUGANDO){
            sf::RectangleShape naveTemporal(sf::Vector2f(50, 50));
            naveTemporal.setFillColor(sf::Color::Cyan);
            naveTemporal.setPosition(100, 100);
            window.draw(naveTemporal);
        }

        window.display();
        
    }
    return 0;
    
}