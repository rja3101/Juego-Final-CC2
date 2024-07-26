#include "FireboyWatergirlGame.h"
#include "FireboyWatergirlPlayer.h"
#include <iostream>

// Constantes para velocidades y gravedad
const float SPEED = 0.5f;
const float GRAVITY = 0.013f;
const float JUMP_FORCE = 2.35f;
const float GROUND_HEIGHT = 850.f;

// Definiciones de rutas de textura para el fondo, suelo, Fireboy y Watergirl
#define BLOQUE_FONDO "C:\\Visual studio\\CCII\\fondo.png"
#define BLOQUE_SUELO "C:\\Visual studio\\CCII\\bloque.png"
#define GEMA_AZUL_PATH "C:\\Visual studio\\CCII\\gema_azul.png"
#define GEMA_ROJA_PATH "C:\\Visual studio\\CCII\\gema_roja.png"
#define PAUSA_IMAGEN_PATH "C:\\Visual studio\\CCII\\menu_juego1.png"

// Constructor: inicializa la ventana y los jugadores (Fireboy y Watergirl)
FireboyWatergirlGame::FireboyWatergirlGame()
    : window(sf::VideoMode(1200u, 900u), "Fireboy and Watergirl"),
    fireboy("fireboy.png"), watergirl("watergirl.png"),
    fireboyGemaRojaObtenida(false), watergirlGemaAzulObtenida(false) {

    // Cargar textura de fondo
    if (!backgroundTexture.loadFromFile(BLOQUE_FONDO)) {
        std::cerr << "Error al cargar la textura de fondo desde " << BLOQUE_FONDO << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);

    // Cargar textura de suelo
    if (!groundTexture.loadFromFile(BLOQUE_SUELO)) {
        std::cerr << "Error al cargar la textura del suelo desde " << BLOQUE_SUELO << std::endl;
    }
    groundSprite.setTexture(groundTexture);
    // Cargar textura de gema azul
    if (!gemaAzulTexture.loadFromFile(GEMA_AZUL_PATH)) {
        std::cerr << "Error al cargar la textura de la gema azul desde " << GEMA_AZUL_PATH << std::endl;
    }
    gemaAzulSprite.setTexture(gemaAzulTexture);

    // Cargar textura de gema roja
    if (!gemaRojaTexture.loadFromFile(GEMA_ROJA_PATH)) {
        std::cerr << "Error al cargar la textura de la gema roja desde " << GEMA_ROJA_PATH << std::endl;
    }
    gemaRojaSprite.setTexture(gemaRojaTexture);
    // Cargar la textura para el menú de pausa
    if (!pauseTexture.loadFromFile(PAUSA_IMAGEN_PATH)) {
        std::cerr << "Error al cargar la textura de pausa desde " << PAUSA_IMAGEN_PATH << std::endl;
    }
    pauseSprite.setTexture(pauseTexture);
    pauseSprite.setPosition((window.getSize().x - pauseSprite.getGlobalBounds().width) / 2.f, (window.getSize().y - pauseSprite.getGlobalBounds().height) / 2.f);
    // Posicionar a Fireboy y Watergirl en el suelo
    fireboy.setPosition(100.f, GROUND_HEIGHT - fireboy.getBounds().height);
    watergirl.setPosition(200.f, GROUND_HEIGHT - watergirl.getBounds().height);

    // Configurar plataformas
    sf::RectangleShape plataforma1(sf::Vector2f(300.f, 20.f));
    plataforma1.setFillColor(sf::Color::White);
    plataforma1.setTexture(&groundTexture);
    plataforma1.setPosition(150.f, 700.f);
    platforms.push_back(plataforma1);

    sf::RectangleShape plataforma2(sf::Vector2f(300.f, 20.f));
    plataforma2.setFillColor(sf::Color::White);
    plataforma2.setTexture(&groundTexture);
    plataforma2.setPosition(550.f, 500.f);
    platforms.push_back(plataforma2);

    sf::RectangleShape plataforma3(sf::Vector2f(300.f, 20.f));
    plataforma3.setFillColor(sf::Color::White);
    plataforma3.setTexture(&groundTexture);
    plataforma3.setPosition(900.f, 300.f);
    platforms.push_back(plataforma3);

    sf::RectangleShape plataforma4(sf::Vector2f(350.f, 20.f));
    plataforma4.setFillColor(sf::Color::White);
    plataforma4.setTexture(&groundTexture);
    plataforma4.setPosition(50.f, 400.f);
    platforms.push_back(plataforma4);

    // Configurar áreas de fuego y agua
    fireArea.setSize(sf::Vector2f(80.f, 15.f));
    fireArea.setFillColor(sf::Color::Red);
    fireArea.setPosition(500.f, GROUND_HEIGHT - 20.f);

    waterArea.setSize(sf::Vector2f(80.f, 15.f));
    waterArea.setFillColor(sf::Color::Blue);
    waterArea.setPosition(700.f, GROUND_HEIGHT - 20.f);

    // Configurar puertas de salida
    fireDoor.setSize(sf::Vector2f(50.f, 100.f));
    fireDoor.setFillColor(sf::Color::Red);
    fireDoor.setPosition(1100.f, 200.f);

    waterDoor.setSize(sf::Vector2f(50.f, 100.f));
    waterDoor.setFillColor(sf::Color::Blue);
    waterDoor.setPosition(80.f, 300.f);
}

