#ifndef STICKMAN_H
#define STICKMAN_H

#pragma once
#include <SFML/Graphics.hpp>


// This is the bounding box only
class Stickman {
    private:
    sf::RectangleShape m_shape;
    sf::Vector2f m_velocity;

    const float m_speed; // pixels per second
    const float m_jumpHeight; // pixels
    bool m_IsJumping; // pixels
    
    public:
    // Constructor
    Stickman(float starX, float startY);
    
    // Moving the square
    void update(float deltaTime);
    // Draw the square
    void draw(sf::RenderWindow &window);
    // Handle input
    void handleInput();
    // Get the global bounds of the square
    sf::FloatRect getBounds(); 
    // FloatRect is a struct that contains the position and size of the rectangle
};

#endif // STICKMAN_H

