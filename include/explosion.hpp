#pragma once
#include <SFML/Graphics.hpp>

class Explosion {
    private:
        sf::Sprite sprite;
        int frameActual;
        int totalFrames;
        sf::Clock relojFrame;
        float tiempoFrame;
        int anchoFrame;
        int altoFrame;
        bool terminada;
    
    public:
        Explosion(float x, float y, const sf::Texture& textura);

        void actualizar();
        void dibujar(sf::RenderWindow& ventana);
        bool estaTerminada() const;
};