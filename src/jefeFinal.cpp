#include "../include/jefeFinal.hpp"

jefeFinal::jefeFinal(float x, float y, const sf::Texture& textura) : enemigo(x,y, textura){
    vida = 50;
    velocidad = 6.0f;

    sprite.setScale(4.0f, 4.0f);

}

void jefeFinal::actualizar(){
    sprite.move(velocidad * direccion, 0.f);

    sf::Vector2f posicion = sprite.getPosition();
    float anchoJefe = sprite.getGlobalBounds().width;

    if(posicion.x + anchoJefe >= 1080){
        direccion = -1;
    }else if(posicion.x <= 0){
        direccion = 1;
    }

}