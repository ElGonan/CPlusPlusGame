#include "Stickman.h"
#include "globals.h"
#include "Obstacle.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>

Stickman::Stickman(float startX, float startY) :
    m_speed(STICKMAN_SPEED),
    m_IsJumping(false),
    m_jumpHeight(STICKMAN_JUMP_HEIGHT)
{
    m_shape.setSize(sf::Vector2f(STICKMAN_SIZE, STICKMAN_SIZE));
    m_shape.setPosition(sf::Vector2f(startX, startY));
    m_shape.setFillColor(sf::Color::Red);
    m_velocity = sf::Vector2f(0.0f, 0.0f);
}

void Stickman::handleInput() {
    m_velocity.x = 0.0f;
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        m_velocity.x = -m_speed;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        m_velocity.x = m_speed;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !m_IsJumping) {
        m_velocity.y = -m_jumpHeight;
        m_IsJumping = true;
    }
}

void Stickman::checkCollision(const Obstacle& obstacle) {
    sf::FloatRect stickmanBounds = m_shape.getGlobalBounds();
    sf::FloatRect obstacleBounds = obstacle.getBounds();

    // Check if the two rectangles intersect (SFML 3.0 way)
    if (stickmanBounds.findIntersection(obstacleBounds) != std::nullopt) {
        // Get the intersection rectangle
        auto intersection = stickmanBounds.findIntersection(obstacleBounds);
        
        // Calculate overlap in each direction
        float overlapLeft = intersection->position.x - stickmanBounds.position.x;
        float overlapRight = stickmanBounds.position.x + stickmanBounds.size.x - intersection->position.x - intersection->size.x;
        float overlapTop = intersection->position.y - stickmanBounds.position.y;
        float overlapBottom = stickmanBounds.position.y + stickmanBounds.size.y - intersection->position.y - intersection->size.y;

        // Find the minimum overlap
        float minOverlapX = std::min(std::abs(overlapLeft), std::abs(overlapRight));
        float minOverlapY = std::min(std::abs(overlapTop), std::abs(overlapBottom));

        // Resolve collision along the axis of least penetration
        if (minOverlapX < minOverlapY) {
            if (overlapLeft < overlapRight) {
                // Collision from left
                m_shape.setPosition(sf::Vector2f(obstacleBounds.position.x - stickmanBounds.size.x, m_shape.getPosition().y));
            } else {
                // Collision from right
                m_shape.setPosition(sf::Vector2f(obstacleBounds.position.x + obstacleBounds.size.x, m_shape.getPosition().y));
            }
            // Stop horizontal movement when colliding
            m_velocity.x = 0.0f;
        } else {
            if (overlapTop < overlapBottom) {
                // Collision from top
                m_shape.setPosition(sf::Vector2f(m_shape.getPosition().x, obstacleBounds.position.y - stickmanBounds.size.y));
                m_velocity.y = 0.0f; // Stop vertical movement
            } else {
                // Collision from bottom
                m_shape.setPosition(sf::Vector2f(m_shape.getPosition().x, obstacleBounds.position.y + obstacleBounds.size.y));
                m_velocity.y = 0.0f;
                m_IsJumping = false; // Land on the obstacle
            }
        }
    }
}

void Stickman::update(float deltaTime, const Obstacle& floor) {
    // Apply gravity
    m_velocity.y += GRAVITY * deltaTime;
    
    // Move the Stickman
    m_shape.move(m_velocity * deltaTime);
    
    // Check for collisions with the floor
    checkCollision(floor);
    
}

void Stickman::draw(sf::RenderWindow& window) {
    window.draw(m_shape);
}

sf::FloatRect Stickman::getBounds() const {
    return m_shape.getGlobalBounds();
}