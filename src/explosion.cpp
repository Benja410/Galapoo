#include "../include/explosion.hpp"


Explosion::Explosion(float x, float y, const sf::Texture& textura){
    sprite.setTexture(textura);
    sprite.setScale(2.0f, 2.0f);
    frameActual = 0;
    totalFrames = 5;
    tiempoFrame = 0.06f;
    anchoFrame = 64;
    altoFrame = 64;
    terminada = false;

    sprite.setTextureRect(sf::IntRect(0,0,anchoFrame,altoFrame));
    sprite.setOrigin(anchoFrame / 2.f, altoFrame /2.f);
    sprite.setPosition(x, y);

}

void Explosion::actualizar(){
    if(terminada) return;

    if(relojFrame.getElapsedTime().asSeconds() >= tiempoFrame){
        frameActual ++;

        if(frameActual>= totalFrames){
            terminada = true;

        } else{
            sprite.setTextureRect(sf::IntRect(frameActual * anchoFrame, 0, anchoFrame, altoFrame));

        }
        relojFrame.restart();
    }
}

void Explosion::dibujar(sf::RenderWindow& ventana){
    if(!terminada){
        ventana.draw(sprite);
    }
}

bool Explosion::estaTerminada() const{
    return terminada;
}
