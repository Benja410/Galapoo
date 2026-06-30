#include "../include/balaEnemiga.hpp"

balaEnemiga::balaEnemiga(float x, float y) : bala(x, y){
    bullet.setTexture(nullptr);

    bullet.setRadius(6.f);
    bullet.setFillColor(sf::Color::Yellow);
    bullet.setPosition(x,y);
    velocidad = 5.0f;
}

void balaEnemiga::actualizar(){
    bullet.move(0.f, velocidad);
}

bool balaEnemiga::outVentana() const{
    return bullet.getPosition().y > 720.f;
}

sf::FloatRect balaEnemiga::hitbox() const{
    return bullet.getGlobalBounds();
}

void balaEnemiga::dibujar(sf::RenderWindow& ventana){
    ventana.draw(bullet);
}