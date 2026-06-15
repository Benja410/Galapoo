#pragma once
#include <SFML/Graphics.hpp>

class bala{
    private:
        sf::CircleShape bullet;
        float velocidad;
    
    public:
        bala(float x, float y);
        void actualizar();
        void dibujar(sf::RenderWindow& ventana);

        bool outVentana() const;

};