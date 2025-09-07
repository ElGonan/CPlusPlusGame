#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include "Stickman.h"

class Enemy : public Stickman {
    public:
    Enemy(float startX, float startY);
    void handleInput() override;
    void update(float deltaTime, const Obstacle& floor, const Obstacle& platform) override;
    void draw(sf::RenderWindow &window);

};

#endif // ENEMY_H
