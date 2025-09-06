#include "globals.h"
#include <SFML/Graphics.hpp>
#include "Stickman.h"
#include <iostream>
#include "Camera.h"
#include "Obstacle.h"

int main()
{
     std::cout << "SFML Version: " << SFML_VERSION_MAJOR << "." 
              << SFML_VERSION_MINOR << "." << SFML_VERSION_PATCH << std::endl;



    // Create the main window
    sf::RenderWindow window(sf::VideoMode({
        static_cast<unsigned int>(S_W), 
        static_cast<unsigned int>(S_H)}), "Palitos y palotes");
    window.setFramerateLimit(60);
    Stickman stickman(STICKMAN_HEIGHT, STICKMAN_WIDTH);
    sf::Clock clock;
    Obstacle floor = Obstacle(-55555.0f, S_H, 99999.0f, 20.0f, sf::Color::Black); 

    // Create a Camera
    Camera camera(S_W, S_H, CAMERA_SMOOTHING); // lower smoothing factor for slower movement    

    // Load background texture
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("../assets/background/elation.png")) {
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
        stickman.handleInput();
        stickman.update(deltaTime, floor);

        // Update view to follow stickman
        camera.setTarget(stickman.getPosition());
        camera.update(deltaTime);
        camera.applyToWindow(window);

        // Draw the background
        window.draw(backgroundSprite);
        // Draw the stickman
        stickman.draw(window);
        // Draw the floor
        floor.draw(window);
       
        // Update the window
        window.display();
    }
}