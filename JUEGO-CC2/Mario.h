#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include "Animation.h"
#include "Mushroom.h"  // Incluye el encabezado para la clase Mushroom
#include "MapManager.h"  // Incluye el encabezado para la clase MapManager

class Mario
{
private:
    bool crouching;
    bool dead;
    bool flipped;
    bool on_ground;
    float enemy_bounce_speed;
    float horizontal_speed;
    float vertical_speed;
    float x;
    float y;
    unsigned char jump_timer;
    unsigned char powerup_state;

    unsigned short death_timer;
    unsigned short growth_timer;
    unsigned short invincible_timer;

    std::vector<Mushroom> mushrooms;

    sf::Sprite sprite;
    sf::Texture texture;

    Animation big_walk_animation;
    Animation walk_animation;

public:
    Mario();

    bool get_dead() const;

    float get_vertical_speed() const;
    float get_x() const;

    void die(bool i_instant_death);
    void draw(sf::RenderWindow& i_window);
    void draw_mushrooms(unsigned i_view_x, sf::RenderWindow& i_window);
    void reset();
    void set_position(float i_x, float i_y);
    void set_vertical_speed(float i_value);
    void update(unsigned i_view_x, MapManager& i_map_manager);

    sf::FloatRect get_hit_box() const;
};