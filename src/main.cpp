#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "jugador.hpp"
#include "bala.hpp"
#include "enemigo.hpp"
#include "explosion.hpp"
#include "jefeFinal.hpp"
#include "balaEnemiga.hpp"


enum EstadoJuego{ //Definimos los estados del juego
    MENU,
    JUGANDO,
    PAUSA,
    GAMEOVER
};

void cargarNivel(int nivel, std::vector<enemigo*>& lista, const sf::Texture& texNormal, const sf::Texture& textJefe){
    for(size_t i = 0; i < lista.size(); i++){
        delete lista[i];
    }
    lista.clear();

    if(nivel == 1){
        for(int i = 0; i < 6; i++){
            lista.push_back(new enemigo(50.f + (i * 80.f), 50.f, texNormal));

        }
    }else if(nivel ==2){
        for(int fila = 0; fila < 2; fila++){
            for(int i = 0; i < 6; i++){
                lista.push_back(new enemigo(50.f + (i * 90.f), 50.f + (fila * 60.f), texNormal));
            }
        }
    } else if (nivel == 3){
        for(int i = 0; i<7; i++){
            float offsetY = (i <= 3) ? (i * 40.f) : ((6-i) * 40.f);
            lista.push_back(new enemigo(50.f + (i * 90.f), 50.f + offsetY, texNormal));
            
        }
    } else if (nivel == 4){
        for(int fila = 0; fila < 3; fila++){
            for(int i = 0; i < 6; i++){
                lista.push_back(new enemigo(40.f + (i * 80.f), 40.f + (fila * 50.f), texNormal));
            }
        }
    } else if (nivel == 5){
        lista.push_back(new jefeFinal(350.f, 50.f, textJefe));
    }
}

