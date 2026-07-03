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

    int vidaMaxima = 300;
    int vidaActual = 300;
    sf::RectangleShape barraVidaFondo;
    sf::RectangleShape barraVidaInterior;

    // NUEVO: Estados estilo KOF/Mortal Kombat
    bool agachado = false;
    float cooldownEmpuje = 0.0f; 

public:
    Personaje(const std::string& nombreArchivo, sf::Vector2f posicionInicial);
    virtual ~Personaje() = default;

    virtual void manejarEntrada() = 0;
    void actualizar(float alturaSuelo);
    void dibujar(sf::RenderWindow& ventana);

    sf::Vector2f getPosicion() const { return sprite.getPosition(); }
    int getVida() const { return vidaActual; } // NUEVO: Para detectar el K.O.
    bool esAgachado() const { return agachado; } // NUEVO

    void mirarHacia(float xEnemigo);
    void recibirDanio(int cantidad, float direccionEmpuje); // ACTUALIZADO: Incluye empuje
    sf::FloatRect getCuerpo() const;
    sf::FloatRect getHitboxAtaque(bool esFuerte) const; // ACTUALIZADO: Golpe débil o fuerte
};

#endif