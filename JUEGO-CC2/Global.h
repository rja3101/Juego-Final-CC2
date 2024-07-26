#pragma once

#include <array>
#include <chrono>
#include <vector>

// Constantes del juego
constexpr float BRICK_PARTICLE_SPEED = 4.0f;
constexpr float COIN_JUMP_SPEED = -6.0f;
constexpr float GOOMBA_SPEED = 1.0f;
constexpr float GRAVITY = 0.25f;
constexpr float KOOPA_SHELL_SPEED = 4.0f;
constexpr float KOOPA_SPEED = 1.0f;
constexpr float MARIO_ACCELERATION = 0.25f;
constexpr float MARIO_JUMP_SPEED = -4.0f;
constexpr float MARIO_WALK_SPEED = 2.0f;
constexpr float MAX_VERTICAL_SPEED = 8.0f;
constexpr float MUSHROOM_SPEED = 1.0f;

constexpr unsigned char CELL_SIZE = 16;
constexpr unsigned char MARIO_BLINKING = 4;
constexpr unsigned char MARIO_DEATH_DURATION = 32;
constexpr unsigned char MARIO_GROWTH_DURATION = 64;
constexpr unsigned char MARIO_INVINCIBILITY_DURATION = 128;
constexpr unsigned char MARIO_JUMP_TIMER = 8;
constexpr unsigned char SCREEN_RESIZE = 2;

constexpr unsigned short COIN_ANIMATION_SPEED = 4;
constexpr unsigned short ENTITY_UPDATE_AREA = 64;
constexpr unsigned short GOOMBA_DEATH_DURATION = 32;
constexpr unsigned short GOOMBA_WALK_ANIMATION_SPEED = 32;
constexpr unsigned short KOOPA_GET_OUT_ANIMATION_SPEED = 4;
constexpr unsigned short KOOPA_GET_OUT_DURATION = 512;
constexpr unsigned short KOOPA_WALK_ANIMATION_SPEED = 32;
constexpr unsigned short MARIO_WALK_ANIMATION_SPEED = 4;
constexpr unsigned short QUESTION_BLOCK_ANIMATION_SPEED = 8;
constexpr unsigned short SCREEN_HEIGHT = 240;
constexpr unsigned short SCREEN_WIDTH = 320;

constexpr std::chrono::microseconds FRAME_DURATION(16667);

enum class Cell
{
    ActivatedQuestionBlock,
    Brick,
    Coin,
    Empty,
    Pipe,
    QuestionBlock,
    Wall
};

// Estructura para objetos en el juego
struct Object
{
    float horizontal_speed;
    float vertical_speed;
    float x;
    float y;

    Object(float i_x, float i_y, float i_horizontal_speed = 0, float i_vertical_speed = 0) :
        horizontal_speed(i_horizontal_speed),
        vertical_speed(i_vertical_speed),
        x(i_x),
        y(i_y)
    {
    }
};

// Mapa del juego
using Map = std::vector<std::array<Cell, SCREEN_HEIGHT / CELL_SIZE>>;