// Bucle principal del juego - pattern Game loop
void FireboyWatergirlGame::run() {
    while (window.isOpen()) {
        processEvents();
        if (!isPaused) {
            update();
        }
        render();
    }
}

// Procesa eventos de la ventana
void FireboyWatergirlGame::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        // Pausar o despausar el juego
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
            togglePause();
        }
    }

    // Controles de salto para Fireboy y Watergirl
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        fireboy.jump(JUMP_FORCE);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        watergirl.jump(JUMP_FORCE);
    }
}

// Actualiza la lógica del juego
void FireboyWatergirlGame::update() {
    // Limitar el movimiento dentro de los límites de la ventana
    sf::FloatRect bounds(5.f, 5.f, static_cast<float>(window.getSize().x) - 10.f, static_cast<float>(window.getSize().y) - 10.f);

    // Movimiento horizontal y aplicación de gravedad para Fireboy y Watergirl
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && fireboy.getBounds().left > bounds.left) {
        fireboy.move(-SPEED, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && fireboy.getBounds().left + fireboy.getBounds().width < bounds.left + bounds.width) {
        fireboy.move(SPEED, 0.f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && watergirl.getBounds().left > bounds.left) {
        watergirl.move(-SPEED, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && watergirl.getBounds().left + watergirl.getBounds().width < bounds.left + bounds.width) {
        watergirl.move(SPEED, 0.f);
    }

    // Aplicar gravedad a Fireboy y Watergirl
    fireboy.applyGravity(GRAVITY, GROUND_HEIGHT);
    watergirl.applyGravity(GRAVITY, GROUND_HEIGHT);

    // Verificar colisiones entre los personajes y el entorno
    checkCollisions();
}
// Alterna el estado de pausa del juego
void FireboyWatergirlGame::togglePause() {
    isPaused = !isPaused;
}

// Dibuja el menú de pausa
void FireboyWatergirlGame::drawPauseMenu() {
    window.draw(pauseSprite);
}
// Renderiza todos los elementos en la ventana
void FireboyWatergirlGame::render() {
    window.clear(sf::Color::Black);

    // Dibujar el fondo en mosaico
    for (int x = 0; x < window.getSize().x; x += backgroundTexture.getSize().x) {
        for (int y = 0; y < window.getSize().y; y += backgroundTexture.getSize().y) {
            backgroundSprite.setPosition(x, y);
            window.draw(backgroundSprite);
        }
    }

    // Dibujar el suelo en mosaico
    for (int x = 0; x < window.getSize().x; x += groundTexture.getSize().x) {
        groundSprite.setPosition(x, GROUND_HEIGHT - groundTexture.getSize().y);
        window.draw(groundSprite);
    }

    // Dibujar las plataformas
    for (const auto& platform : platforms) {
        window.draw(platform);
    }

    // Dibujar áreas de fuego y agua, y puertas
    window.draw(fireArea);
    window.draw(waterArea);
    window.draw(fireDoor);
    window.draw(waterDoor);
    // Dibujar las gemas solo si no han sido obtenidas
    if (!watergirlGemaAzulObtenida) {
        gemaAzulSprite.setPosition(600.f, GROUND_HEIGHT - 100.f);
        window.draw(gemaAzulSprite);
    }

    if (!fireboyGemaRojaObtenida) {
        gemaRojaSprite.setPosition(300.f, GROUND_HEIGHT - 200.f);
        window.draw(gemaRojaSprite);
    }

    // Dibujar a Fireboy y Watergirl
    fireboy.draw(window);
    watergirl.draw(window);


    if (isPaused) {
        drawPauseMenu();
    }

    window.display();
}
// Reinicia la posición y velocidad de Fireboy y Watergirl
void FireboyWatergirlGame::resetGame() {
    fireboy.setPosition(100.f, GROUND_HEIGHT - fireboy.getBounds().height);
    watergirl.setPosition(200.f, GROUND_HEIGHT - watergirl.getBounds().height);
    fireboy.resetVerticalSpeed();
    watergirl.resetVerticalSpeed();
}

// Verifica las colisiones entre los personajes y el entorno
void FireboyWatergirlGame::checkCollisions() {
    // Colisiones entre Watergirl y el área de fuego
    if (watergirl.getBounds().intersects(fireArea.getGlobalBounds())) {
        resetGame();
    }

    // Colisiones entre Fireboy y el área de agua
    if (fireboy.getBounds().intersects(waterArea.getGlobalBounds())) {
        resetGame();
    }

    // Colisión con puertas de salida
    if (fireboy.getBounds().intersects(fireDoor.getGlobalBounds()) && watergirl.getBounds().intersects(waterDoor.getGlobalBounds())) {
        window.close();
    }
    if (!fireboyGemaRojaObtenida && fireboy.getBounds().intersects(gemaRojaSprite.getGlobalBounds())) {
        fireboyGemaRojaObtenida = true;  // Fireboy obtiene la gema roja
    }

    // Colisiones entre Watergirl y la gema azul
    if (!watergirlGemaAzulObtenida && watergirl.getBounds().intersects(gemaAzulSprite.getGlobalBounds())) {
        watergirlGemaAzulObtenida = true;  // Watergirl obtiene la gema azul
    }
    // Colisiones con plataformas
    for (auto& platform : platforms) {
        // Verificar colisiones verticales para Fireboy
        if (fireboy.getBounds().intersects(platform.getGlobalBounds())) {
            // Verificar colisiones verticales
            if (fireboy.getVerticalSpeed() > 0 && fireboy.getBounds().top + fireboy.getBounds().height - fireboy.getVerticalSpeed() <= platform.getPosition().y) {
                fireboy.setPosition(fireboy.getBounds().left, platform.getPosition().y - fireboy.getBounds().height);
                fireboy.resetVerticalSpeed();
                fireboy.setOnGround(true); // Establecer que está en el suelo
            }
            else if (fireboy.getVerticalSpeed() < 0 && fireboy.getBounds().top >= platform.getPosition().y + platform.getSize().y) {
                fireboy.setPosition(fireboy.getBounds().left, platform.getPosition().y + platform.getSize().y);
                fireboy.resetVerticalSpeed();
            }
        }
        // Verificar colisiones horizontales para Fireboy
        if (fireboy.getBounds().intersects(platform.getGlobalBounds())) {
            if (fireboy.getBounds().left < platform.getPosition().x + platform.getSize().x && fireboy.getBounds().left + fireboy.getBounds().width > platform.getPosition().x) {
                if (fireboy.getBounds().top + fireboy.getBounds().height > platform.getPosition().y && fireboy.getBounds().top < platform.getPosition().y + platform.getSize().y) {
                    if (fireboy.getBounds().left < platform.getPosition().x) {
                        fireboy.setPosition(platform.getPosition().x - fireboy.getBounds().width, fireboy.getBounds().top);
                    }
                    else {
                        fireboy.setPosition(platform.getPosition().x + platform.getSize().x, fireboy.getBounds().top);
                    }
                }
            }
        }

        // Verificar colisiones verticales para Watergirl
        if (watergirl.getBounds().intersects(platform.getGlobalBounds())) {
            // Verificar colisiones verticales
            if (watergirl.getVerticalSpeed() > 0 && watergirl.getBounds().top + watergirl.getBounds().height - watergirl.getVerticalSpeed() <= platform.getPosition().y) {
                watergirl.setPosition(watergirl.getBounds().left, platform.getPosition().y - watergirl.getBounds().height);
                watergirl.resetVerticalSpeed();
                watergirl.setOnGround(true); // Establecer que está en el suelo
            }
            else if (watergirl.getVerticalSpeed() < 0 && watergirl.getBounds().top >= platform.getPosition().y + platform.getSize().y) {
                watergirl.setPosition(watergirl.getBounds().left, platform.getPosition().y + platform.getSize().y);
                watergirl.resetVerticalSpeed();
            }
        }
        // Verificar colisiones horizontales para Watergirl
        if (watergirl.getBounds().intersects(platform.getGlobalBounds())) {
            if (watergirl.getBounds().left < platform.getPosition().x + platform.getSize().x && watergirl.getBounds().left + watergirl.getBounds().width > platform.getPosition().x) {
                if (watergirl.getBounds().top + watergirl.getBounds().height > platform.getPosition().y && watergirl.getBounds().top < platform.getPosition().y + platform.getSize().y) {
                    if (watergirl.getBounds().left < platform.getPosition().x) {
                        watergirl.setPosition(platform.getPosition().x - watergirl.getBounds().width, watergirl.getBounds().top);
                    }
                    else {
                        watergirl.setPosition(platform.getPosition().x + platform.getSize().x, watergirl.getBounds().top);
                    }
                }
            }
        }
    }
}