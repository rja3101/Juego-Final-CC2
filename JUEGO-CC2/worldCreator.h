#ifndef WORLDCREATOR_H
#define WORLDCREATOR_H

#include "Button.h"
#include "perlinNoise.h"
#include "Textbox.h"
#include "Subject.h"
#include <iomanip>
#include "Utils.h"
#include "World.h"

class WorldCreator : public sf::Drawable, public Subject {

public:
    int octaves = 4;
    float bias = 4.f;
    uint32_t seed;

    int playerClass = 0;
    Button bIncreaseOctaves;
    Button bDecreaseOctaves;

    Button bIncreaseBias;
    Button bDecreaseBias;

    Button bRandomizeSeed;
    Button bConfirmSeed;

    Button bChangeClass;

    Button bStartGame;

    Button bGoBack;

    Textbox seedInput;

    World gameWorld;

    WorldCreator();
    WorldCreator(sf::Font& font);

    void update(sf::Vector2f pos);
    void checkClick(sf::Vector2f pos);
    void clearVectors();

private:
    sf::Text biasText;
    sf::Text octavesText;
    sf::Text classText;

    sf::Text titleText;

    sf::Text seedLabel;
    sf::Text biasLabel;
    sf::Text octavesLabel;

    sf::Texture diceTexture;
    sf::Sprite diceSprite;

    void changeBias(float amount);
    void changeOctaves(int amount);

    void randomizeSeed();
    void changeSeed(size_t s);
    void changeClass();
    void updateMap();
    Rnd rnd;
    std::vector<float> randomValues2d;
    std::vector<float> noiseValues2d;
    sf::VertexArray gameMap;

    sf::RectangleShape background;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // WORLDCREATOR_H
