#include "globals.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include "Stickman.h"
#include <iostream>
#include "Camera.h"
#include "Obstacle.h"
#include "Enemy.h"
#include "Object.h"

int main()
{

    int collectedObjects = 0;
    
    const sf::Font font(fontPath);
    sf::Text counterText(font, "Potions: 0", 24);
    counterText.setFillColor(sf::Color::Black);

    std::cout << "SFML Version: " << SFML_VERSION_MAJOR << "." 
    << SFML_VERSION_MINOR << "." << SFML_VERSION_PATCH << std::endl;

    // Create the main window
    sf::RenderWindow window(sf::VideoMode({
        static_cast<unsigned int>(S_W), 
        static_cast<unsigned int>(S_H)}), "Palitos y palotes");
    window.setFramerateLimit(60);
    sf::Clock clock;

    // Entity objects
    Stickman stickman(STICKMAN_HEIGHT, STICKMAN_WIDTH);
    Enemy enemy(STICKMAN_HEIGHT,S_H-STICKMAN_HEIGHT);
    std::vector<Stickman*> enemies = {&enemy};

    // Obstacle objects
    std::vector<Obstacle*> obstacles = {
        // Obstacle constructor: posx, posy, width, height, color
        new Obstacle(-9999.0f, S_H, 99999.0f, 20.0f, sf::Color::Black), // Floor
        new Obstacle(200.0f, S_H - 150.0f, 200.0f, 20.0f, sf::Color::Cyan), // Platform
        new Obstacle(600.0f, S_H - 300.0f, 200.0f, 20.0f, sf::Color::Cyan),  // Higher Platform
        new Obstacle(1000.0f, S_H - 450.0f, 200.0f, 20.0f, sf::Color::Cyan),  // Even Higher Platform
        new Obstacle(500.0f, S_H - 600.0f, 200.0f, 20.0f, sf::Color::Cyan),  // Even Higherer Platform
        new Obstacle(0.0f, S_H - 750.0f, 600.0f, 20.0f, sf::Color::Cyan),  // Even Highererer Platform
        new Object(600.0f, S_H - 150.0f, 100.0f, 100.0f, spritePath, sf::Color::Green), // Object to interact with
        new Object(1010.0f, S_H - 550.0f, 100.0f, 100.0f, spritePath, sf::Color::Green), // Object to interact with
        new Object(550.0f, S_H - 710.0f, 100.0f, 100.0f, spritePath, sf::Color::Green), // Object to interact with
        new Object(50.0f, S_H - 760.0f, 100.0f, 100.0f, spritePath, sf::Color::Green), // Object to interact with
        new Object(0.0f, S_H - 750.0f, 100.0f, 100.0f, spritePath, sf::Color::Green) // Object to interact with
    };


    // Create a Camera
    Camera camera(S_W, S_H, CAMERA_SMOOTHING); // lower smoothing factor for slower movement    

    // Load background texture
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile(backgroundPath)) {
        // Handle error - maybe use a fallback color
        std::cerr << "Failed to load background texture!" << std::endl;
    }
    sf::Sprite backgroundSprite(backgroundTexture);

    backgroundSprite.setPosition(sf::Vector2f(0.0f, 0.0f));

    backgroundSprite.setScale(
        sf::Vector2f(
            static_cast<float>(S_W) / backgroundTexture.getSize().x,
            static_cast<float>(S_H) / backgroundTexture.getSize().y
        )
    );
    // Start the game loop
    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        // Process events
        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();
            }
        // Clear screen
        window.clear(sf::Color(R_BG, G_BG, B_BG));

        // Stickman input
        stickman.update(deltaTime, obstacles, enemies);

        enemy.update(deltaTime, obstacles, stickman);

        // Update view to follow stickman
        camera.setTarget(stickman.getPosition());
        camera.update(deltaTime);
        camera.applyToWindow(window);
        counterText.setPosition(sf::Vector2f(camera.getCenter().x - S_W / 2 + 10, 
        camera.getCenter().y - S_H / 2 + 10));

        // Draw the background
        window.draw(backgroundSprite);
        // Draw the stickman
        stickman.draw(window);
        enemy.draw(window);

        // Check if objects are collected and update counter
        for (auto it = obstacles.begin(); it != obstacles.end(); ) {
            Object* obj = dynamic_cast<Object*>(*it);
            if (obj && !obj->isVisible()) {
                collectedObjects++;
                delete obj;
                it = obstacles.erase(it); // Eliminate the collected object
            } else {
                ++it;
            }
        }

        // Draw the obstacles
        for (Obstacle* obstacle : obstacles) {
            obstacle->draw(window);
        }

        // Update and draw the collected objects counter
        counterText.setString("Potions: " + std::to_string(collectedObjects));
        window.draw(counterText);
        
        // Update the window
        window.display();
    }

    // FREE ALL THE MEMORY
    for (auto* obstacle : obstacles) {
        delete obstacle;
    }

    std::cout << "Exiting the game. Goodbye!" << std::endl;

    return 0;
}