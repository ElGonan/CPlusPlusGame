#include "Object.h"
#include <iostream>

Object::Object(float startX, float startY, float width, float height, sf::Color color) :
    Obstacle(startX, startY, width, height, color)
    {

    };

void Object::onContact(int& collectedObjects) {
    // override de el contacto, para que no se quede detenido en el aire
    if (m_visible) {
        collectedObjects++;
        disappear();
        std::cout << "Object collected!" << std::endl;
    }

}


void Object::draw(sf::RenderWindow &window) {
    if (m_visible)
        Obstacle::draw(window);
};

void Object::disappear() {
    m_visible = false;
    std::cout << "Object disappeared!" << std::endl;
}