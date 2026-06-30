#pragma once
#include "enemigo.hpp"

class jefeFinal : public enemigo{
    public:
        jefeFinal(float x, float y, const sf::Texture& textura);

        void actualizar() override;
};