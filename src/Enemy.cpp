#include "Enemy.h"

Enemy::Enemy(float startX, float startY) :
    Stickman(startX, startY)
{
}

void Enemy::handleInput() {
    // Enemies might have different AI-based movement
}

void Enemy::update(float deltaTime, const Obstacle& floor, const Obstacle& platform) {
    Stickman::update(deltaTime, floor, platform);
}
void Enemy::draw(sf::RenderWindow &window) {
    window.draw(m_shape);
}