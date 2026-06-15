#include "../include/jugador.hpp"

Jugador::Jugador(float x, float y){
    forma.setSize(sf::Vector2f(50.f, 50.f)); //Definimos el tamaño del jugador
    forma.setFillColor(sf::Color::Cyan); //Definimos el color del jugador
    forma.setPosition(x, y); //Posicionamos al jugador en la ventana
    velocidad = 5.0f; //Definimos la velocidad de movimiento del jugador
}

void Jugador::actualizar(){

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        forma.move(-velocidad, 0.f); //Movemos al jugador hacia la izquierda
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        forma.move(velocidad, 0.f); //Movemos al jugador hacia la derecha
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        forma.move(0.f, -velocidad); //Movemos al jugador hacia arriba
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        forma.move(0.f, velocidad); //Movemos al jugador hacia abajo
    }

    sf::Vector2f posicion = forma.getPosition(); //Obtenemos la posición actual del jugador
    if(posicion.x < 0){ //Verificamos que el jugador no se salga por la izquierda
        forma.setPosition(0, posicion.y);
    }
    else if(posicion.x + forma.getSize().x > 1080){ //Verificamos que el jugador no se salga por la derecha
        forma.setPosition(1080 - forma.getSize().x, posicion.y);
    }
    if(posicion.y < 0){ //Verificamos que el jugador no se salga por arriba
        forma.setPosition(posicion.x, 0);
    }
    else if(posicion.y + forma.getSize().y > 720){ //Verificamos que el jugador no se salga por abajo
        forma.setPosition(posicion.x, 720 - forma.getSize().y);
    }

}

void Jugador::dibujar(sf::RenderWindow& ventana){
    ventana.draw(forma); //Dibujamos al jugador en la ventana
}
