#include <SFML/Graphics.hpp>
#include <optional>
#include <vector>
#include "Jugadores.h"

int main() {
    sf::RenderWindow ventana(sf::VideoMode({800, 600}), "Proyecto 252 - Juego de Peleas");
    ventana.setFramerateLimit(60);

    float nivelDelSuelo = 530.0f; // Punto de colisión para los pies de los personajes

    // Cargar fondo del escenario
    sf::Texture texturaFondo;
    sf::Sprite spriteFondo;
    if (texturaFondo.loadFromFile("assets/textures/fondo.png")) {
        spriteFondo.setTexture(texturaFondo);
    }

    // Contenedor de luchadores en la arena
    std::vector<Personaje*> luchadores;
    luchadores.push_back(new JugadorAzul({150.0f, 200.0f}));
    luchadores.push_back(new JugadorRojo({550.0f, 200.0f}));

    // BUCLE DE JUEGO
    while (ventana.isOpen()) {
        while (const std::optional evento = ventana.pollEvent()) {
            if (evento->is<sf::Event::Closed>()) {
                ventana.close();
            }
        }

        // 1. Actualizar Lógica
        for (auto* luchador : luchadores) {
            luchador->manejarEntrada();
            luchador->actualizar(nivelDelSuelo);
        }

        // 2. Renderizar
        ventana.clear(sf::Color::Black);
        
        ventana.draw(spriteFondo);
        for (auto* luchador : luchadores) {
            luchador->dibujar(ventana);
        }

        ventana.display();
    }

    // Limpieza de memoria
    for (auto* luchador : luchadores) {
        delete luchador;
    }

    return 0;
}