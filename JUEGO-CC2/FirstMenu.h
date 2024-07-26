#ifndef FIRSTMENU_H
#define FIRSTMENU_H

#include <SFML/Graphics.hpp>

class FirstMenu {
public:

    // Método estático para obtener la única instancia de FirstMenu.
    static FirstMenu& getInstance(sf::RenderWindow& window) {
        static FirstMenu instance(window);// Instancia única de FirstMenu.
        return instance;
    }

    void loadMenuImages(const std::string& backgroundPath, const std::string& image1Path, const std::string& image2Path, const std::string& image3Path);
    void draw();
    int isClicked(const sf::Vector2i& mousePos);

    static constexpr float SPRITE1_X = 100.0f;
    static constexpr float SPRITE1_Y = 200.0f;
    static constexpr float SPRITE2_X = 300.0f;
    static constexpr float SPRITE2_Y = 200.0f;
    static constexpr float SPRITE3_X = 500.0f;
    static constexpr float SPRITE3_Y = 200.0f;

private:
    FirstMenu(sf::RenderWindow& window);
    FirstMenu(const FirstMenu&) = delete;
    FirstMenu& operator=(const FirstMenu&) = delete;

    sf::RenderWindow& window;
    sf::Texture backgroundTexture;
    sf::Texture texture1;
    sf::Texture texture2;
    sf::Texture texture3;
    sf::Sprite backgroundSprite;
    sf::Sprite sprite1;
    sf::Sprite sprite2;
    sf::Sprite sprite3;
    sf::FloatRect rect1;
    sf::FloatRect rect2;
    sf::FloatRect rect3;
};

#endif // FIRSTMENU_H
