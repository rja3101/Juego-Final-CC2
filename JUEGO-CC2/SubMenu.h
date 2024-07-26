#ifndef SUB_MENU_H
#define SUB_MENU_H

#include "Game.h"
#include "Button.h"
#include <SFML/Graphics.hpp>
#include "perlinNoise.h"


class SubMenu : public sf::Drawable {

public:
    sf::Text logo;
    Button bMainMenu;
    Button bResume;
    Button bExitGame;
    Button bSettings;

    sf::RectangleShape overlay;
    SubMenu(std::string fontPath, std::string texturePath, std::string menu_type);
    void update(sf::Vector2f pos);

private:
    std::string menuType;
    sf::Font font;
    sf::Texture texture;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
#endif // SUB_MENU_H
