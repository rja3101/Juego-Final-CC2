#pragma once

#include <vector>
#include <memory>
#include <SFML/Graphics/Color.hpp>
#include "Enemy.h"
#include "MapManager.h"
#include "Mario.h"

void convert_sketch(const unsigned char i_current_level, unsigned short& i_level_finish, std::vector<std::shared_ptr<Enemy>>& i_enemies, sf::Color& i_background_color, MapManager& i_map_manager, Mario& i_mario);