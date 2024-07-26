#ifndef FIREBOY_WATERGIRL_PLAYER_H
#define FIREBOY_WATERGIRL_PLAYER_H

#include <SFML/Graphics.hpp>
#include <future>
#include <string>

class FireboyWatergirlPlayer {
public:
    FireboyWatergirlPlayer(const std::string& textureFile);
    void setPosition(float x, float y); 
    void move(float offsetX, float offsetY); 
    void draw(sf::RenderWindow& window);
    void applyGravity(float gravity, float groundHeight); 
    void jump(float jumpForce); 
    sf::FloatRect getBounds() const; 
    void resetVerticalSpeed(); 
    bool isOnGround() const; 
    float getVerticalSpeed() const; 
    void setOnGround(bool onGround);

private:
    sf::Texture texture; 
    sf::Sprite sprite; 
    float verticalSpeed;
    bool onGround; //
};

#endif // FIREBOY_WATERGIRL_PLAYER_H




