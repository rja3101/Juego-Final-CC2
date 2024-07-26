#ifndef WORLD_H
#define WORLD_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "perlinNoise.h"
#include "Unit.h"
#include "Tile.h"
#include "Biomes.h"
#include <iostream>

class World : public sf::Drawable {

private:
    Rnd rnd;


    unsigned sizeX;
    unsigned sizeY;
    unsigned seed;
    unsigned tilesAmount;
    float tileSize = 64.f; // length of one tile in pixels
    unsigned biomeTileSize = 64; // length of one biome in tiles

    unsigned octaves;
    float bias;

    sf::Texture tileTexture;
    sf::VertexArray tilesToDraw;
    sf::VertexArray spritesToDraw;
    std::vector<unsigned short> tilesInfo;
    std::vector<float> objsInfo;
    std::vector<Biomes> biomes;
    std::vector<sf::VertexArray> nearbyBiomes;
    sf::Vector2i playerBiomePos;

    void generateBiomes();

    void generateTiles(const sf::Vector2f& playerPos);


    void biomeBlend(const sf::Vector2f& playerPos);

    void setTileTexture(unsigned tileIndex, unsigned biomeIndex, unsigned textureID, unsigned biomeID, const sf::Vector2f& biomeCoords, const sf::Vector2f& tileCoords);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
    World(unsigned sizeX, unsigned sizeY, std::vector<float> biomeValues);
    World(unsigned sizeX, unsigned sizeY, unsigned seed, unsigned octaves, float bias);
    World();
    void setTexture(const std::string& path);

    void generateNewWorld();

    void update(sf::Time& elapsed, const sf::Vector2f& playerPos);
    unsigned getSizeX() const;
    unsigned getSizeY() const;

    unsigned getSeed() const;

    Biomes getBiome(unsigned x, unsigned y) const;

    void setSizeX(unsigned x);

    void setSizeY(unsigned y);

    void setSeed(unsigned s);

    void setBias(float b);

    void setOctaves(unsigned o);

    static std::vector<sf::Color> biomeColors;
};
#endif