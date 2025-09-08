#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include "Stickman.h"

class Enemy : public Stickman {
    private:
    sf::Color m_color = sf::Color::Yellow;
    public:
    Enemy(float startX, float startY);
    void handleInput() override;
    void update(float deltaTime, const std::vector<Obstacle*>& obstacles) override;
    void draw(sf::RenderWindow &window);
    bool isEnemy() const override { return true; };

};

#endif // ENEMY_H
