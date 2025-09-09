#include "Enemy.h"
#include "globals.h"
#include <SFML/Graphics.hpp>
#include <cmath>

Enemy::Enemy(float startX, float startY) :
    Stickman(startX, startY)
{
    m_shape.setFillColor(m_color);
}

void Enemy::handleInput() {
    // Enemy does not handle input
}

void Enemy::update(float deltaTime, const std::vector<Obstacle*>& obstacles) {
    
    m_velocity.y += GRAVITY * deltaTime;
    // Check for collisions with all obstacles
    for (Obstacle* obstacle : obstacles) {
        checkCollision(*obstacle);
    }

    // // Simple AI: Move left and right
    // if (m_shape.getPosition().x < 100) {
    //     m_velocity.x = 100;
    // } else if (m_shape.getPosition().x > 700) {
    //     m_velocity.x = -100;
    // }

    m_shape.move(m_velocity * deltaTime);
}


void Enemy::update(float deltaTime, const std::vector<Obstacle*>& obstacles , const Stickman& player) {
    update(deltaTime, obstacles);
    // Simple AI: Move towards the player if within range
    float detectionRange = 200.0f; // Example range
    if (playerInRange(player, detectionRange)) {
        m_velocity.x = (player.getPosition().x - m_shape.getPosition().x)*2.0f; // Move towards player
        if (player.getPosition().y < m_shape.getPosition().y && !m_IsJumping) {
            m_velocity.y = -std::sqrt(3.0f * GRAVITY * 100.0f); // Jump if player is above
            m_IsJumping = true;
        }
        
    }
}

bool Enemy::playerInRange(const Stickman& player, float range) {
    float distance = std::abs(player.getPosition().x - m_shape.getPosition().x);
    return distance <= range;

    
}

void Enemy::draw(sf::RenderWindow &window) {
    window.draw(m_shape);
}