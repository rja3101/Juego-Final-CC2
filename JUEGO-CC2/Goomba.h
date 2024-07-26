#pragma once

#include "Animation.h"
#include "Enemy.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

class Goomba : public Enemy
{
private:
    bool no_collision_dying;
    bool underground;

    unsigned short death_timer;

    sf::Sprite sprite;
    sf::Texture texture;
    Animation walk_animation;

public:
    Goomba(bool i_underground, float i_x, float i_y);

    bool get_dead(bool i_deletion) const override;
    void die(unsigned char i_death_type) override;
    void draw(unsigned i_view_x, sf::RenderWindow& i_window) override;
    void update(unsigned i_view_x, const std::vector<std::shared_ptr<Enemy>>& i_enemies, const MapManager& i_map_manager, Mario& i_mario) override;
};