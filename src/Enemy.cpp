#include "Enemy.h"

Enemy::Enemy(float startX, float startY) :
    Stickman(startX, startY)
{
    m_shape.setFillColor(m_color);
}

void Enemy::handleInput() {
    // Enemy does not handle input
}

void Enemy::update(float deltaTime, const std::vector<Obstacle>& obstacles) {
    Stickman::update(deltaTime, obstacles);
}


void Enemy::draw(sf::RenderWindow &window) {
    window.draw(m_shape);
}