#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <SFML/Graphics.hpp>

class Personaje {
protected:
    sf::Sprite sprite;          
    sf::Texture textura;
    sf::Vector2f velocidad{0.0f, 0.0f};
    
    float velocidadMovimiento = 6.0f;
    float fuerzaSalto = 16.0f;
    float gravedad = 0.7f;
    bool enElSuelo = false;

public:
    Personaje(const std::string& rutaTextura, sf::Vector2f posicionInicial);
    virtual ~Personaje() = default;

    virtual void manejarEntrada() = 0; // Cada personaje implementa sus teclas
    void actualizar(float alturaSuelo);
    void dibujar(sf::RenderWindow& ventana);
};

#endif
