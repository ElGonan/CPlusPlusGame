#include "Camera.h"
#include "globals.h"
#include <SFML/Graphics.hpp>

Camera::Camera(float width, float height, float smooth)
    : size(width, height), smoothingFactor(smooth) {
    view.setSize(size);
    targetPosition = sf::Vector2f(CAMERA_INITIAL_POS_X, CAMERA_INITIAL_POS_Y);
    view.setCenter(targetPosition);
}

void Camera::setTarget(const sf::Vector2f& position) {
    // targetPosition = position;
    // Offset the target position to have the stickman slightly lower in the screen
    targetPosition = sf::Vector2f(position.x, position.y - STICKMAN_HEIGHT / 2.25f);
}

void Camera:: update(float deltaTime) {
    sf::Vector2f currentCenter = view.getCenter();
    sf::Vector2f newCenter = currentCenter + (targetPosition - currentCenter) * smoothingFactor;
    view.setCenter(newCenter);

    // Add camera logic to prevent showing areas outside the game world
}

void Camera::setSize(float width, float height) {
    size = sf::Vector2f(width, height);
    view.setSize(size);
}

void Camera::applyToWindow(sf::RenderWindow& window) {
    window.setView(view);
}

const sf::View& Camera::getView() const {
    return view;
}

sf::Vector2f Camera::getCenter() const {
    return view.getCenter();
}