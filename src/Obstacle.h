#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <SFML/Graphics.hpp>
class Obstacle {
    private:
        sf::RectangleShape o_shape;
        sf::Vector2f o_position;
        sf::Vector2f o_size;

    public:
        Obstacle(float posX, 
            float posY, 
            float width, 
            float height, 
            sf::Color color = sf::Color::Blue);
        
        sf::Vector2f getPosition() const { return o_position;}
        sf::Vector2f getSize() const { return o_size;}

        void draw(sf::RenderWindow &window) {
            window.draw(o_shape);
        }

        sf::FloatRect getBounds() const;
};
    



#endif // OBSTACLE_H