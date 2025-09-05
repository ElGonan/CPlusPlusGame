#include "globals.h"
#include <SFML/Graphics.hpp>
#include "Stickman.h"

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode({S_W, S_H}), "Palitos y palotes");
    window.setFramerateLimit(60);
    Stickman stickman(STICKMAN_HEIGHT, STICKMAN_WIDTH);
    sf::Clock clock;

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
        stickman.handleInput();
        stickman.update(deltaTime);
        stickman.draw(window);
        // Update the window
        window.display();
    }
}