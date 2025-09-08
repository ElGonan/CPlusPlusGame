#ifndef STICKMAN_H
#define STICKMAN_H

// #pragma once
#include <SFML/Graphics.hpp>
#include "Obstacle.h"


// This is the bounding box only
class Stickman {
    protected:
    sf::RectangleShape m_shape;
    sf::Vector2f m_velocity;
    sf::Color m_color;

    const float m_speed; // pixels per second
    const float m_jumpHeight; // pixels
    bool m_IsJumping; // pixels

    void checkCollision(const Obstacle& obstacle);
    void checkCollision(const Stickman& other);

    private:

    bool m_isPushed;
    float m_pushForce;
    float m_pushDuration;
    float m_pushTimer;


    public:
    // Constructor
    Stickman(float starX, float startY);
    
    // Moving the square
    virtual void update(float deltaTime, const std::vector<Obstacle*>& obstacles);
    virtual void update(float deltaTime, const std::vector<Obstacle*>& obstacles , const std::vector<Stickman*>& enemies);
    // Draw the square
    void draw(sf::RenderWindow &window);
    // Handle input
    virtual void handleInput();
    // Get the global bounds of the square
    sf::FloatRect getBounds() const; 
    // FloatRect is a struct that contains the position and size of the rectangle

    
    // Get the position of the square
    sf::Vector2f getPosition() const {return m_shape.getPosition();};

    // pushBack
    void pushBack(const sf::Vector2f& direction);
    void updatePush(float deltaTime);

    // Check if stickman is an enemy
    virtual bool isEnemy() const { return false; };

    virtual sf::RectangleShape getShape() const { return m_shape; }
};

#endif //STICKMAN_H

