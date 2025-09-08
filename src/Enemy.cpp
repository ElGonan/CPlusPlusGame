#include "Enemy.h"
#include "globals.h"

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

    // Simple AI: Move left and right
    if (m_shape.getPosition().x < 100) {
        m_velocity.x = 100;
    } else if (m_shape.getPosition().x > 700) {
        m_velocity.x = -100;
    }

    m_shape.move(m_velocity * deltaTime);
}

void Enemy::draw(sf::RenderWindow &window) {
    window.draw(m_shape);
}