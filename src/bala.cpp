#include "../include/bala.hpp"

bala::bala(float x, float y){
    bullet.setRadius(8.f);
    bullet.setFillColor(sf::Color::Magenta);
    bullet.setPosition(x,y);
    velocidad = 10.0f;
}

void bala::actualizar(){
    bullet.move(0.f, -velocidad);
}

void bala::dibujar(sf::RenderWindow& ventana){
    ventana.draw(bullet);
}

bool bala::outVentana() const {
    return (bullet.getPosition().y + (bullet.getRadius() * 2) < 0);
}