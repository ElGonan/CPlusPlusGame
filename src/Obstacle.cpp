#include "Obstacle.h"

Obstacle::Obstacle(float posX, float posY, float width, float height, sf::Color color) {
    o_position = sf::Vector2f(posX, posY);
    o_size = sf::Vector2f(width, height);
    o_shape.setSize(o_size);
    o_shape.setPosition(o_position);
    o_shape.setFillColor(color);
}

Obstacle::~Obstacle() {
    // Destructor implementation (if needed)
}

void Obstacle::draw(sf::RenderWindow &window) {
    window.draw(o_shape);
}


sf::FloatRect Obstacle::getBounds() const {
    return o_shape.getGlobalBounds();
}