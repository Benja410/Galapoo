#include "../include/enemigo.hpp"
#include <vector>

enemigo::enemigo(float x, float y, const sf::Texture& textura){
    sprite.setTexture(textura);
    sprite.setPosition(x, y);
    velocidad = 4.0f; //Definimos la velocidad de movimiento del jugador
    direccion = 1; //Definimos hacia donde se mueve el enemigo (1 derecha -1 Izquierda)
    vida = 2; //Definimos la vida del enemigo
}

std::vector<enemigo> listaEnemigos;

void enemigo::actualizar(){
    sprite.move(velocidad*direccion, 0.f); //Movemos al enemigo hacia abajo
    sf::Vector2f posicion = sprite.getPosition(); //Obtenemos la posición actual del enemigo
    float anchoEnemigo = sprite.getGlobalBounds().width;

    if(posicion.x + anchoEnemigo >= 1080){
        direccion = -1;
        sprite.move(0.f, 20.f);
    }
    else if(posicion.x <= 0){
        direccion = 1;
        sprite.move(0.f, 20.f);
    }
    if(posicion.y > 300){ //Verificamos que el enemigo no se salga por abajo
        sprite.setPosition(posicion.x, - anchoEnemigo); //Si el enemigo sale por abajo, lo reposicionamos en la parte superior de la ventana
    }

}

void enemigo::dibujar(sf::RenderWindow& ventana){
    ventana.draw(sprite);
}

sf::FloatRect enemigo::hitbox() const{
    return sprite.getGlobalBounds();
}