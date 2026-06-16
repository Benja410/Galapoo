#include "../include/jugador.hpp"
#include <iostream>

Jugador::Jugador(float x, float y){
    forma.setSize(sf::Vector2f(50.f, 50.f)); //Definimos el tamaño del jugador
    forma.setFillColor(sf::Color::Cyan); //Definimos el color del jugador
    forma.setPosition(x, y); //Posicionamos al jugador en la ventana
    velocidad = 5.0f; //Definimos la velocidad de movimiento del jugador
    tiempoBullet = 0.3f; //Definimos el tiempo de disparo entre balas
    
    if (!bufferDisparo.loadFromFile("../assets/bala.wav")) {
        std::cerr << "Error al cargar el sonido bala.wav\n";
    }

    sonidoDisparo.setBuffer(bufferDisparo); //Asignamos el buffer al sonido de disparo
    sonidoDisparo.setVolume(50.f); //Ajustamos el volumen del sonido de disparo
}

void Jugador::actualizar(std::vector<bala>& listaBala){

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

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::X)){
        if(relojDisparo.getElapsedTime().asSeconds() >= tiempoBullet){ //Si el tiempo entre balas es correcto, entonces creamos la bala
            float centroX = (forma.getPosition().x) + (forma.getSize().x / 2) - 4.f; //Creamos la bala desde el centro del jugador
            float topeY = forma.getPosition().y; //Definimos el tope de la bala hacia arriba

            listaBala.push_back(bala(centroX, topeY)); //Si la bal asale de la ventana, la "matamos"
            sonidoDisparo.play(); //Reproducimos el sonido de disparo
            relojDisparo.restart();
        }
    }

}

void Jugador::reiniciar(){
    forma.setPosition(375.f, 500.f); //Reiniciamos la posición del jugador al centro inferior de la ventana
    relojDisparo.restart(); //Reiniciamos el reloj de disparo para evitar que el jugador pueda disparar inmediatamente al reiniciar
}

void Jugador::dibujar(sf::RenderWindow& ventana){
    ventana.draw(forma); //Dibujamos al jugador en la ventana
}

sf::FloatRect Jugador::hitbox() const{
    return forma.getGlobalBounds(); //Obtenemos la hitbox del jugador
}