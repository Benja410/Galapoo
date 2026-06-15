#include "../include/enemigo.hpp"
#include <vector>

enemigo::enemigo(float x, float y){
    forma.setSize(sf::Vector2f(40.f, 40.f)); //Definimos el tamaño del jugador
    forma.setFillColor(sf::Color::Red); //Definimos el color del jugador
    forma.setPosition(x, y); //Posicionamos al jugador en la ventana
    velocidad = 4.0f; //Definimos la velocidad de movimiento del jugador
    direccion = 1; //Definimos hacia donde se mueve el enemigo (1 derecha -1 Izquierda)
    vida = 2; //Definimos la vida del enemigo
}

std::vector<enemigo> listaEnemigos;

void enemigo::actualizar(){
    forma.move(velocidad*direccion, 0.f); //Movemos al enemigo hacia abajo
    sf::Vector2f posicion = forma.getPosition(); //Obtenemos la posición actual del enemigo
    
    if(posicion.x + forma.getSize().x >= 1080){
        direccion = -1;
        forma.move(0.f, 20.f);
    }
    else if(posicion.x <= 0){
        direccion = 1;
        forma.move(0.f, 20.f);
    }
    if(posicion.y > 300){ //Verificamos que el enemigo no se salga por abajo
        forma.setPosition(posicion.x, -forma.getSize().y); //Si el enemigo sale por abajo, lo reposicionamos en la parte superior de la ventana
    }

}

void enemigo::dibujar(sf::RenderWindow& ventana){
    ventana.draw(forma);
}

sf::FloatRect enemigo::hitbox() const{
    return forma.getGlobalBounds();
}