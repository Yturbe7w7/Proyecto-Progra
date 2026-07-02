#include "Personaje.h"
#include <iostream>

Personaje::Personaje(const std::string& rutaTextura, sf::Vector2f posicionInicial) {
    // Buscamos la textura directamente en la carpeta assets que pide tu estructura
    if (!textura.loadFromFile("assets/textures/" + rutaTextura)) {
        std::cerr << "Error cargando la textura: " << rutaTextura << std::endl;
    }
    sprite.setTexture(textura);
    sprite.setPosition(posicionInicial);
    
    // Opcional: Escalar el sprite si es muy grande o chico
    sprite.setScale({2.0f, 2.0f}); 
}

void Personaje::actualizar(float alturaSuelo) {
    if (!enElSuelo) {
        velocidad.y += gravedad;
    }

    sprite.move(velocidad);

    // Colisión con el suelo usando el tamaño del Sprite asignado
    float limiteInferior = sprite.getPosition().y + sprite.getGlobalBounds().size.y;
    if (limiteInferior >= alturaSuelo) {
        sprite.setPosition({sprite.getPosition().x, alturaSuelo - sprite.getGlobalBounds().size.y});
        velocidad.y = 0.0f;
        enElSuelo = true;
    }
}

void Personaje::dibujar(sf::RenderWindow& ventana) {
    ventana.draw(sprite);
}