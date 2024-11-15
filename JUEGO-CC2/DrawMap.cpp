#include <array>
#include <chrono>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <thread>
#include <vector>

#include "Global.h"
#include "DrawMap.h"

void draw_map_segment(unsigned short start_x, unsigned short end_x, unsigned short map_height,
    const sf::Image& i_map_sketch, sf::RenderWindow& i_window,
    const sf::Texture& i_map_texture, const Map& i_map)
{
    sf::Sprite cell_sprite(i_map_texture);

    for (unsigned short a = start_x; a < end_x; ++a)
    {
        for (unsigned short b = 0; b < map_height; ++b)
        {
            unsigned short sprite_x = 0;
            unsigned short sprite_y = 0;

            sf::Color pixel = i_map_sketch.getPixel(a, b + 2 * map_height);
            sf::Color pixel_down = sf::Color(0, 0, 0, 0);
            sf::Color pixel_left = sf::Color(0, 0, 0, 0);
            sf::Color pixel_right = sf::Color(0, 0, 0, 0);
            sf::Color pixel_up = sf::Color(0, 0, 0, 0);

            cell_sprite.setPosition(CELL_SIZE * a, CELL_SIZE * b);

            if (255 == pixel.a)
            {
                if (0 < a)
                {
                    pixel_left = i_map_sketch.getPixel(a - 1, b + 2 * map_height);
                }

                if (0 < b)
                {
                    pixel_up = i_map_sketch.getPixel(a, b + 2 * map_height - 1);
                }

                if (a < i_map_sketch.getSize().x - 1)
                {
                    pixel_right = i_map_sketch.getPixel(1 + a, b + 2 * map_height);
                }

                if (b < map_height - 1)
                {
                    pixel_down = i_map_sketch.getPixel(a, 1 + b + 2 * map_height);
                }

                if (sf::Color(255, 255, 255) == pixel) // Clouds
                {
                    sprite_x = 8;

                    if (sf::Color(255, 255, 255) == pixel_up)
                    {
                        sprite_y = 1;
                    }

                    if (sf::Color(255, 255, 255) == pixel_left)
                    {
                        if (sf::Color(255, 255, 255) != pixel_right)
                        {
                            sprite_x = 9;
                        }
                    }
                    else if (sf::Color(255, 255, 255) == pixel_right)
                    {
                        sprite_x = 7;
                    }
                }
                else if (sf::Color(146, 219, 0) == pixel) // Grass
                {
                    sprite_x = 5;

                    if (sf::Color(146, 219, 0) == pixel_left)
                    {
                        if (sf::Color(146, 219, 0) != pixel_right)
                        {
                            sprite_x = 6;
                        }
                    }
                    else if (sf::Color(146, 219, 0) == pixel_right)
                    {
                        sprite_x = 4;
                    }
                }
                else if (sf::Color(0, 73, 0) == pixel) // Hills outline
                {
                    sprite_y = 1;

                    if (sf::Color(0, 109, 0) == pixel_left)
                    {
                        if (sf::Color(0, 109, 0) != pixel_right)
                        {
                            sprite_x = 2;
                        }
                    }
                    else if (sf::Color(0, 109, 0) == pixel_right)
                    {
                        sprite_x = 1;
                    }
                }
                else if (sf::Color(0, 109, 0) == pixel) // Hills
                {
                    sprite_x = 4;
                    sprite_y = 1;

                    if (sf::Color(0, 73, 0) == pixel_left)
                    {
                        sprite_x = 3;
                    }
                    else if (sf::Color(0, 73, 0) == pixel_right)
                    {
                        sprite_x = 5;
                    }
                }
                else if (sf::Color(109, 255, 85) == pixel) // Flagpole
                {
                    sprite_x = 12;

                    if (sf::Color(109, 255, 85) == pixel_up)
                    {
                        sprite_y = 1;
                    }
                }

                cell_sprite.setTextureRect(sf::IntRect(CELL_SIZE * sprite_x, CELL_SIZE * sprite_y, CELL_SIZE, CELL_SIZE));

                i_window.draw(cell_sprite);
            }

            if (Cell::Empty != i_map[a][b])
            {
                if (Cell::Pipe == i_map[a][b]) // Pipes
                {
                    if (Cell::Pipe == i_map[a][b - 1])
                    {
                        sprite_y = 1;
                    }
                    else
                    {
                        sprite_y = 0;
                    }

                    if (Cell::Pipe == i_map[a - 1][b])
                    {
                        sprite_x = 11;
                    }
                    else
                    {
                        sprite_x = 10;
                    }
                }
                else if (Cell::QuestionBlock == i_map[a][b]) // Question blocks
                {
                    sprite_x = 1;
                    sprite_y = 0;
                }
                else if (Cell::Wall == i_map[a][b])
                {
                    sprite_y = 0;

                    if (sf::Color(0, 0, 0) == i_map_sketch.getPixel(a, b)) // Walls
                    {
                        sprite_x = 2;
                    }
                    else // Solid blocks
                    {
                        sprite_x = 3;
                    }
                }

                cell_sprite.setTextureRect(sf::IntRect(CELL_SIZE * sprite_x, CELL_SIZE * sprite_y, CELL_SIZE, CELL_SIZE));

                i_window.draw(cell_sprite);
            }
        }
    }
}

void draw_map(unsigned i_view_x, const sf::Image& i_map_sketch, sf::RenderWindow& i_window,
    const sf::Texture& i_map_texture, const Map& i_map)
{
    unsigned short map_end = ceil((i_view_x + SCREEN_WIDTH) / static_cast<float>(CELL_SIZE));
    unsigned short map_height = floor(i_map_sketch.getSize().y / 3.f);
    unsigned short map_start = floor(i_view_x / static_cast<float>(CELL_SIZE));

    unsigned short num_threads = std::thread::hardware_concurrency();
    unsigned short segment_width = (map_end - map_start) / num_threads;

    std::vector<std::thread> threads;

    for (unsigned short i = 0; i < num_threads; ++i)
    {
        unsigned short start_x = map_start + i * segment_width;
        unsigned short end_x = (i == num_threads - 1) ? map_end : start_x + segment_width;

        threads.emplace_back(draw_map_segment, start_x, end_x, map_height, std::ref(i_map_sketch),
            std::ref(i_window), std::ref(i_map_texture), std::ref(i_map));
    }

    for (auto& t : threads)
    {
        if (t.joinable())
        {
            t.join();
        }
    }
}