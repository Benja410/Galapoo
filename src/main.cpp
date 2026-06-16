#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include "jugador.hpp"
#include "bala.hpp"
#include "enemigo.hpp"

enum EstadoJuego{ //Definimos los estados del juego
    MENU,
    JUGANDO,
    PAUSA,
    GAMEOVER
};

int main(){

    sf::RenderWindow window(sf::VideoMode(1080, 720), "Galapoo - Proyecto ELO329"); //Definimos el tamaño de la ventana y el titulo de esta
    window.setFramerateLimit(60); // Fijamos los fps a 60

    EstadoJuego estadoActual = MENU; // Inicializamos el estado del juego en el menú
    sf::Font font; //Cargamos la fuente para el texto del menú

    if(!font.loadFromFile("../assets/ARCADE_I.TTF")){ //Debugger para verificar que la fuente se cargue
        std::cout << "Error al cargar la fuente" << std::endl;
        return -1;
    }

    //Definimos los textos para el menú, junto a su fuente, tamaño, color y posición
    sf::Text textoTitulo("GALAPOO", font, 80); //Definimos el titulo del menu, junto a su fuente y tamaño
    textoTitulo.setFillColor(sf::Color::White); // Definimos el color del texto del titulo
    textoTitulo.setPosition(275, 100); // Posicionamos el texto del titulo en la ventana, para que quede centrado
    sf::Text textoInstruccion("Presiona ENTER para jugar", font, 30); //Definimos el texto de instruccion para el menu, junto a su fuente y tamaño
    textoInstruccion.setFillColor(sf::Color::Green); //Color del texto de instruccion
    textoInstruccion.setPosition(190, 200); // Posicionamos el texto de instruccion debajo del titulo, para que quede centrado

    //Definimos los textos para la pausa, junto a su fuente, tamaño, color y posición
    sf::Text textoPausa("PAUSA", font, 100); //Definimos el texto de pausa, junto a su fuente y tamaño
    textoPausa.setFillColor(sf::Color::Yellow); // Definimos el color del texto de pausa
    textoPausa.setPosition(320, 100); // Posicionamos el texto de pausa en la ventana, para que quede centrado
    sf::Text textoPausaInstruccion("Presiona C para continuar", font, 30); //Definimos el texto de instruccion para la pausa, junto a su fuente y tamaño
    textoPausaInstruccion.setFillColor(sf::Color::Green); //Color del texto de instruccion para la pausa
    textoPausaInstruccion.setPosition(190, 350); // Posicionamos el texto de instruccion para la pausa debajo del texto de pausa

    //Definimos el texto de game over, junto a su fuente, tamaño, color y posición
    sf::Text textoGameOver("GAME OVER", font, 100); //Definimos el texto de game over, junto a su fuente y tamaño
    textoGameOver.setFillColor(sf::Color::Red); // Definimos el color del texto de game over
    textoGameOver.setPosition(110, 100); // Posicionamos el texto de game over en la ventana, para que quede centrado
    sf::Text textoReiniciar("Presiona M para volver al menu", font, 30); //Definimos el texto de instruccion para el menu, junto a su fuente y tamaño
    textoReiniciar.setFillColor(sf::Color::Green); //Color del texto de instruccion
    textoReiniciar.setPosition(120, 250);

    Jugador miNave(375.f, 500.f); //Creamos una instancia de la clase Jugador para representar la nave del jugador, posicionada inicialmente en el centro inferior de la ventana
    std::vector<bala> balas; //Creamos el vector "bala"
    
    //Generamos los enemigos
    std::vector<enemigo> listaEnemigo; //Creamos el vector para generar enemigos
    for(int i = 0; i < 6; i++){
        float posicionX = 0.f + (i * 70.f);
        float posicionY = 50.f;
        listaEnemigo.push_back(enemigo(posicionX, posicionY));//Agregamos enemigos a la lista de enemigos, posicionados en la parte superior de la ventana
    }
    
    //Cargamos el sonido de explosion
    sf::SoundBuffer bufferExplosion; //Buffer para el sonido de explosion
    sf::Sound sonidoExplosion; //Sonido de explosion
    if(!bufferExplosion.loadFromFile("../assets/explosion.wav")) {
        std::cerr << "Error al cargar el sonido explosion.wav\n";
    }
    sonidoExplosion.setBuffer(bufferExplosion);
    sonidoExplosion.setVolume(40.f); //Ajustamos el volumen del sonido de explosion

    while(window.isOpen()){ 
        sf::Event event; 

        while(window.pollEvent(event)){ 
            if(event.type == sf::Event::Closed){ 
                window.close();
            }
            
            if(event.type == sf::Event::KeyPressed){ 
                if(estadoActual == MENU && event.key.code == sf::Keyboard::Enter){ 
                    estadoActual = JUGANDO;
                }
                else if(estadoActual == JUGANDO && event.key.code == sf::Keyboard::Escape){ 
                    estadoActual = PAUSA;
                }
                else if(estadoActual == PAUSA && event.key.code == sf::Keyboard::C){ 
                    estadoActual = JUGANDO;
                }
                else if(estadoActual == PAUSA && event.key.code == sf::Keyboard::M){ 
                    miNave.reiniciar();
                    balas.clear(); 
                    listaEnemigo.clear(); 
                    
                    for(int i = 0; i < 6; i++){
                        float posicionX = 0.f + (i * 70.f);
                        float posicionY = 50.f;
                        listaEnemigo.push_back(enemigo(posicionX, posicionY)); 
                    }

                    estadoActual = MENU;
                }
                else if(estadoActual == GAMEOVER && event.key.code == sf::Keyboard::M){ 
                    miNave.reiniciar();
                    balas.clear(); 
                    listaEnemigo.clear(); 
                    
                    for(int i = 0; i < 6; i++){
                        float posicionX = 0.f + (i * 70.f);
                        float posicionY = 50.f;
                        listaEnemigo.push_back(enemigo(posicionX, posicionY)); 
                    }
                    
                    estadoActual = MENU; 
                }
            }
        }

        // ==========================================
        // ESTA ES LA SECCIÓN DE LÓGICA (ACTUALIZAR)
        // ==========================================
        if(estadoActual == JUGANDO){ 
            miNave.actualizar(balas); 

            for (size_t i = 0; i < balas.size(); i++){ 
                balas[i].actualizar();
            }

            for(size_t i = 0; i < listaEnemigo.size(); i++){
                listaEnemigo[i].actualizar();
            }

            // Limpieza de balas fuera de ventana
            for (int i = balas.size() - 1; i >= 0; i--){ 
                if(balas[i].outVentana()){
                    balas.erase(balas.begin() + i);
                }
            }

            // --- SE TRASLADARON LAS COLISIONES AQUÍ (ZONA DE LÓGICA) ---
            for(int i = listaEnemigo.size() - 1; i >= 0; i--){
                bool enemigoBorrado = false; // Bandera para saber si el enemigo murió

                // 1. Colisión Bala vs Enemigo
                for(int j = balas.size() - 1; j >= 0; j--){
                    if(listaEnemigo[i].hitbox().intersects(balas[j].hitbox())){ 
                        listaEnemigo[i].vida -= 1; 
                        
                        if(listaEnemigo[i].vida <= 0){ 
                            sonidoExplosion.play(); 
                            listaEnemigo.erase(listaEnemigo.begin() + i);
                            enemigoBorrado = true; // Marcamos que el enemigo ya no existe
                        }
                        balas.erase(balas.begin() + j);
                        break; // Salimos del bucle de balas
                    }
                }

                // 2. Colisión Nave vs Enemigo (SOLO si el enemigo sigue vivo)
                if (!enemigoBorrado) {
                    if(miNave.hitbox().intersects(listaEnemigo[i].hitbox())){ 
                        estadoActual = GAMEOVER;
                        break; // Salimos del bucle de enemigos porque el juego terminó
                    }
                }
            }
        }

        // ==========================================
        // ESTA ES LA SECCIÓN DE GRÁFICOS (DIBUJAR)
        // ==========================================
        window.clear(sf::Color::Black); 
        
        if (estadoActual == MENU){ 
            window.draw(textoTitulo);
            window.draw(textoInstruccion); 
        }
        else if (estadoActual == JUGANDO){ 
            miNave.dibujar(window); 
            
            for(size_t i = 0; i < balas.size(); i++){ 
                balas[i].dibujar(window);
            }

            for(size_t i = 0; i < listaEnemigo.size(); i++){
                listaEnemigo[i].dibujar(window);
            }
            // NOTA: Toda la lógica de colisiones fue removida de aquí para mantener limpio el renderizado
        }
        else if(estadoActual == PAUSA){
            window.draw(textoPausa);
            window.draw(textoPausaInstruccion);
            window.draw(textoReiniciar);
        }
        else if (estadoActual == GAMEOVER){ 
            window.draw(textoGameOver);
            window.draw(textoReiniciar);
        }
        
        window.display(); 
    }
    return 0;
}