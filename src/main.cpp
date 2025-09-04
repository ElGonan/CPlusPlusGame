#include <SFML/Graphics.hpp>
#include "Stickman.h"

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Palitos y palotes");
    window.setFramerateLimit(60);
    Stickman stickman(500.0f, 250.0f);
    sf::Clock clock;

    int r = 255;
    int g = 255;
    int b = 255;

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
        window.clear(sf::Color(r,g,b));
        stickman.handleInput();
        stickman.update(deltaTime);
        stickman.draw(window);
        // Update the window
        window.display();
    }
}