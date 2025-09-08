#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>
#include "Obstacle.h"

class Object : public Obstacle {
    private:
        bool m_visible = true;
    public:
        Object(float startX, float startY, float width, float height, sf::Color color = sf::Color::Green);
        void draw(sf::RenderWindow &window) override;
        void onContact(int& collectedObjects); 
        void disappear();
};


#endif // OBJECT_H