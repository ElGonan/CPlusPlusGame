#ifndef CAMERA_H
#define CAMERA_H

#include "globals.h"
#include <SFML/Graphics.hpp>

class Camera {
private:

   sf::View view;
   sf::Vector2f targetPosition;
   float smoothingFactor;
   sf::Vector2f size;
public:
    Camera(float width, float height, float smooth = CAMERA_SMOOTHING);

    void setTarget(const sf::Vector2f& position);
    void update(float deltaTime);
    void setSize(float width, float height);
    void applyToWindow(sf::RenderWindow& window);
    const sf::View& getView() const;
    sf::Vector2f getCenter() const;

};

#endif // CAMERA_H