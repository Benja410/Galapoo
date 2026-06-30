#include "../include/jugador.hpp"
#include <iostream>

Jugador::Jugador(float x, float y, const sf::Texture& textura){
    sprite.setTexture(textura);
    sprite.setScale(1.5f, 1.5f);
    sprite.setPosition(x, y); //Posicionamos al jugador en la ventana
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
        sprite.move(-velocidad, 0.f); //Movemos al jugador hacia la izquierda
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        sprite.move(velocidad, 0.f); //Movemos al jugador hacia la derecha
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        sprite.move(0.f, -velocidad); //Movemos al jugador hacia arriba
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        sprite.move(0.f, velocidad); //Movemos al jugador hacia abajo
    }

    sf::Vector2f posicion = sprite.getPosition(); //Obtenemos la posición actual del jugador
    float anchoNave = sprite.getGlobalBounds().width; //Obtenemos el ancho del jugador
    float altoNave = sprite.getGlobalBounds().height;
    if(posicion.x < 0){ //Verificamos que el jugador no se salga por la izquierda
        sprite.setPosition(0, posicion.y);
    }
    else if(posicion.x + anchoNave > 1080){ //Verificamos que el jugador no se salga por la derecha
        sprite.setPosition(1080 - anchoNave, posicion.y);
    }
    if(posicion.y < 0){ //Verificamos que el jugador no se salga por arriba
        sprite.setPosition(posicion.x, 0);
    }
    else if(posicion.y + altoNave > 720){ //Verificamos que el jugador no se salga por abajo
        sprite.setPosition(posicion.x, 720 - altoNave);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::X)){
        if(relojDisparo.getElapsedTime().asSeconds() >= tiempoBullet){ //Si el tiempo entre balas es correcto, entonces creamos la bala
            float centroX = posicion.x + (anchoNave / 2) - 4.f; //Creamos la bala desde el centro del jugador
            float topeY = posicion.y; //Definimos el tope de la bala hacia arriba

            listaBala.push_back(bala(centroX, topeY)); //Si la bal asale de la ventana, la "matamos"
            sonidoDisparo.play(); //Reproducimos el sonido de disparo
            relojDisparo.restart();
        }
    }

}

void Jugador::reiniciar(){
    sprite.setPosition(375.f, 500.f); //Reiniciamos la posición del jugador al centro inferior de la ventana
    relojDisparo.restart(); //Reiniciamos el reloj de disparo para evitar que el jugador pueda disparar inmediatamente al reiniciar
}

void Jugador::dibujar(sf::RenderWindow& ventana){
    ventana.draw(sprite); //Dibujamos al jugador en la ventana
}

sf::FloatRect Jugador::hitbox() const{
    return sprite.getGlobalBounds(); //Obtenemos la hitbox del jugador
}