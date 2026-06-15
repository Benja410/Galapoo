#pragma once
#include <SFML/Graphics.hpp>

class Jugador{
    private:
        sf::RectangleShape forma; //Forma del jugador, en este caso un rectángulo
        float velocidad; //Velocidad de movimiento del jugador

    public:
        Jugador(float x, float y); //Constructor de la clase jugador
        void actualizar(); //Función para actualizar la posición del jugador
        void dibujar(sf::RenderWindow& ventana); //Función para dibujar al jugador en la ventana    

};