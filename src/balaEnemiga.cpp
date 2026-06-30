#include "../include/balaEnemiga.hpp"

balaEnemiga::balaEnemiga(float x, float y) : bala(x, y){
    bullet.setFillColor(sf::Color::Yellow);
}

void balaEnemiga::actualizar(){
    bullet.move(0.f, velocidad);
}

bool balaEnemiga::outVentana() const{
    return bullet.getPosition().y > 720.f;
}