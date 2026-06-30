#pragma once
#include "bala.hpp"

class balaEnemiga : public bala{

    public:
        balaEnemiga(float x, float y);
        void actualizar() override;
        bool outVentana() const override;
        void dibujar(sf::RenderWindow& ventana);
        sf::FloatRect hitbox() const;
};