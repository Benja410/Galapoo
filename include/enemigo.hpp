#pragma once
#include <SFML/Graphics.hpp>


class enemigo{
    protected:
        sf::Sprite sprite; //Forma del jugador
        float velocidad; //Velocidad de movimiento del jugador
        int direccion; 

    public:
        int vida;
        enemigo(float x, float y, const sf::Texture& textura); //Constructor de la clase jugador

        virtual ~enemigo() = default; //Destructor virtual
        virtual void actualizar();//Función virtual para actualizar la posición del jugador
        virtual void dibujar(sf::RenderWindow& ventana); //Función virtual para dibujar al jugador en la ventana    
        sf::FloatRect hitbox() const;
        
};