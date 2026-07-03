#ifndef JUGADORES_H
#define JUGADORES_H

#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>
#include <cstdlib>

class Personaje {
protected:
    sf::Texture textura;
    sf::Sprite sprite;
    int vida;
    float velocidadY;
    bool enElSuelo;
    
    sf::RectangleShape barraFondo;
    sf::RectangleShape barraCantidad;
    
    // NUEVO: Componentes para la barra de Energía Especial
    sf::RectangleShape barraFondoEspecial;
    sf::RectangleShape barraCantidadEspecial;
    float energiaEspecial; 

public:
    bool golpeDebil;
    bool golpeFuerte;
    bool ataqueEspecial; // NUEVO: Estado de súper ataque

    virtual ~Personaje() {}
    
    void configurarBarras(float x, float y) {
        // Barra de Vida (Base 1000 HP)
        barraFondo.setSize(sf::Vector2f(250.0f, 16.0f));
        barraFondo.setFillColor(sf::Color(100, 0, 0)); 
        barraFondo.setPosition(x, y);

        barraCantidad.setSize(sf::Vector2f(250.0f, 16.0f));
        barraCantidad.setFillColor(sf::Color(0, 255, 0)); 
        barraCantidad.setPosition(x, y);

        // NUEVO: Barra de Energía Especial (Debajo de la de vida)
        barraFondoEspecial.setSize(sf::Vector2f(180.0f, 8.0f));
        barraFondoEspecial.setFillColor(sf::Color(40, 40, 60));
        barraFondoEspecial.setPosition(x, y + 22.0f);

        barraCantidadEspecial.setSize(sf::Vector2f(0.0f, 8.0f));
        barraCantidadEspecial.setFillColor(sf::Color(0, 190, 255)); // Azul eléctrico
        barraCantidadEspecial.setPosition(x, y + 22.0f);
    }

    virtual void actualizar(float nivelDelSuelo) {
        velocidadY += 0.8f;
        sprite.move(0.0f, velocidadY);
        
        float limiteInferior = sprite.getGlobalBounds().top + sprite.getGlobalBounds().height;
        if (limiteInferior >= nivelDelSuelo) {
            float desfasamientoY = limiteInferior - sprite.getPosition().y;
            sprite.setPosition(sprite.getPosition().x, nivelDelSuelo - desfasamientoY);
            velocidadY = 0.0f;
            enElSuelo = true;
        }

        sf::FloatRect limitesCuerpo = sprite.getGlobalBounds();
        float mitadAnchoEfectivo = limitesCuerpo.width / 2.0f;

        if (limitesCuerpo.left < 5.0f) {
            sprite.setPosition(mitadAnchoEfectivo + 5.0f, sprite.getPosition().y);
        }
        if (limitesCuerpo.left + limitesCuerpo.width > 795.0f) {
            sprite.setPosition(795.0f - mitadAnchoEfectivo, sprite.getPosition().y);
        }

        // Actualizar renderizado de Barra de Vida (Escala sobre 1000 HP)
        float nuevoAnchoVida = (vida / 1000.0f) * 250.0f;
        barraCantidad.setSize(sf::Vector2f(nuevoAnchoVida, 16.0f));

        // Actualizar renderizado de Barra de Súper (Escala sobre 100 Puntos)
        float nuevoAnchoEnergia = (energiaEspecial / 100.0f) * 180.0f;
        barraCantidadEspecial.setSize(sf::Vector2f(nuevoAnchoEnergia, 8.0f));
    }
    
    virtual void mirarHacia(float objetivoX) {
        if (sprite.getPosition().x < objetivoX) {
            sprite.setScale(1.6f, 1.6f); 
        } else {
            sprite.setScale(-1.6f, 1.6f); 
        }
    }

    void recibirDanio(int cantidad) {
        vida -= cantidad;
        if (vida < 0) vida = 0;
        
        // Al recibir daño también carga un poco de energía (0.5 por cada punto de daño recibido)
        cargarEnergia(cantidad * 0.5f);
    }

    void cargarEnergia(float cantidad) {
        energiaEspecial += cantidad;
        if (energiaEspecial > 100.0f) energiaEspecial = 100.0f;
    }

    void gastarEnergiaCompleta() {
        energiaEspecial = 0.0f;
    }

    float getEnergia() const { return energiaEspecial; }
    int getVida() const { return vida; }
    sf::Vector2f getPosicion() const { return sprite.getPosition(); }
    sf::FloatRect getCuerpo() { return sprite.getGlobalBounds(); }

