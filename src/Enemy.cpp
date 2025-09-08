#include "Enemy.h"

Enemy::Enemy(float startX, float startY) :
    Stickman(startX, startY)
{
    m_shape.setFillColor(m_color);
}

void Enemy::handleInput() {
    // Enemy does not handle input
}

void Enemy::update(float deltaTime, const std::vector<Obstacle*>& obstacles) {
    Stickman::update(deltaTime, obstacles);

    // Simple AI: Move left and right between two points
    static float leftBoundary = 100.0f;
    static float rightBoundary = 700.0f;
    static bool movingRight = true;
    float speed = 100.0f; // pixels per second

    // Update enemy position
    if (movingRight) {
        m_shape.move(sf::Vector2f(speed * deltaTime, 0));
        if (m_shape.getPosition().x > rightBoundary) {
            m_shape.setPosition(sf::Vector2f(rightBoundary, m_shape.getPosition().y));
            movingRight = false;
        }
    } else {
        m_shape.move(sf::Vector2f(-speed * deltaTime, 0));
        if (m_shape.getPosition().x < leftBoundary) {
            m_shape.setPosition(sf::Vector2f(leftBoundary, m_shape.getPosition().y));
            movingRight = true;
        }
    }
}

void Enemy::draw(sf::RenderWindow &window) {
    window.draw(m_shape);
}