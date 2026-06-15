#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "../include/bala.hpp"

class Jugador{
    private:
        sf::RectangleShape forma; //Forma del jugador, en este caso un rectángulo
        float velocidad; //Velocidad de movimiento del jugador

        sf::Clock relojDisparo;
        float tiempoBullet; //Tiempo de disparo

        sf::SoundBuffer bufferDisparo; //Buffer para el sonido de disparo
        sf::Sound sonidoDisparo; //Sonido de disparo

        public:
        Jugador(float x, float y); //Constructor de la clase jugador
        void actualizar(std::vector<bala>& listaBala);//Función para actualizar la posición del jugador
        void dibujar(sf::RenderWindow& ventana); //Función para dibujar al jugador en la ventana    

};