    sf::FloatRect getHitboxAtaque(int tipoAtaque) {
        // 0: Debil, 1: Fuerte, 2: Especial Súper
        sf::FloatRect cuerpo = sprite.getGlobalBounds();
        float rangoAtaque = 55.0f;
        if (tipoAtaque == 1) rangoAtaque = 85.0f;
        if (tipoAtaque == 2) rangoAtaque = 120.0f; // El Súper tiene un rango enorme
        
        if (sprite.getScale().x > 0) {
            return sf::FloatRect(cuerpo.left + cuerpo.width - 40.0f, cuerpo.top + 30.0f, rangoAtaque, 40.0f);
        } else {
            return sf::FloatRect(cuerpo.left - rangoAtaque + 40.0f, cuerpo.top + 30.0f, rangoAtaque, 40.0f);
        }
    }

    void dibujar(sf::RenderWindow& ventana) { 
        ventana.draw(sprite); 
        ventana.draw(barraFondo);
        ventana.draw(barraCantidad);
        ventana.draw(barraFondoEspecial);
        ventana.draw(barraCantidadEspecial);
    }
};

// Clase para el Jugador 1
class Jugador : public Personaje {
public:
    Jugador(const std::string& archivoTextura, sf::Vector2f posicionInicial, int numJugador) {
        if (textura.loadFromFile("assets/textures/" + archivoTextura)) {
            sprite.setTexture(textura);
            sf::FloatRect bounds = sprite.getLocalBounds();
            sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
            sprite.setScale(1.6f, 1.6f); 
        }
        sprite.setPosition(posicionInicial);
        vida = 1000; // MODIFICADO: 1000 de vida base
        energiaEspecial = 0.0f;
        velocidadY = 0.0f;
        enElSuelo = true;
        golpeDebil = false;
        golpeFuerte = false;
        ataqueEspecial = false;
        
        configurarBarras(50.0f, 30.0f);
    }

    void manejarEntrada() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) sprite.move(-5.0f, 0.0f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) sprite.move(5.0f, 0.0f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && enElSuelo) {
            velocidadY = -14.0f;
            enElSuelo = false;
        }
        golpeDebil = sf::Keyboard::isKeyPressed(sf::Keyboard::J);
        golpeFuerte = sf::Keyboard::isKeyPressed(sf::Keyboard::K);
        ataqueEspecial = sf::Keyboard::isKeyPressed(sf::Keyboard::U); // NUEVO: Tecla U para Súper
    }
    
    void congelar() {
        golpeDebil = false;
        golpeFuerte = false;
        ataqueEspecial = false;
    }
};

// Clase para la Inteligencia Artificial Avanzada
class IA_Enemigo : public Personaje {
public:
    IA_Enemigo(const std::string& archivoTextura, sf::Vector2f posicionInicial) {
        if (textura.loadFromFile("assets/textures/" + archivoTextura)) {
            sprite.setTexture(textura);
            sf::FloatRect bounds = sprite.getLocalBounds();
            sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
            sprite.setScale(1.6f, 1.6f); 
        }
        sprite.setPosition(posicionInicial);
        vida = 1000; // MODIFICADO: 1000 de vida base
        energiaEspecial = 0.0f;
        velocidadY = 0.0f;
        enElSuelo = true;
        golpeDebil = false;
        golpeFuerte = false;
        ataqueEspecial = false;
        
        configurarBarras(500.0f, 30.0f);
    }

    void pensar(float xJugador1) {
        float miX = sprite.getPosition().x;
        float distancia = std::abs(xJugador1 - miX);

        if (vida < 250 && (std::rand() % 100) < 20) {
            if (miX < xJugador1) sprite.move(-3.5f, 0.0f);
            else sprite.move(3.5f, 0.0f);
            golpeDebil = false;
            golpeFuerte = false;
            ataqueEspecial = false;
            return;
        }

        if (distancia > 80.0f) {
            if (miX < xJugador1) sprite.move(3.0f, 0.0f);
            else sprite.move(-3.0f, 0.0f);
            
            if (enElSuelo && (std::rand() % 1000) < 15) {
                velocidadY = -14.0f;
                enElSuelo = false;
            }
            golpeDebil = false;
            golpeFuerte = false;
            ataqueEspecial = false;
        } 
        else {
            // NUEVO: Si la IA tiene la barra cargada al 100% y está cerca, prioriza tirar el Súper
            if (energiaEspecial >= 100.0f) {
                ataqueEspecial = true;
                golpeDebil = false;
                golpeFuerte = false;
                return;
            }

            int azar = std::rand() % 100;
            if (azar < 9) {         
                golpeDebil = true;
                golpeFuerte = false;
                ataqueEspecial = false;
            } else if (azar < 13) { 
                golpeDebil = false;
                golpeFuerte = true;
                ataqueEspecial = false;
            } else {
                golpeDebil = false;
                golpeFuerte = false;
                ataqueEspecial = false;
            }
        }
    }
    
    void congelar() {
        golpeDebil = false;
        golpeFuerte = false;
        ataqueEspecial = false;
    }
};

#endif