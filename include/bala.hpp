#pragma once
#include <SFML/Graphics.hpp>

class bala{ //Definimos la clase bala
    protected:
        sf::CircleShape bullet; //Forma de la bala, en este caso circular
        float velocidad; //Velocidad de la bala
    
    public:
        bala(float x, float y); //Constructor para la clase bala
        virtual ~bala() = default;

        virtual void actualizar(); //Función para actualizar la posicion de la bala
        virtual bool outVentana() const; //Booleano que verifica si la bala sale de la ventana.
        
        void dibujar(sf::RenderWindow& ventana); //Función para dibujar la bala en la ventana
        sf::FloatRect hitbox() const; //Función para obtener la hitbox de la bala

};