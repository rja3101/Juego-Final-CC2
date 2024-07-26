#ifndef FIREBOYWATERGIRLGAME_H
#define FIREBOYWATERGIRLGAME_H

#include <SFML/Graphics.hpp>
#include "FireboyWatergirlPlayer.h"
class FireboyWatergirlGame {
public:
    FireboyWatergirlGame(); // Constructor de la clase FireboyWatergirlGame
    void run(); // Función principal para ejecutar el juego

private:
    void processEvents(); // Procesa los eventos de entrada
    void update(); // Actualiza la lógica del juego
    void render(); // Renderiza los elementos del juego
    void resetGame(); // Reinicia el juego
    void checkCollisions(); // Verifica las colisiones en el juego

    bool fireboyGemaRojaObtenida; //Valor para ver si cogio la gema roja
    bool watergirlGemaAzulObtenida;  //Valor para ver si cogio la gema azul

    void togglePause(); // Nueva función para pausar/despausar el juego
    void drawPauseMenu(); // Nueva función para dibujar el menú de pausa  

    sf::RenderWindow window; // Ventana principal del juego
    FireboyWatergirlPlayer fireboy; // Jugador Fireboy
    FireboyWatergirlPlayer watergirl; // Jugador Watergirl
    std::vector<sf::RectangleShape> platforms; // Vector de plataformas
    sf::RectangleShape fireArea; // Área de fuego
    sf::RectangleShape waterArea; // Área de agua
    sf::RectangleShape fireDoor; // Puerta de Fireboy
    sf::RectangleShape waterDoor; // Puerta de Watergirl
    sf::Texture backgroundTexture; // Textura del fondo
    sf::Sprite backgroundSprite; // Sprite del fondo
    sf::Texture groundTexture; // Textura del suelo
    sf::Sprite groundSprite; // Sprite del suelo
    sf::Texture pauseTexture; // Textura del menu de pausa
    sf::Sprite pauseSprite; //Sprite del menu de pausa
    sf::Texture gemaAzulTexture; // Textura de la gema azul
    sf::Sprite gemaAzulSprite; // Sprite de la gema azul

    sf::Texture gemaRojaTexture; // Textura de la gema roja
    sf::Sprite gemaRojaSprite; // Sprite de la gema roja

    bool isPaused; // Variable para manejar el estado de pausa
    sf::Font font; // Fuente para el texto del menú de pausa
    sf::Text pauseText; // Texto para el menú de pausa

};

#endif // FIREBOYWATERGIRLGAME_H
