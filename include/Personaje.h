#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <SFML/Graphics.hpp>
#include <string>

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
    // El constructor recibirá el nombre de la imagen y dónde aparece
    Personaje(const std::string& nombreArchivo, sf::Vector2f posicionInicial);
    virtual ~Personaje() = default;

    // Método que cada personaje resolverá con sus propias teclas
    virtual void manejarEntrada() = 0;
    
    // Lógica física y dibujado
    void actualizar(float alturaSuelo);
    void dibujar(sf::RenderWindow& ventana);
};

#endif