int main(){

    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(1080, 720), "Galapoo - Proyecto ELO329"); //Definimos el tamaño de la ventana y el titulo de esta
    window.setFramerateLimit(60); // Fijamos los fps a 60

    EstadoJuego estadoActual = MENU; // Inicializamos el estado del juego en el menú
    sf::Font font; //Cargamos la fuente para el texto del menú

    sf::Texture texturaExplosion;
    if(!texturaExplosion.loadFromFile("../assets/explosion2.jpg")){ //Debugger para verificar que la imagen se cargue
        std::cerr << "Error al cargar explosion.png\n";
    }

    sf::Texture texturaEnemigo;
    if(!texturaEnemigo.loadFromFile("../assets/naveEnemiga.png")){
        std::cerr << "Eror al cargar la nave.png\n";
    }

    sf::Texture texturaJefe;
    if(!texturaJefe.loadFromFile("../assets/naveEnemiga.png")){
        std::cerr << "Error al cargar la naveJefe.png\n";
    }

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
    std::vector<balaEnemiga> balasEnemigas; //Creames el vector "balaEnemiga"
    sf::Clock relojDisparoEnemigo; //Controla cada cuanto tiempo intentara disparar
    
    //Generamos los enemigos
    std::vector<enemigo* > listaEnemigo; //Creamos el vector para generar enemigos
    int nivelActual = 1;
    cargarNivel(nivelActual, listaEnemigo, texturaEnemigo, texturaJefe);
    
    std::vector<Explosion> listaExplosiones; //Creamos el vector para gestionar explosiones
    bool jugadorVivo = true; //Booleano para saber si el jugador esta con vida

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
                    balasEnemigas.clear();
                    listaEnemigo.clear(); 
                    jugadorVivo = true;
                    
                    nivelActual = 1;
                    cargarNivel(nivelActual, listaEnemigo, texturaEnemigo, texturaJefe);

                    estadoActual = MENU;
                }
                else if(estadoActual == GAMEOVER && event.key.code == sf::Keyboard::M){ 
                    miNave.reiniciar();
                    balas.clear(); 
                    balasEnemigas.clear();
                    for(size_t i = 0; i < listaEnemigo.size(); i++){
                        delete listaEnemigo[i];
                    }
                    listaEnemigo.clear(); 
                    jugadorVivo = true;
                    
                    nivelActual = 1;
                    cargarNivel(nivelActual, listaEnemigo, texturaEnemigo, texturaJefe);
                    
                    estadoActual = MENU; 

                }
            }
        }

        // ==========================================
        // ESTA ES LA SECCIÓN DE LÓGICA (ACTUALIZAR)
        // ==========================================
        if(estadoActual == JUGANDO){ 
            if(jugadorVivo){ //Solo actualizamos si el jugador esta vivo
                miNave.actualizar(balas); 
            }

            for (size_t i = 0; i < balas.size(); i++){ 
                balas[i].actualizar();
            }

            for (size_t i = 0; i < balasEnemigas.size(); i++){ 
                balasEnemigas[i].actualizar();
            }

            for(size_t i = 0; i < listaEnemigo.size(); i++){
                listaEnemigo[i]->actualizar();
            }

            // Limpieza de balas fuera de ventana
            for (int i = balas.size() - 1; i >= 0; i--){ 
                if(balas[i].outVentana()){
                    balas.erase(balas.begin() + i);
                }
            }

            for (int i = balasEnemigas.size() - 1; i >= 0; i--){ 
                if(balasEnemigas[i].outVentana()){
                    balasEnemigas.erase(balasEnemigas.begin() + i);
                }
            }

            for(size_t i =0; i < listaExplosiones.size(); i++){
                listaExplosiones[i].actualizar();
            }

            for(int i = listaExplosiones.size() - 1; i>= 0; i--){
                if (listaExplosiones[i].estaTerminada()){
                    listaExplosiones.erase(listaExplosiones.begin() + i);
                    if(!jugadorVivo){
                        estadoActual = GAMEOVER;
                    }
                }
            }

            // ===============================================
            // LOGICA DE DISPARO ENEMIGO ALEATORIO POR NIVEL
            // ===============================================
            if(!listaEnemigo.empty() && jugadorVivo){
                if(relojDisparoEnemigo.getElapsedTime().asSeconds() >= 0.6f){
                    int probaDisparo = nivelActual *20;
                    if((rand() % 100) < probaDisparo){
                        int enemigoShooter = rand() % listaEnemigo.size();

                        sf::FloatRect boundsEnemigo = listaEnemigo[enemigoShooter]->hitbox();
                        float spawnX = boundsEnemigo.left + (boundsEnemigo.width / 2.f) - 5.f;
                        float spawnY = boundsEnemigo.top + boundsEnemigo.height;

                        balasEnemigas.push_back(balaEnemiga(spawnX, spawnY));

                    }
                    relojDisparoEnemigo.restart();
                }
            }

            // --- SE TRASLADARON LAS COLISIONES AQUÍ (ZONA DE LÓGICA) ---
            for(int i = listaEnemigo.size() - 1; i >= 0; i--){
                bool enemigoBorrado = false; // Bandera para saber si el enemigo murió

                // 1. Colisión Bala vs Enemigo
                for(int j = balas.size() - 1; j >= 0; j--){
                    if(listaEnemigo[i]->hitbox().intersects(balas[j].hitbox())){ 
                        listaEnemigo[i]->vida -= 1; 
                        
                        if(listaEnemigo[i]->vida <= 0){ 
                            sonidoExplosion.play(); 
                            sf::FloatRect bounds = listaEnemigo[i]->hitbox();
                            listaExplosiones.push_back(Explosion(bounds.left + bounds.width/2.f, bounds.top + bounds.height/2.f, texturaExplosion));
                            delete listaEnemigo[i];
                            listaEnemigo.erase(listaEnemigo.begin() + i);
                            enemigoBorrado = true; // Marcamos que el enemigo ya no existe
                        }
                        balas.erase(balas.begin() + j);
                        break; // Salimos del bucle de balas
                    }
                }

                // 2. Colisión Nave vs Enemigo (SOLO si el enemigo sigue vivo)
                if (!enemigoBorrado && jugadorVivo) {
                    if(miNave.hitbox().intersects(listaEnemigo[i]->hitbox())){ 
                        sonidoExplosion.play();
                        sf::FloatRect bounds = miNave.hitbox(); //Explotamos al jugador antes de mandar a la pantalla del GAMEOVER
                        listaExplosiones.push_back(Explosion(bounds.left + bounds.width/2.f, bounds.top + bounds.height/2.f, texturaExplosion));
                        jugadorVivo = false;
                        break; // Salimos del bucle de enemigos porque el juego terminó
                    }
                }

                if(jugadorVivo){
                    for(int i = balasEnemigas.size() - 1; i >= 0; i--){
                        if(miNave.hitbox().intersects(balasEnemigas[i].hitbox())){
                            sonidoExplosion.play();
                            sf::FloatRect bounds = miNave.hitbox();
                            listaExplosiones.push_back(Explosion(bounds.left + bounds.width/2.f, bounds.top + bounds.height/2.f, texturaExplosion));

                            jugadorVivo = false;
                            balasEnemigas.erase(balasEnemigas.begin() + i);
                            break;
                        }
                    }
                }
            }
             // =====================================
             // SISTEMA DE AVANCE DE NIVELES
             // =====================================
            if(listaEnemigo.empty() && jugadorVivo){
                nivelActual++;

                if(nivelActual > 5){
                    estadoActual = MENU;
                    nivelActual = 1;
                    cargarNivel(nivelActual, listaEnemigo, texturaEnemigo, texturaJefe);
                }else{
                    balas.clear();
                    cargarNivel(nivelActual, listaEnemigo, texturaEnemigo, texturaJefe);
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
            if(jugadorVivo){
                miNave.dibujar(window);
            }
            
            for(size_t i = 0; i < balas.size(); i++){ 
                balas[i].dibujar(window);
            }

            for(size_t i = 0; i < listaEnemigo.size(); i++){
                listaEnemigo[i]->dibujar(window);
            }

            for(size_t i = 0; i < listaExplosiones.size(); i++){
                listaExplosiones[i].dibujar(window);
            }

            for(size_t i = 0; i < balasEnemigas.size(); i++){ 
                balasEnemigas[i].dibujar(window);
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