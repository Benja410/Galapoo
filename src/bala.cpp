#include "../include/bala.hpp"

bala::bala(float x, float y){
    bullet.setRadius(8.f); //Definimos el tamaño de la bala 
    bullet.setFillColor(sf::Color::Magenta); //Definimos el color de la bala
    bullet.setPosition(x,y); //Posicionamos la bala en la ventana
    velocidad = 10.0f; //Definimos la velocidad de movimiento de la bala 
}

void bala::actualizar(){
    bullet.move(0.f, -velocidad);
}

void bala::dibujar(sf::RenderWindow& ventana){ //Funcion para dibujar la bala en la ventana
    ventana.draw(bullet);
}

bool bala::outVentana() const {
    return (bullet.getPosition().y + (bullet.getRadius() * 2) < 0);
}

sf::FloatRect bala::hitbox() const{
    return bullet.getGlobalBounds();
}