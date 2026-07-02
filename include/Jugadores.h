#ifndef JUGADORES_H
#define JUGADORES_H

#include "Personaje.h"

// ==========================================
// PERSONAJE 1: GUERRERO AZUL (Controles: WASD)
// ==========================================
class JugadorAzul : public Personaje {
public:
    // Pasa el nombre del archivo de imagen que guardes en assets/textures/
    JugadorAzul(sf::Vector2f pos) : Personaje("azul.png", pos) {}

    void manejarEntrada() override {
        velocidad.x = 0.0f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) velocidad.x = -velocidadMovimiento;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) velocidad.x = velocidadMovimiento;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && enElSuelo) {
            velocidad.y = -fuerzaSalto;
            enElSuelo = false;
        }
    }
};

// ==========================================
// PERSONAJE 2: GUERRERO ROJO (Controles: Flechas)
// ==========================================
class JugadorRojo : public Personaje {
public:
    JugadorRojo(sf::Vector2f pos) : Personaje("rojo.png", pos) {}

    void manejarEntrada() override {
        velocidad.x = 0.0f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) velocidad.x = -velocidadMovimiento;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) velocidad.x = velocidadMovimiento;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && enElSuelo) {
            velocidad.y = -fuerzaSalto;
            enElSuelo = false;
        }
    }
};

#endif