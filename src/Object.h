#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>
#include "Obstacle.h"

class Object : public Obstacle {
    private:
        bool m_visible = true;
        sf::Texture m_texture;
        sf::Sprite m_sprite;

    public:
        Object(float startX, 
            float startY, 
            float width, 
            float height, 
            const std::string& spritePath,
            sf::Color color = sf::Color::Green
            );
        std::string spritePath;
        void draw(sf::RenderWindow &window) override;
        void onContact(); 
        void disappear();
        bool isVisible();

        sf::FloatRect getBounds() const override;
};


#endif // OBJECT_H