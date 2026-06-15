#pragma once
#include <SFML/Graphics.hpp>

class bala{ //Definimos la clase bala
    private:
        sf::CircleShape bullet; //Forma de la bala, en este caso circular
        float velocidad; //Velocidad de la bala
    
    public:
        bala(float x, float y); //Constructor para la clase bala
        void actualizar(); //Función para actualizar la posicion de la bala
        void dibujar(sf::RenderWindow& ventana); //Función para dibujar la bala en la ventana

        bool outVentana() const; //Booleano que verifica si la bala sale de la ventana.

};