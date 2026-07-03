#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> 
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include "Jugadores.h"

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    sf::RenderWindow ventana(sf::VideoMode(800, 600), "PELEITAS");
    ventana.setFramerateLimit(60);

    float nivelDelSuelo = 530.0f; 

    sf::Texture texturaFondo;
    sf::Sprite spriteFondo;
    sf::Music musicaFondo;

    std::string listaFondos[3] = {"fondo0.png", "fondo1.png", "fondo2.png"};
    std::string listaMusica[3] = {"musica0.ogg", "musica1.ogg", "musica2.ogg"};

    sf::Font fuente;
    bool tieneFuente = fuente.loadFromFile("C:/Windows/Fonts/arial.ttf");

    sf::Text textoTituloJuego;
    if (tieneFuente) {
        textoTituloJuego.setFont(fuente);
        textoTituloJuego.setString("PELEITAS");
        textoTituloJuego.setCharacterSize(55);
        textoTituloJuego.setFillColor(sf::Color::Cyan);
        textoTituloJuego.setStyle(sf::Text::Bold);
        sf::FloatRect boundsT = textoTituloJuego.getLocalBounds();
        textoTituloJuego.setOrigin(boundsT.left + boundsT.width / 2.0f, 0.0f);
        textoTituloJuego.setPosition(400.0f, 20.0f);
    }

    sf::Text textoMenu;
    if (tieneFuente) {
        textoMenu.setFont(fuente);
        textoMenu.setCharacterSize(26);
        textoMenu.setFillColor(sf::Color::White);
    }

    sf::Text textoFin;
    if (tieneFuente) {
        textoFin.setFont(fuente);
        textoFin.setCharacterSize(50);
        textoFin.setFillColor(sf::Color::Yellow);
    }

    sf::Text textoTimer;
    if (tieneFuente) {
        textoTimer.setFont(fuente);
        textoTimer.setCharacterSize(40);
        textoTimer.setFillColor(sf::Color::White);
        textoTimer.setStyle(sf::Text::Bold);
        textoTimer.setPosition(375.0f, 20.0f); 
    }

    sf::Text textoMarcador;
    if (tieneFuente) {
        textoMarcador.setFont(fuente);
        textoMarcador.setCharacterSize(18);       
        textoMarcador.setFillColor(sf::Color::Cyan);
        textoMarcador.setStyle(sf::Text::Bold);
    }

    sf::Text textoAnuncioRonda;
    if (tieneFuente) {
        textoAnuncioRonda.setFont(fuente);
        textoAnuncioRonda.setCharacterSize(70);
        textoAnuncioRonda.setFillColor(sf::Color::Yellow);
        textoAnuncioRonda.setStyle(sf::Text::Bold);
    }

    std::string archivosPersonajes[4] = {"azul.png", "rojo.png", "verde.png", "amarillo.png"};
    std::string nombresPersonajes[4] = {"Rea", "Subaru", "Kazuma", "Mio"};

    bool enMenu = true;
    bool juegoTerminado = false;
    bool rondaTerminada = false; 
    
    int seleccionJ1 = -1;
    int seleccionJ2 = -1;

    int indiceCursor = 0; 
    int turnoJugadorSeleccionando = 1; 

    sf::RectangleShape bloquesMenu[4];
    sf::Texture texturasMiniaturas[4];
    sf::Sprite spritesMiniaturas[4];
    sf::Text textosBloques[4];

    for (int i = 0; i < 4; i++) {
        if (texturasMiniaturas[i].loadFromFile("assets/textures/" + archivosPersonajes[i])) {
            spritesMiniaturas[i].setTexture(texturasMiniaturas[i]);
            sf::FloatRect boundsSprite = spritesMiniaturas[i].getLocalBounds();
            spritesMiniaturas[i].setScale(120.0f / boundsSprite.width, 120.0f / boundsSprite.height);
            spritesMiniaturas[i].setPosition(100.0f + (i * 160.0f), 250.0f);
        }

        bloquesMenu[i].setSize(sf::Vector2f(120.0f, 120.0f));
        bloquesMenu[i].setFillColor(sf::Color(40, 40, 50)); 
        bloquesMenu[i].setOutlineThickness(4.0f);
        bloquesMenu[i].setOutlineColor(sf::Color(100, 100, 100));
        bloquesMenu[i].setPosition(100.0f + (i * 160.0f), 250.0f); 

        if (tieneFuente) {
            textosBloques[i].setFont(fuente);
            textosBloques[i].setString(nombresPersonajes[i]);
            textosBloques[i].setCharacterSize(22);
            textosBloques[i].setFillColor(sf::Color::White);
            textosBloques[i].setStyle(sf::Text::Bold);
            
            sf::FloatRect boundsTxt = textosBloques[i].getLocalBounds();
            textosBloques[i].setOrigin(boundsTxt.left + boundsTxt.width / 2.0f, 0.0f);
            textosBloques[i].setPosition(100.0f + (i * 160.0f) + 60.0f, 385.0f);
        }
    }

    sf::RectangleShape rectCursor;
    rectCursor.setSize(sf::Vector2f(130.0f, 130.0f));
    rectCursor.setFillColor(sf::Color::Transparent);
    rectCursor.setOutlineThickness(6.0f);
    rectCursor.setOutlineColor(sf::Color::Yellow); 

    int rondasGanadasJ1 = 0;
    int rondasGanadasIA = 0;
    int numeroRondaActual = 1;

    Jugador* j1 = nullptr;
    IA_Enemigo* ia = nullptr; 

    sf::Clock relojCooldownJ1;
    sf::Clock relojCooldownIA;
    float tiempoCooldownActualJ1 = 0.0f;
    float tiempoCooldownActualIA = 0.0f;

    sf::Clock relojPartida;
    int tiempoRestante = 60;
    
    sf::Clock relojPausaRonda; 

    sf::Clock relojIntroRonda;
    float tiempoIntro = 2.0f; 

    bool j1EfectoCritico = false;
    bool iaEfectoCritico = false;

    bool j1SúperOnda = false;
    bool iaSúperOnda = false;

    while (ventana.isOpen()) {
        sf::Event evento;
        while (ventana.pollEvent(evento)) {
            if (evento.type == sf::Event::Closed) {
                ventana.close();
            }

            if (enMenu && evento.type == sf::Event::KeyPressed) {
                if (evento.key.code == sf::Keyboard::Left || evento.key.code == sf::Keyboard::A) {
                    indiceCursor--;
                    if (indiceCursor < 0) indiceCursor = 3; 
                }
                if (evento.key.code == sf::Keyboard::Right || evento.key.code == sf::Keyboard::D) {
                    indiceCursor++;
                    if (indiceCursor > 3) indiceCursor = 0;
                }
                if (evento.key.code == sf::Keyboard::Enter || evento.key.code == sf::Keyboard::Space) {
                    if (turnoJugadorSeleccionando == 1) {
                        seleccionJ1 = indiceCursor;
                        turnoJugadorSeleccionando = 2; 
                    } 
                    else if (turnoJugadorSeleccionando == 2) {
                        seleccionJ2 = indiceCursor;
                        
                        j1 = new Jugador(archivosPersonajes[seleccionJ1], sf::Vector2f(150.0f, 400.0f), 1);
                        ia = new IA_Enemigo(archivosPersonajes[seleccionJ2], sf::Vector2f(650.0f, 400.0f));
                        
                        rondasGanadasJ1 = 0;
                        rondasGanadasIA = 0;
                        numeroRondaActual = 1;

                        int indiceAleatorio = std::rand() % 3;
                        if (texturaFondo.loadFromFile("assets/textures/" + listaFondos[indiceAleatorio])) {
                            spriteFondo.setTexture(texturaFondo);
                            // AJUSTE: Redimensiona automáticamente la imagen a 800x600 píxeles
                            sf::Vector2u tamanoTextura = texturaFondo.getSize();
                            spriteFondo.setScale(800.0f / tamanoTextura.x, 600.0f / tamanoTextura.y);
                        }
                        musicaFondo.stop();
                        if (musicaFondo.openFromFile("assets/audio/" + listaMusica[indiceAleatorio])) {
                            musicaFondo.setLoop(true);
                            musicaFondo.setVolume(40.0f);
                            musicaFondo.play();
                        }

                        enMenu = false; 
                        juegoTerminado = false;
                        rondaTerminada = false;
                        relojIntroRonda.restart(); 
                        relojPartida.restart(); 
                    }
                }
            }
        }

        if (juegoTerminado && sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            if (j1) { delete j1; j1 = nullptr; }
            if (ia) { delete ia; ia = nullptr; }
            seleccionJ1 = -1;
            seleccionJ2 = -1;
            turnoJugadorSeleccionando = 1;
            indiceCursor = 0;
            enMenu = true;
            juegoTerminado = false;
            rondaTerminada = false;
        }

        ventana.clear(sf::Color(20, 20, 28)); 

        if (enMenu) {
            if (tieneFuente) {
                ventana.draw(textoTituloJuego);

                if (turnoJugadorSeleccionando == 1) {
                    textoMenu.setString("ESCOGE TU PERSONAJE");
                } else {
                    textoMenu.setString("ESCOGE A TU ENEMIGO");
                }
                
                sf::FloatRect boundsMenu = textoMenu.getLocalBounds();
                textoMenu.setOrigin(boundsMenu.left + boundsMenu.width / 2.0f, 0.0f);
                textoMenu.setPosition(400.0f, 130.0f);
                ventana.draw(textoMenu);
            }

            rectCursor.setPosition(100.0f + (indiceCursor * 160.0f) - 5.0f, 250.0f - 5.0f);

            for (int i = 0; i < 4; i++) {
                if (turnoJugadorSeleccionando == 2 && i == seleccionJ1) {
                    bloquesMenu[i].setOutlineColor(sf::Color(255, 0, 0)); 
                } else {
                    bloquesMenu[i].setOutlineColor(sf::Color(80, 80, 90));
                }
                ventana.draw(bloquesMenu[i]);
                ventana.draw(spritesMiniaturas[i]); 
                ventana.draw(textosBloques[i]);     
            }

            ventana.draw(rectCursor);
        } 
        else {
            bool enIntro = relojIntroRonda.getElapsedTime().asSeconds() < tiempoIntro;

            if (!juegoTerminado && !rondaTerminada) {
                
                if (enIntro) {
                    relojPartida.restart();
                    tiempoRestante = 60;
                    
                    j1->congelar();
                    ia->congelar();
                    
                    j1->actualizar(nivelDelSuelo);
                    ia->actualizar(nivelDelSuelo);
                } 
                else {
                    int segundosTranscurridos = static_cast<int>(relojPartida.getElapsedTime().asSeconds());
                    tiempoRestante = 60 - segundosTranscurridos;

                    bool rondaDefinida = false;

                    if (tiempoRestante <= 0) {
                        tiempoRestante = 0;
                        rondaDefinida = true;
                    }
                    else if (j1->getVida() <= 0 || ia->getVida() <= 0) {
                        rondaDefinida = true;
                    }

                    if (rondaDefinida) {
                        rondaTerminada = true;
                        relojPausaRonda.restart();

                        if (j1->getVida() > ia->getVida()) {
                            rondasGanadasJ1++;
                            textoFin.setString("¡RONDA " + std::to_string(numeroRondaActual) + " PARA " + nombresPersonajes[seleccionJ1] + "!");
                        } else if (ia->getVida() > j1->getVida()) {
                            rondasGanadasIA++;
                            textoFin.setString("¡RONDA " + std::to_string(numeroRondaActual) + " PARA LA IA (" + nombresPersonajes[seleccionJ2] + ")!");
                        } else {
                            textoFin.setString("¡RONDA EMPATADA!");
                        }

                        sf::FloatRect bounds = textoFin.getLocalBounds();
                        textoFin.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
                        textoFin.setPosition(sf::Vector2f(400.0f, 250.0f));

                        if (rondasGanadasJ1 >= 2 || rondasGanadasIA >= 2) {
                            juegoTerminado = true;
                            musicaFondo.stop();
                            if (rondasGanadasJ1 >= 2) {
                                textoFin.setString("¡GANADOR: " + nombresPersonajes[seleccionJ1] + "!\nPresiona 'R' para volver al menu");
                            } else {
                                textoFin.setString("¡GANADOR: " + nombresPersonajes[seleccionJ2] + " (IA)!\nPresiona 'R' para volver al menu");
                            }
                            sf::FloatRect bounds2 = textoFin.getLocalBounds();
                            textoFin.setOrigin(bounds2.left + bounds2.width / 2.0f, bounds2.top + bounds2.height / 2.0f);
                            textoFin.setPosition(sf::Vector2f(400.0f, 250.0f));
                        }
                    }

                    if (!rondaTerminada) {
                        if (tieneFuente) {
                            textoTimer.setString(std::to_string(tiempoRestante));
                        }

                        j1->manejarEntrada();
                        ia->pensar(j1->getPosicion().x); 

                        j1->actualizar(nivelDelSuelo);
                        ia->actualizar(nivelDelSuelo);

                        j1->mirarHacia(ia->getPosicion().x);
                        ia->mirarHacia(j1->getPosicion().x);

                        if (relojCooldownJ1.getElapsedTime().asSeconds() >= tiempoCooldownActualJ1) {
                            if (j1->ataqueEspecial && j1->getEnergia() >= 100.0f) {
                                j1SúperOnda = true; 
                                if (j1->getHitboxAtaque(2).intersects(ia->getCuerpo())) {
                                    ia->recibirDanio(100); 
                                }
                                j1->gastarEnergiaCompleta();
                                tiempoCooldownActualJ1 = 0.75f; 
                                relojCooldownJ1.restart();
                            }
                            else if (j1->golpeDebil || j1->golpeFuerte) {
                                j1SúperOnda = false;
                                bool esFuerte = j1->golpeFuerte;
                                if (j1->getHitboxAtaque(esFuerte ? 1 : 0).intersects(ia->getCuerpo())) {
                                    int danioBase = esFuerte ? 22 : 7;
                                    j1EfectoCritico = (std::rand() % 100) < 15;
                                    if (j1EfectoCritico) danioBase *= 2;

                                    ia->recibirDanio(danioBase);
                                    j1->cargarEnergia(esFuerte ? 15.0f : 6.0f); 
                                }
                                tiempoCooldownActualJ1 = esFuerte ? 0.45f : 0.15f;
                                relojCooldownJ1.restart();
                            }
                        }

                        if (relojCooldownIA.getElapsedTime().asSeconds() >= tiempoCooldownActualIA) {
                            if (ia->ataqueEspecial && ia->getEnergia() >= 100.0f) {
                                iaSúperOnda = true;
                                if (ia->getHitboxAtaque(2).intersects(j1->getCuerpo())) {
                                    j1->recibirDanio(100); 
                                }
                                ia->gastarEnergiaCompleta();
                                tiempoCooldownActualIA = 0.75f;
                                relojCooldownIA.restart();
                            }
                            else if (ia->golpeDebil || ia->golpeFuerte) {
                                iaSúperOnda = false;
                                bool esFuerte = ia->golpeFuerte;
                                if (ia->getHitboxAtaque(esFuerte ? 1 : 0).intersects(j1->getCuerpo())) {
                                    int danioBase = esFuerte ? 22 : 7;
                                    iaEfectoCritico = (std::rand() % 100) < 15;
                                    if (iaEfectoCritico) danioBase *= 2;

                                    j1->recibirDanio(danioBase);
                                    ia->cargarEnergia(esFuerte ? 15.0f : 6.0f); 
                                }
                                tiempoCooldownActualIA = esFuerte ? 0.45f : 0.15f;
                                relojCooldownIA.restart();
                            }
                        }
                    }
                }
            }

            if (rondaTerminada && !juegoTerminado) {
                if (relojPausaRonda.getElapsedTime().asSeconds() >= 3.0f) {
                    rondaTerminada = false;
                    numeroRondaActual++;
                    
                    delete j1;
                    delete ia;
                    j1 = new Jugador(archivosPersonajes[seleccionJ1], sf::Vector2f(150.0f, 400.0f), 1);
                    ia = new IA_Enemigo(archivosPersonajes[seleccionJ2], sf::Vector2f(650.0f, 400.0f));
                    
                    int indiceAleatorio = std::rand() % 3;
                    if (texturaFondo.loadFromFile("assets/textures/" + listaFondos[indiceAleatorio])) {
                        spriteFondo.setTexture(texturaFondo);
                        // AJUSTE: Redimensiona automáticamente la imagen a 800x600 píxeles también entre rondas
                        sf::Vector2u tamanoTextura = texturaFondo.getSize();
                        spriteFondo.setScale(800.0f / tamanoTextura.x, 600.0f / tamanoTextura.y);
                    }
                    musicaFondo.stop();
                    if (musicaFondo.openFromFile("assets/audio/" + listaMusica[indiceAleatorio])) {
                        musicaFondo.play();
                    }

                    relojIntroRonda.restart(); 
                    relojPartida.restart();
                }
            }

            if (tieneFuente) {
                std::string infoMarcador = "RND " + std::to_string(numeroRondaActual) + "   " + nombresPersonajes[seleccionJ1] + " [" + std::to_string(rondasGanadasJ1) + " - " + std::to_string(rondasGanadasIA) + "] IA (" + nombresPersonajes[seleccionJ2] + ")";
                textoMarcador.setString(infoMarcador);

                sf::FloatRect boundsMarcador = textoMarcador.getLocalBounds();
                textoMarcador.setOrigin(boundsMarcador.left + boundsMarcador.width / 2.0f, 0.0f);
                textoMarcador.setPosition(sf::Vector2f(400.0f, 70.0f)); 
            }

            ventana.draw(spriteFondo);
            j1->dibujar(ventana);
            ia->dibujar(ventana);

            if (!rondaTerminada) {
                if (!enIntro && (j1->golpeDebil || j1->golpeFuerte || j1SúperOnda)) {
                    float tTranscurrido = relojCooldownJ1.getElapsedTime().asSeconds();
                    int tipoH = j1SúperOnda ? 2 : (j1->golpeFuerte ? 1 : 0);
                    sf::FloatRect hitbox = j1->getHitboxAtaque(tipoH);
                    
                    sf::CircleShape ondaGolpe;
                    float centroX = hitbox.left + (hitbox.width / 2.0f);
                    float centroY = hitbox.top + (hitbox.height / 2.0f);
                    
                    float radioMaximo = 35.0f;
                    if (tipoH == 1) radioMaximo = 60.0f;
                    if (tipoH == 2) radioMaximo = 110.0f; 
                    
                    float radioActual = (tTranscurrido / tiempoCooldownActualJ1) * radioMaximo;
                    if (radioActual > radioMaximo) radioActual = radioMaximo;

                    ondaGolpe.setRadius(radioActual);
                    ondaGolpe.setOrigin(radioActual, radioActual);
                    ondaGolpe.setPosition(centroX, centroY);
                    int alpha = static_cast<int>((1.0f - (tTranscurrido / tiempoCooldownActualJ1)) * 255);
                    if (alpha < 0) alpha = 0;

                    if (tipoH == 2) ondaGolpe.setFillColor(sf::Color(0, 190, 255, alpha)); 
                    else if (j1EfectoCritico) ondaGolpe.setFillColor(sf::Color(255, 0, 0, alpha));
                    else ondaGolpe.setFillColor(sf::Color(255, 255, 170, alpha));
                    ventana.draw(ondaGolpe);
                }

                if (!enIntro && (ia->golpeDebil || ia->golpeFuerte || iaSúperOnda)) {
                    float tTranscurrido = relojCooldownIA.getElapsedTime().asSeconds();
                    int tipoH = iaSúperOnda ? 2 : (ia->golpeFuerte ? 1 : 0);
                    sf::FloatRect hitbox = ia->getHitboxAtaque(tipoH);
                    
                    sf::CircleShape ondaGolpe;
                    float centroX = hitbox.left + (hitbox.width / 2.0f);
                    float centroY = hitbox.top + (hitbox.height / 2.0f);
                    
                    float radioMaximo = 35.0f;
                    if (tipoH == 1) radioMaximo = 60.0f;
                    if (tipoH == 2) radioMaximo = 110.0f;
                    
                    float radioActual = (tTranscurrido / tiempoCooldownActualIA) * radioMaximo;
                    if (radioActual > radioMaximo) radioActual = radioMaximo;

                    ondaGolpe.setRadius(radioActual);
                    ondaGolpe.setOrigin(radioActual, radioActual);
                    ondaGolpe.setPosition(centroX, centroY);
                    int alpha = static_cast<int>((1.0f - (tTranscurrido / tiempoCooldownActualIA)) * 255);
                    if (alpha < 0) alpha = 0;

                    if (tipoH == 2) ondaGolpe.setFillColor(sf::Color(0, 190, 255, alpha));
                    else if (iaEfectoCritico) ondaGolpe.setFillColor(sf::Color(255, 0, 0, alpha));
                    else ondaGolpe.setFillColor(sf::Color(255, 130, 40, alpha));
                    ventana.draw(ondaGolpe);
                }

                if (tieneFuente) ventana.draw(textoTimer);
            }

            if (tieneFuente) ventana.draw(textoMarcador);
            if ((rondaTerminada || juegoTerminado) && tieneFuente) ventana.draw(textoFin);

            if (enIntro && !juegoTerminado && tieneFuente) {
                float segs = relojIntroRonda.getElapsedTime().asSeconds();
                if (segs < 1.4f || (static_cast<int>(segs * 10) % 2 == 0)) {
                    textoAnuncioRonda.setString("RONDA " + std::to_string(numeroRondaActual));
                    sf::FloatRect boundsRonda = textoAnuncioRonda.getLocalBounds();
                    textoAnuncioRonda.setOrigin(boundsRonda.left + boundsRonda.width / 2.0f, boundsRonda.top + boundsRonda.height / 2.0f);
                    textoAnuncioRonda.setPosition(400.0f, 260.0f);
                    ventana.draw(textoAnuncioRonda);
                }
            }
        }

        ventana.display();
    }

    if (j1) delete j1;
    if (ia) delete ia;

    return 0;
}