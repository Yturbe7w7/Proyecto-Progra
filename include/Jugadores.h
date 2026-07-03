#ifndef JUGADORES_H
#define JUGADORES_H

#include "Personaje.h"

// JUGADOR 1: Se mueve con WASD
class JugadorAzul : public Personaje {
public:
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

// JUGADOR 2: Se mueve con las Flechas de Dirección
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