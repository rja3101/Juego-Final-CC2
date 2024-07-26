#pragma once

#include "Animation.h"
#include "Enemy.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

class Koopa : public Enemy
{
private:
    // Usado para asegurar que solo se chequea la colisión con Mario una vez
    bool check_collision;
    bool flipped;

    // Variables para manejar el estado y animaciones de Koopa
    bool no_collision_dying;
    bool underground;

    unsigned char state; // 0 - Koopa walk, 1 - Koopa shell, 2 - Koopa shell slide
    unsigned short get_out_timer;

    sf::Sprite sprite;
    sf::Texture texture;

    Animation get_out_animation;
    Animation walk_animation;

public:
    Koopa(bool i_underground, float i_x, float i_y);

    bool get_dead(bool i_deletion) const override;
    void die(unsigned char i_death_type) override;
    void draw(unsigned i_view_x, sf::RenderWindow& i_window) override;
    void update(unsigned i_view_x, const std::vector<std::shared_ptr<Enemy>>& i_enemies, const MapManager& i_map_manager, Mario& i_mario) override;
};