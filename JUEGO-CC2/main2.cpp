#include <SFML/Graphics.hpp>
#include "FirstMenu.h"
#include "FireboyWatergirlGame.h"
#include "Monster.h"
#include "Game.h"
#include "Modes.h"
#include "Menu.h"
#include "Button.h"
#include "worldCreator.h"
#include "Settings.h"
#include "Info.h"
#include "SubMenu.h"
#include <ctime>
#include <array>
#include <chrono>
#include <cmath>
#include "Animation.h"
#include "Global.h"
#include "MapManager.h"
#include "Mushroom.h"
#include "Mario.h"
#include "Enemy.h"
#include "Goomba.h"
#include "Koopa.h"
#include "ConvertSketch.h"
#include "Utils.hpp"
int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "FirstMenu");

    // Obtener la instancia única de FirstMenu.
    FirstMenu& firstMenu = FirstMenu::getInstance(window);
    firstMenu.loadMenuImages(
        "C:\\Visual studio\\CCII\\fondo_friv.png",   // Ruta de la imagen de fondo
        "C:\\Visual studio\\CCII\\juego1.png",       // Ruta de la primera imagen de juego
        "C:\\Visual studio\\CCII\\juego2.png",       // Ruta de la segunda imagen de juego
        "C:\\Visual studio\\CCII\\juego3-1.png"      // Ruta de la tercera imagen de juego
    );

    bool startGame1 = false;
    bool startGame2 = false;
    bool startGame3 = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                int clicked = firstMenu.isClicked(sf::Mouse::getPosition(window));
                if (clicked == 1) {
                    startGame1 = true;
                }
                else if (clicked == 2) {
                    startGame2 = true;
                }
                else if (clicked == 3) {
                    startGame3 = true;
                }
            }
        }
        window.clear();

        if (!startGame1 && !startGame2 && !startGame3) {
            firstMenu.draw();
        } else if (startGame1) {
            FireboyWatergirlGame game1;
            game1.run();
            startGame1 = false; // Vuelve a false para que se muestre el menú después del juego
        } else if (startGame2) {

            sf::RenderWindow window(sf::VideoMode(1600, 1000), "Juego_2");
            sf::Image icon;
            if (icon.loadFromFile("C:\\Visual studio\\CCII\\JUEGO-CC2\\texture.png")) {
                window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
            }
            Menu menu("C:\\Visual studio\\CCII\\JUEGO-CC2\\font.ttf", "C:\\Visual studio\\CCII\\JUEGO-CC2\\texture.png");
            SubMenu gameOverMenu("C:\\Visual studio\\CCII\\JUEGO-CC2\\font.ttf", "C:\\Visual studio\\CCII\\JUEGO-CC2\\texture.png", "game_over");  // Menu to be presented upon the player's death
            SubMenu escKeyMenu("C:\\Visual studio\\CCII\\JUEGO-CC2\\font.ttf", "C:\\Visual studio\\CCII\\JUEGO-CC2\\texture.png", "escape_key");   // Menu to be presented upon pressing escape
            sf::Clock clock;
            sf::Time deltaTime;
            sf::View viewGame;
            sf::View viewUI;
            Game game("C:\\Visual studio\\CCII\\JUEGO-CC2\\texture.png", "C:\\Visual studio\\CCII\\JUEGO-CC2\\font.ttf", &window, &viewUI);
            int mode = MAIN_MENU;
            sf::Font font;
            if (!font.loadFromFile("C:\\Visual studio\\CCII\\JUEGO-CC2\\font.ttf")) {}
            Info info(font, "C:\\Visual studio\\CCII\\JUEGO-CC2\\texture.png");
            WorldCreator wCreator(font);
            Settings settings(font);
            window.setFramerateLimit(60);
            sf::Vector2u windowSize = window.getSize();
            float idk = (float)windowSize.y / windowSize.x;
            float idk2 = (1.f - idk) * 0.5;
            viewUI.setViewport(sf::FloatRect(idk2, 0.f, idk, 1));
            viewGame.setViewport(sf::FloatRect(idk2, 0.f, idk, 1));
            window.setView(viewUI);

            bool escapeKeyPressed = false; 
            while (window.isOpen()) {
                window.clear();
                sf::Vector2i windowPosition = sf::Mouse::getPosition(window);
                sf::Vector2f mousePos = window.mapPixelToCoords(windowPosition);
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed && mode != GAME_LOOP) {
                        window.close(); 
                    }
                    else if (event.type == sf::Event::Resized) {
                        sf::Vector2u windowSize = window.getSize();
                        float idk = (float)windowSize.y / windowSize.x;
                        float idk2 = (1.f - idk) * 0.5;
                        viewUI.setViewport(sf::FloatRect(idk2, 0.f, idk, 1));
                        viewGame.setViewport(sf::FloatRect(idk2, 0.f, idk, 1));
                        window.setView(viewUI);
                    }
                    switch (mode) {
                    case MAIN_MENU:
                        menu.update(mousePos);
                        if (event.type == sf::Event::MouseButtonPressed) {
                            if (menu.bExitGame.click(mousePos)) {
                                window.close();
                                startGame2 = false;
                            }
                            if (menu.bNewGame.click(mousePos))      mode = WORLD_CREATOR;
                            if (menu.bDescription.click(mousePos))  mode = INFO_MENU;
                            if (menu.bSettings.click(mousePos))     mode = SETTINGS_MENU;
                        }
                        break;
                    case WORLD_CREATOR:
                        wCreator.update(mousePos);
                        if (event.type == sf::Event::MouseButtonPressed) {
                            wCreator.checkClick(mousePos);
                            if (wCreator.bStartGame.click(mousePos)) {
                                game.changePlayerClass(wCreator.playerClass);
                                game.updateSettings(settings);
                                game.changeMap(wCreator.gameWorld);
                                mode = GAME_LOOP;
                                wCreator.clearVectors();
                            }
                            if (wCreator.bGoBack.click(mousePos)) {
                                mode = MAIN_MENU;
                            }
                        }
                        if (event.type == sf::Event::TextEntered) {
                            if ((event.text.unicode >= 48 && event.text.unicode <= 57) || event.text.unicode == 8) {
                                wCreator.seedInput.addCharacter(static_cast<char>(event.text.unicode));
                            }
                        }
                        break;
                    case GAME_LOOP:
                        if (event.type == sf::Event::KeyPressed) {
                            if (event.key.code == sf::Keyboard::Escape && !game.player->isDead()) {
                                escapeKeyPressed = !game.paused ? true : false;
                                game.paused = !game.paused;
                            }
                        }
                        if (event.type == sf::Event::Closed && !game.player->isDead()) {
                            escapeKeyPressed = !game.paused ? true : false;
                            game.paused = !game.paused;
                        }
                        break;
                    case SETTINGS_MENU:
                        settings.update(mousePos);
                        settings.checkClick(mousePos);

                        if (settings.bGoBack.click(mousePos) && !escapeKeyPressed)
                            mode = MAIN_MENU; 

                        if (settings.bGoBack.click(mousePos) && escapeKeyPressed) {
                            mode = GAME_LOOP; 
                            game.updateSettings(settings); 
                        }
                        break;
                    case INFO_MENU:
                        info.update(mousePos);
                        info.checkClick(mousePos);
                        if (info.goBack.click(mousePos)) {
                            mode = MAIN_MENU;
                        }
                        break;
                    default: break;
                    }
                }
                switch (mode) {
                case MAIN_MENU:
                    window.draw(menu);
                    break;
                case WORLD_CREATOR:
                    window.draw(wCreator);
                    break;
                case GAME_LOOP:
                    window.setView(viewGame);
                    mousePos = window.mapPixelToCoords(windowPosition);

                    game.update(deltaTime, mousePos);
                    viewGame.setCenter(game.player->getCenter());
                    window.draw(game);

                    //  Menu to be presented upon the player's death
                    if (game.player->isDead()) {

                        game.paused = true;
                        mousePos = window.mapPixelToCoords(windowPosition);
                        gameOverMenu.update(mousePos);
                        window.draw(gameOverMenu);

                        if (event.type == sf::Event::MouseButtonPressed) {

                            if (gameOverMenu.bExitGame.click(mousePos)) {
                                window.close();
                                startGame2 = false;
                            }

                            if (gameOverMenu.bMainMenu.click(mousePos)) {
                                mode = MAIN_MENU;
                                game.paused = false;

                                // Recreating the game object was the only way I found to reset the game.
                                game.reset();
                            }
                        }
                    }
                    break;
                case SETTINGS_MENU:
                    window.draw(settings);
                    break;
                case INFO_MENU:
                    window.draw(info);
                    break;
                default: break;
                }

                // Menu to be presented upon pressing escape
                if (escapeKeyPressed && mode == GAME_LOOP) {

                    game.paused = true;
                    mousePos = window.mapPixelToCoords(windowPosition);
                    escKeyMenu.update(mousePos);
                    window.draw(escKeyMenu);

                    if (event.type == sf::Event::MouseButtonPressed) {

                        if (escKeyMenu.bResume.click(mousePos)) {
                            game.paused = false;
                            escapeKeyPressed = false;
                        }
                        if (escKeyMenu.bSettings.click(mousePos))
                            mode = SETTINGS_MENU;

                        if (escKeyMenu.bExitGame.click(mousePos)) {
                            window.close();
                            startGame2 = false;
                        }

                        if (escKeyMenu.bMainMenu.click(mousePos)) {
                            mode = MAIN_MENU;
                            game.paused = false;
                            escapeKeyPressed = false;


                            game.monsters.clear();
                            game.projectiles.clear();
                            for (auto& x : game.particleSystem)
                            {
                                x.emitters.clear();
                                x.textEmitters.clear();
                            }
                            game.reset();
                        }
                    }
                }

                window.display();
                deltaTime = clock.restart();
            }
            startGame2 = false; 
        }
        else if (startGame3) {
            unsigned char current_level = 0;

            unsigned short level_finish = 0;

            std::chrono::microseconds lag(0);

            std::chrono::steady_clock::time_point previous_time;

            std::vector<std::shared_ptr<Enemy>> enemies;

            sf::Color background_color = sf::Color(0, 219, 255);

            sf::Event event;

            sf::RenderWindow window(sf::VideoMode(SCREEN_RESIZE* SCREEN_WIDTH, SCREEN_RESIZE* SCREEN_HEIGHT), "Super Mario Bros", sf::Style::Close);
            window.setPosition(sf::Vector2i(window.getPosition().x, window.getPosition().y - 90));

            sf::View view(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));

            MapManager map_manager;

            Mario mario;

            convert_sketch(current_level, level_finish, enemies, background_color, map_manager, mario);

            previous_time = std::chrono::steady_clock::now();

            while (1 == window.isOpen())
            {
                std::chrono::microseconds delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previous_time);

                lag += delta_time;

                previous_time += delta_time;

                while (FRAME_DURATION <= lag)
                {
                    unsigned view_x;

                    lag -= FRAME_DURATION;

                    while (1 == window.pollEvent(event))
                    {
                        switch (event.type)
                        {
                        case sf::Event::Closed:
                        {
                            window.close();

                            break;
                        }
                        case sf::Event::KeyPressed:
                        {
                            switch (event.key.code)
                            {
                            case sf::Keyboard::Enter:
                            {
                                enemies.clear();

                                mario.reset();

                                convert_sketch(current_level, level_finish, enemies, background_color, map_manager, mario);
                            }
                            }
                        }
                        }
                    }

                    //Once Mario goes beyond the finish, we move on to the next level.
                    if (CELL_SIZE * level_finish <= mario.get_x())
                    {
                        current_level++;

                        enemies.clear();

                        mario.reset();

                        convert_sketch(current_level, level_finish, enemies, background_color, map_manager, mario);
                    }

                    //Keeping Mario at the center of the view.
                    view_x = Utils::clamp(round(mario.get_x()) - 0.5f * (SCREEN_WIDTH - CELL_SIZE), 0, CELL_SIZE * map_manager.get_map_width() - SCREEN_WIDTH);

                    map_manager.update();

                    mario.update(view_x, map_manager);

                    for (unsigned short a = 0; a < enemies.size(); a++)
                    {
                        enemies[a]->update(view_x, enemies, map_manager, mario);
                    }

                    for (unsigned short a = 0; a < enemies.size(); a++)
                    {
                        if (1 == enemies[a]->get_dead(1))
                        {
                            //We don't have to worry about memory leaks since we're using SMART POINTERS!
                            enemies.erase(a + enemies.begin());

                            a--;
                        }
                    }

                    if (FRAME_DURATION > lag)
                    {
                        view.reset(sf::FloatRect(view_x, 0, SCREEN_WIDTH, SCREEN_HEIGHT));

                        window.setView(view);
                        window.clear(background_color);

                        //If the background color is sf::Color(0, 0, 85), the level is underground.
                        map_manager.draw_map(1, sf::Color(0, 0, 85) == background_color, view_x, window);

                        mario.draw_mushrooms(view_x, window);

                        map_manager.draw_map(0, sf::Color(0, 0, 85) == background_color, view_x, window);

                        for (unsigned short a = 0; a < enemies.size(); a++)
                        {
                            enemies[a]->draw(view_x, window);
                        }

                        mario.draw(window);

                        window.display();
                    }
                }
            }
            startGame3 = false; // Vuelve a false para que se muestre el menú después del juego
        }

        window.display();
    }

    return 0;
}
