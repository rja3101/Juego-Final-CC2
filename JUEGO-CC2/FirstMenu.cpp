#include "FirstMenu.h"
#include <iostream>

FirstMenu::FirstMenu(sf::RenderWindow& window) : window(window) {}

void FirstMenu::loadMenuImages(const std::string& backgroundPath, const std::string& image1Path, const std::string& image2Path, const std::string& image3Path) {
    if (!backgroundTexture.loadFromFile(backgroundPath)) {
        std::cerr << "Error loading background image: " << backgroundPath << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setPosition(0, 0);

    if (!texture1.loadFromFile(image1Path)) {
        std::cerr << "Error loading image: " << image1Path << std::endl;
    }
    sprite1.setTexture(texture1);
    sprite1.setPosition(SPRITE1_X, SPRITE1_Y);

    if (!texture2.loadFromFile(image2Path)) {
        std::cerr << "Error loading image: " << image2Path << std::endl;
    }
    sprite2.setTexture(texture2);
    sprite2.setPosition(SPRITE2_X, SPRITE2_Y);

    if (!texture3.loadFromFile(image3Path)) {
        std::cerr << "Error loading image: " << image3Path << std::endl;
    }
    sprite3.setTexture(texture3);
    sprite3.setPosition(SPRITE3_X, SPRITE3_Y);

    rect1 = sprite1.getGlobalBounds();
    rect2 = sprite2.getGlobalBounds();
    rect3 = sprite3.getGlobalBounds();
}

void FirstMenu::draw() {
    window.draw(backgroundSprite);
    window.draw(sprite1);
    window.draw(sprite2);
    window.draw(sprite3);
}

int FirstMenu::isClicked(const sf::Vector2i& mousePos) {
    if (rect1.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
        return 1;
    }
    if (rect2.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
        return 2;
    }
    if (rect3.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
        return 3;
    }
    return 0;
}
