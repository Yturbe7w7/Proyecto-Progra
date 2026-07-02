#include <SFML/Graphics.hpp>
#include <optional>
#include <vector>
#include "Jugadores.h"

int main() {
    sf::RenderWindow ventana(sf::VideoMode({800, 600}), "Proyecto 252 - Juego de Peleas");
    ventana.setFramerateLimit(60);

    float nivelDelSuelo = 550.0f;

    // Polimorfismo: Guardamos diferentes personajes en un solo contenedor
    std::vector<Personaje*> luchadores;
    luchadores.push_back(new JugadorAzul({150.0f, 300.0f}));
    luchadores.push_back(new JugadorRojo({550.0f, 300.0f}));

    while (ventana.isOpen()) {
        while (const std::optional evento = ventana.pollEvent()) {
            if (evento->is<sf::Event::Closed>()) {
                ventana.close();
            }
        }

        // Actualizar todos los personajes en escena
        for (auto* luchador : luchadores) {
            luchador->manejarEntrada();
            luchador->actualizar(nivelDelSuelo);
        }

        // Renderizado
        ventana.clear(sf::Color(30, 30, 30)); // Fondo gris oscuro
        
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